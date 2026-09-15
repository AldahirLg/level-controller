#include "control.h"

Control::Control(IPump &pump, MqttManager &mqttManager)
    : _pump(pump), _mqttManager(mqttManager) {}

void Control::loop()
{
    switch (gSystemState.bomba.controlMode)
    {
    case ControlMode::MANUAL:
        manual();
        break;
    case ControlMode::AUTO:
        automatic();
        break;
    default:
        break;
    }
}

void Control::setManualPump(bool on)
{
    _manualPumpRequest = on;
}

void Control::manual()
{
    if (_manualPumpRequest && gSystemState.cisterna.levelPercent < gSystemConfig.cisterna.minLevel)
    {
        _pump.off();
        gSystemState.bomba.isOn = false;
        _manualPumpRequest = false;
        // notificar mqtt
        return;
    }

    if (_manualPumpRequest)
    {
        _pump.on();
        gSystemState.bomba.isOn = true;
    }

    else
    {
        _pump.off();
        gSystemState.bomba.isOn = false;
    }

    // notificar mqtt si hubo cambio de estado
}

void Control::automatic()
{
    // 1. Errores: máxima prioridad
    if (!gSystemState.tinaco.sensorState ||
        !gSystemState.cisterna.SensorState)
    {
        _event = SystemEvent::ERROR_SENSOR;
    }
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

    if (_event != _lastEvent)
    {
        notifyEvent(_event);
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
        break;
    }
}

void Control::setControlMode(ControlMode mode)
{
    gSystemState.bomba.controlMode = mode;
}

void Control::setConfig(const SystemConfig &config)
{
    gSystemConfig = config;
}

void Control::checkFillStall()
{
    float current = gSystemState.tinaco.levelPercent;

    if (current - _fillCheckpointLevel >= MIN_INCREASE_PERCENT)
    {
        _fillCheckpointLevel = current;
        _fillCheckpointTime = millis();
        return;
    }

    if (millis() - _fillCheckpointTime >= FILL_STALL_TIMEOUT_MS)
    {
        _event = SystemEvent::PUMP_STALL;
    }
}

void Control::errorPumpStall()
{
    _pump.off();
    gSystemState.bomba.isOn = false;
    _fillTimerActive = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;
}

void Control::lowLevel()
{

    if (!_fillTimerActive)
    {
        _fillTimerActive = true;
        _fillCheckpointLevel = gSystemState.tinaco.levelPercent;
        _fillCheckpointTime = millis();
    }
    checkFillStall();
    _pump.on();
    gSystemState.bomba.isOn = true;
    Serial.printf("[Control]: %s\n", eventToString(_event));
}

void Control::highLevel()
{
    _pump.off();
    gSystemState.bomba.isOn = false;
}

void Control::lowCisLevel()
{
    _pump.off();
    gSystemState.bomba.isOn = false;
}

void Control::errorSensor()
{
    _pump.off();
    gSystemState.bomba.isOn = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;
}

void Control::errorConnectionTin()
{
    _pump.off();
    gSystemState.bomba.isOn = false;
    gSystemState.bomba.controlMode = ControlMode::MANUAL;
}

void Control::normalLevel() {}

void Control::notifyEvent(SystemEvent event)
{
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