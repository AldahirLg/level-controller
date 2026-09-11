#pragma once
// #include <Arduino.h>
#include <cstdint>
#include "system_state/system_state.h"
#include "pump/i_pump.h"

enum SystemEvent
{
    HIGH_LEVEL,
    LOW_LEVEL,
    CIS_LOW_LEVEL,
    NORMAL_LEVEL,
};

class Control
{
public:
    Control(IPump &pump);
    void loop();
    SystemEvent getSystemEvent();
    void setManualPump(bool on);

private:
    IPump &_pump;
    SystemEvent _event{SystemEvent::NORMAL_LEVEL};
    bool _manualPumpRequest{false};

    void manual();
    void automatic();
    void highLevel();
    void lowLevel();
    void lowCisLevel();
    void normalLevel();
};