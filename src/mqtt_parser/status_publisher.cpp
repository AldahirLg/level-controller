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
    if (_firstRun || hasChanged())
    {
        publish();

        _lastTinaco = gSystemState.tinaco;
        _lastCisterna = gSystemState.cisterna;
        _lastBomba = gSystemState.bomba;

        _firstRun = false;
    }
}

bool StatusPublisher::hasChanged()
{
    return gSystemState.tinaco.levelPercent !=
               _lastTinaco.levelPercent ||

           gSystemState.tinaco.sensorState !=
               _lastTinaco.sensorState ||

           gSystemState.cisterna.levelPercent !=
               _lastCisterna.levelPercent ||

           gSystemState.cisterna.SensorState !=
               _lastCisterna.SensorState ||

           gSystemState.bomba.isOn !=
               _lastBomba.isOn ||

           gSystemState.bomba.controlMode !=
               _lastBomba.controlMode;
}

void StatusPublisher::publish()
{
    JsonDocument doc;

    // Estado general
    doc["status"]["tinLevel"] =
        gSystemState.tinaco.levelPercent;

    doc["status"]["cisLevel"] =
        gSystemState.cisterna.levelPercent;

    doc["status"]["sensorTin"] =
        gSystemState.tinaco.sensorState;

    doc["status"]["sensorCis"] =
        gSystemState.cisterna.SensorState;

    // Estado de bomba
    doc["pump"]["isOn"] =
        gSystemState.bomba.isOn;

    doc["pump"]["mode"] =
        controlModeToString(
            gSystemState.bomba.controlMode);

    String payload;

    serializeJson(doc, payload);

    _mqttManager.publishData(payload.c_str());
}
