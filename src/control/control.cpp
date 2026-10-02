#include "control.h"

static bool isNotifiableEvent(SystemEvent event)
{
    switch (event)
    {
    case SystemEvent::CIS_LOW_LEVEL:
    case SystemEvent::ERROR_SENSOR:
    case SystemEvent::ERROR_CONNECTION_TIN:
    case SystemEvent::PUMP_STALL:
        return true;
    default:
        return false;
    }
}

Control::Control(IPump &pump, MqttManager &mqttManager)
    : _pump(pump), _mqttManager(mqttManager)
{
    Serial.println("[Control] Control inicializado");
}

void Control::loop()
{
    checkTinacoConnection();

    switch (gSystemState.bomba.controlMode)
    {
    case ControlMode::MANUAL:
        manual();
        break;

    case ControlMode::AUTO:
        automatic();
        break;

    default:
        Serial.println("[Control] Modo de control desconocido");
        break;
    }
}

void Control::setManualPump(bool on)
{
    _manualPumpRequest = on;

    Serial.printf(
        "[Control] Solicitud bomba manual: %s\n",
        on ? "ON" : "OFF");
}

void Control::manual()
{
    // Protección de cisterna
    if (_manualPumpRequest &&
        gSystemState.cisterna.levelPercent < gSystemConfig.cisterna.minLevel)
    {
        Serial.printf(
            "[Control] Protección cisterna - nivel %.1f%% < mínimo %.1f%%\n",
            static_cast<double>(gSystemState.cisterna.levelPercent),
            static_cast<double>(gSystemConfig.cisterna.minLevel));

        _pump.off();
        gSystemState.bomba.isOn = _pump.state();
        _manualPumpRequest = false;

        notifyEvent(SystemEvent::CIS_LOW_LEVEL);
        return;
    }

    if (_manualPumpRequest && !gSystemState.bomba.isOn)
    {
        _pump.on();
        gSystemState.bomba.isOn = _pump.state();
    }
    else if (!_manualPumpRequest && gSystemState.bomba.isOn)
    {
        _pump.off();
        gSystemState.bomba.isOn = _pump.state();
    }
}

void Control::automatic()
{
    // 1. Errores: máxima prioridad
    if (!gSystemState.tinaco.sensorState ||
        !gSystemState.cisterna.SensorState)
    {
        _event = SystemEvent::ERROR_SENSOR;
    }

    // IMPLEMENTACION DESPUES
    else if (!gSystemState.tinaco.ConnectionState)
    {
        _event = SystemEvent::ERROR_CONNECTION_TIN;
    }

    // 2. Protecciones de nivel
    else if (gSystemState.cisterna.levelPercent <
             gSystemConfig.cisterna.minLevel)
    {
        _event = SystemEvent::CIS_LOW_LEVEL;
    }

    // 3. Control por nivel
    else if (gSystemState.tinaco.levelPercent >=
             gSystemConfig.tinaco.levelHigh)
    {
        _event = SystemEvent::HIGH_LEVEL;
    }
    else if (gSystemState.tinaco.levelPercent <
             gSystemConfig.tinaco.levelLow)
    {
        _event = SystemEvent::LOW_LEVEL;
    }

    // 4. Banda normal
    else
    {
        _event = SystemEvent::NORMAL_LEVEL;
    }

    // 5. Falla de llenado: solo si no hay otro evento con más prioridad.
    //    Se vigila siempre que la bomba esté encendida (LOW_LEVEL o banda normal).
    if ((_event == SystemEvent::LOW_LEVEL ||
         _event == SystemEvent::NORMAL_LEVEL) &&
        monitorFill())
    {
        Serial.println("[Control] FALLA - bomba sin incremento de nivel");
        _event = SystemEvent::PUMP_STALL;
    }

    if (_event != _lastEvent)
    {
        Serial.printf(
            "[Control] Evento cambiado: %s -> %s\n",
            eventToString(_lastEvent),
            eventToString(_event));

        notifyEvent(_event); // filtra internamente: solo errores
        _lastEvent = _event;
    }

    switch (_event)
    {
    case SystemEvent::HIGH_LEVEL:
        highLevel();
        break;

    case SystemEvent::LOW_LEVEL:
        lowLevel();
        break;

    case SystemEvent::CIS_LOW_LEVEL:
        lowCisLevel();
        break;

    case SystemEvent::ERROR_SENSOR:
        errorSensor();
        break;

    case SystemEvent::ERROR_CONNECTION_TIN:
        errorConnectionTin();
        break;

    case SystemEvent::PUMP_STALL:
        errorPumpStall();
        break;

    case SystemEvent::NORMAL_LEVEL:
        break;

    default:
        Serial.println("[Control] Evento desconocido");
        break;
    }
}

void Control::setControlMode(ControlMode mode)
{
    gSystemState.bomba.controlMode = mode;

    // Limpiar estado pendiente para que la bomba no se reenciende sola
    _manualPumpRequest = false;
    _fillTimerActive = false;
    _lastEvent = SystemEvent::NORMAL_LEVEL; // re-notifica si el error persiste al volver a AUTO

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();

    Serial.printf(
        "[Control] Modo de control cambiado: %s\n",
        mode == ControlMode::AUTO ? "AUTO" : "MANUAL");
}

