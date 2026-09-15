#pragma once
#include <Arduino.h>
// #include <cstdint>
#include "system_state/system_state.h"
#include "pump/i_pump.h"
#include "mqtt/mqtt_manager.h"
#include <ArduinoJson.h>

enum SystemEvent
{
    HIGH_LEVEL,
    LOW_LEVEL,
    CIS_LOW_LEVEL,
    NORMAL_LEVEL,
    ERROR_SENSOR,
    ERROR_CONNECTION_TIN,
    PUMP_STALL
};

class Control
{
public:
    Control(IPump &pump, MqttManager &mqttManager);
    void loop();
    SystemEvent getSystemEvent();
    void setManualPump(bool on);
    void setConfig(const SystemConfig &config);
    void setControlMode(ControlMode mode);

private:
    IPump &_pump;
    MqttManager &_mqttManager;

    SystemEvent _event{SystemEvent::NORMAL_LEVEL};
    bool _manualPumpRequest{false};

    unsigned long _fillCheckpointTime = 0;
    float _fillCheckpointLevel = 0.0f;
    bool _fillTimerActive = false;
    static constexpr unsigned long FILL_STALL_TIMEOUT_MS = 60000;
    static constexpr float MIN_INCREASE_PERCENT = 1.0f;

    void checkFillStall();

    void manual();
    void automatic();
    void highLevel();
    void lowLevel();
    void lowCisLevel();
    void normalLevel();
    void errorSensor();
    void errorConnectionTin();
    void errorPumpStall();
    SystemEvent _lastEvent = SystemEvent::NORMAL_LEVEL;

    void notifyEvent(SystemEvent event);
    const char *eventToString(SystemEvent event);
};