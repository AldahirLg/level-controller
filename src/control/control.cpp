#include "control.h"

Control::Control(IPump &pump)
    : _pump(pump) {}

void Control::loop()
{
    switch (gSystemConfig.control_mode)
    {
    case ControlMode::MANUAL:
        manual();
        break;
    case ControlMode::AUTOMATIC:
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
    if (_manualPumpRequest && gSystemState.cisterna.levelPercent < gSystemConfig.cisterna.level_low_percent)
    {
        _pump.off();
        gSystemState.bomba.isOn = false;
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

    if (gSystemState.cisterna.levelPercent < gSystemConfig.cisterna.level_low_percent)
    {
        _event = SystemEvent::CIS_LOW_LEVEL;
    }

    else if (gSystemState.tinaco.levelPercent >= gSystemConfig.tinaco.level_high_percent)
    {
        _event = SystemEvent::HIGH_LEVEL;
    }

    else if (gSystemState.tinaco.levelPercent < gSystemConfig.tinaco.level_low_percent)
    {
        _event = SystemEvent::LOW_LEVEL;
    }
    else
    {
        _event = SystemEvent::NORMAL_LEVEL;
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
    case SystemEvent::NORMAL_LEVEL:

        break;
    default:
        break;
    }
}

void Control::lowLevel()
{
    _pump.on();
    gSystemState.bomba.isOn = true;
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
void Control::normalLevel() {}