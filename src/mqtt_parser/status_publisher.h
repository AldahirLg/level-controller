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
    SystemConfig _lastConfig{};

    bool _firstRunStatus = true;
    bool _firstRunPump = true;
    bool _firstRunParameters = true;
    bool hasStatusChanged();
    bool hasPumpChanged();
    bool hasParametersChanged();

    void publishStatus();
    void publishPump();
    void publishParameters();
};