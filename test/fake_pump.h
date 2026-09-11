// test/fake_pump.h
#pragma once

#include "pump/i_pump.h"

class FakePump : public IPump
{
public:
    void on() override
    {
        isOn = true;
        onCallCount++;
    }

    void off() override
    {
        isOn = false;
        offCallCount++;
    }

    bool state() override
    {
        return isOn;
    }

    bool isOn{false};
    int onCallCount{0};
    int offCallCount{0};
};