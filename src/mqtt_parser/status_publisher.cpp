// status_publisher.cpp
#include "status_publisher.h"

const char *controlModeToString(ControlMode mode)
{
    switch (mode)
    {
    case ControlMode::AUTO:
        return "AUTO";

    case ControlMode::MANUAL:
        return "MANUAL";

    default:
        return "UNKNOWN";
    }
}

StatusPublisher::StatusPublisher(MqttManager &mqttManager)
    : _mqttManager(mqttManager) {}

void StatusPublisher::loop()
{
    if (_firstRunStatus || hasStatusChanged())
    {
        publishStatus();

        _lastTinaco = gSystemState.tinaco;
        _lastCisterna = gSystemState.cisterna;

        _firstRunStatus = false;
    }

    if (_firstRunPump || hasPumpChanged())
    {
        publishPump();

        _lastBomba = gSystemState.bomba;

        _firstRunPump = false;
    }

    if (hasParametersChanged())
    {
        publishParameters();
        _lastConfig = gSystemConfig;
        //_firstRunParameters = false;
    }
}

bool StatusPublisher::hasStatusChanged()
{
    return gSystemState.tinaco.levelPercent !=
               _lastTinaco.levelPercent ||

           gSystemState.tinaco.sensorState !=
               _lastTinaco.sensorState ||

           gSystemState.tinaco.ConnectionState !=
               _lastTinaco.ConnectionState ||

           gSystemState.cisterna.levelPercent !=
               _lastCisterna.levelPercent ||

           gSystemState.cisterna.SensorState !=
               _lastCisterna.SensorState;
}

bool StatusPublisher::hasPumpChanged()
{
    return gSystemState.bomba.isOn !=
               _lastBomba.isOn ||

           gSystemState.bomba.controlMode !=
               _lastBomba.controlMode;
}

bool StatusPublisher::hasParametersChanged()
{
    return gSystemConfig.tinaco.height_cm !=
               _lastConfig.tinaco.height_cm ||
           gSystemConfig.tinaco.levelHigh !=
               _lastConfig.tinaco.levelHigh ||
           gSystemConfig.tinaco.levelLow !=
               _lastConfig.tinaco.levelLow ||
           gSystemConfig.cisterna.height_cm !=
               _lastConfig.cisterna.height_cm ||
           gSystemConfig.cisterna.minLevel !=
               _lastConfig.cisterna.minLevel;
}

void StatusPublisher::publishStatus()
{
    JsonDocument doc;

    doc["status"]["tinLevel"] =
        gSystemState.tinaco.levelPercent;

    doc["status"]["cisLevel"] =
        gSystemState.cisterna.levelPercent;

    doc["status"]["sensorTin"] =
        gSystemState.tinaco.sensorState;

    doc["status"]["sensorCis"] =
        gSystemState.cisterna.SensorState;
    doc["status"]["tinBattery"] = gSystemState.tinaco.battery;
    doc["status"]["connectionTin"] = gSystemState.tinaco.ConnectionState;
    String payload;
    serializeJson(doc, payload);

    _mqttManager.publishData(payload.c_str());
}

void StatusPublisher::publishPump()
{
    JsonDocument doc;

    doc["pump"]["isOn"] =
        gSystemState.bomba.isOn;

    doc["pump"]["mode"] =
        controlModeToString(
            gSystemState.bomba.controlMode);

    String payload;
    serializeJson(doc, payload);

    _mqttManager.publishData(payload.c_str());
}

void StatusPublisher::publishParameters()
{
    JsonDocument doc;
    doc["parameters"]["hTin"] = gSystemConfig.tinaco.height_cm;
    doc["parameters"]["levelHigh"] = gSystemConfig.tinaco.levelHigh;
    doc["parameters"]["levelLow"] = gSystemConfig.tinaco.levelLow;
    doc["parameters"]["hCis"] = gSystemConfig.cisterna.height_cm;
    doc["parameters"]["minCis"] = gSystemConfig.cisterna.minLevel;
    String payload;
    serializeJson(doc, payload);
    _mqttManager.publishData(payload.c_str());
}