void Control::setConfig(const SystemConfig &config)
{
    gSystemConfig = config;
    Serial.println("[Control] Configuración actualizada");
}

// Devuelve true si la bomba lleva encendida FILL_STALL_TIMEOUT_MS
// sin que el nivel del tinaco suba al menos MIN_INCREASE_PERCENT.
bool Control::monitorFill()
{
    if (!gSystemState.bomba.isOn)
    {
        _fillTimerActive = false;
        return false;
    }

    const float current = gSystemState.tinaco.levelPercent;

    if (!_fillTimerActive)
    {
        Serial.println("[Control] Iniciando monitoreo de llenado");

        _fillTimerActive = true;
        _fillCheckpointLevel = current;
        _fillCheckpointTime = millis();
        return false;
    }

    if (current - _fillCheckpointLevel >= MIN_INCREASE_PERCENT)
    {
        Serial.printf(
            "[Control] Llenado detectado - nivel: %.1f%% -> %.1f%%\n",
            static_cast<double>(_fillCheckpointLevel),
            static_cast<double>(current));

        _fillCheckpointLevel = current;
        _fillCheckpointTime = millis();
        return false;
    }

    return millis() - _fillCheckpointTime >= FILL_STALL_TIMEOUT_MS;
}

void Control::errorPumpStall()
{
    Serial.println("[Control] PUMP_STALL - apagando bomba");

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();
    _fillTimerActive = false;
    _manualPumpRequest = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;

    Serial.println("[Control] PUMP_STALL - cambiando a modo MANUAL");
}

void Control::lowLevel()
{
    if (!gSystemState.bomba.isOn)
    {
        _pump.on();
        gSystemState.bomba.isOn = _pump.state();

        Serial.printf(
            "[Control] LOW_LEVEL - nivel tinaco: %.1f%% - Bomba ON\n",
            static_cast<double>(gSystemState.tinaco.levelPercent));
    }
}

void Control::highLevel()
{
    const bool wasOn = gSystemState.bomba.isOn;

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();

    if (wasOn)
    {
        Serial.printf(
            "[Control] HIGH_LEVEL - nivel tinaco: %.1f%% - Bomba OFF\n",
            static_cast<double>(gSystemState.tinaco.levelPercent));
    }
}

void Control::lowCisLevel()
{
    const bool wasOn = gSystemState.bomba.isOn;

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();

    if (wasOn)
    {
        Serial.printf(
            "[Control] CIS_LOW_LEVEL - nivel cisterna: %.1f%% - Bomba OFF (protección)\n",
            static_cast<double>(gSystemState.cisterna.levelPercent));
    }
}

void Control::errorSensor()
{
    Serial.println("[Control] ERROR_SENSOR - apagando bomba");

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();
    _manualPumpRequest = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;

    Serial.println("[Control] ERROR_SENSOR - cambiando a modo MANUAL");
}

void Control::errorConnectionTin()
{
    Serial.println("[Control] ERROR_CONNECTION_TIN - apagando bomba");

    _pump.off();
    gSystemState.bomba.isOn = _pump.state();
    _manualPumpRequest = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;

    Serial.println("[Control] ERROR_CONNECTION_TIN - cambiando a modo MANUAL");
}

void Control::normalLevel()
{
    Serial.println("[Control] NORMAL_LEVEL");
}

void Control::notifyEvent(SystemEvent event)
{
    if (!isNotifiableEvent(event))
        return;

    Serial.printf("[Control] Notificando evento MQTT: %s\n", eventToString(event));

    JsonDocument doc;
    doc["event"] = eventToString(event);

    String payload;
    serializeJson(doc, payload);

    _mqttManager.publishEvent(payload.c_str());
}

const char *Control::eventToString(SystemEvent event)
{
    switch (event)
    {
    case SystemEvent::HIGH_LEVEL:
        return "HIGH_LEVEL";

    case SystemEvent::LOW_LEVEL:
        return "LOW_LEVEL";

    case SystemEvent::CIS_LOW_LEVEL:
        return "CIS_LOW_LEVEL";

    case SystemEvent::ERROR_SENSOR:
        return "ERROR_SENSOR";

    case SystemEvent::ERROR_CONNECTION_TIN:
        return "ERROR_CONNECTION_TIN";

    case SystemEvent::PUMP_STALL:
        return "PUMP_STALL";

    case SystemEvent::NORMAL_LEVEL:
        return "NORMAL_LEVEL";

    default:
        return "UNKNOWN";
    }
}

void Control::notifyTinacoData()
{
    _lastTinacoMs = millis();

    if (!gSystemState.tinaco.ConnectionState)
    {
        gSystemState.tinaco.ConnectionState = true;
        Serial.println("[Control] Tinaco conectado");
    }
}

void Control::checkTinacoConnection()
{
    if (gSystemState.tinaco.ConnectionState &&
        millis() - _lastTinacoMs >= TINACO_TIMEOUT_MS)
    {
        gSystemState.tinaco.ConnectionState = false;
        Serial.println("[Control] Tinaco desconectado (sin datos)");
    }
}