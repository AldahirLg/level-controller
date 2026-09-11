#pragma once
#include <Arduino.h>
#include <cstdint>
#include "i_pump.h"

class Pump : public IPump
{
public:
    Pump(uint8_t pin, bool activeHigh = true);
    void begin();
    void on() override;
    void off() override;
    void toggle();
    bool state() override;

private:
    uint8_t _pin;
    bool _activeHigh;
    bool _state;
};