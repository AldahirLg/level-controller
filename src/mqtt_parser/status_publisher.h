// status_publisher.h
#pragma once
#include "system_state/system_state.h"
#include "mqtt/mqtt_manager.h"
#include <ArduinoJson.h>

class StatusPublisher
{
public:
    StatusPublisher(MqttManager &mqttManager);

    void loop();

private:
    MqttManager &_mqttManager;
    String _deviceId;

    TinacoState _lastTinaco{};
    CisternaState _lastCisterna{};
    BombaState _lastBomba{};
    bool _firstRun = true;

    ControlMode _lastMode{};

    bool hasChanged();
    void publish();
};