#include "pump.h"

Pump::Pump(uint8_t pin, bool activeHigh)
    : _pin(pin), _activeHigh(activeHigh), _state(false) {}

void Pump::begin()
{
    pinMode(_pin, OUTPUT);
    off();
}

void Pump::on()
{
    digitalWrite(_pin, _activeHigh ? HIGH : LOW);
    _state = true;
}

void Pump::off()
{
    digitalWrite(_pin, _activeHigh ? LOW : HIGH);
    _state = false;
}

void Pump::toggle()
{
    if (_state)
    {
        off();
    }
    else
    {
        on();
    }
}

bool Pump::state()
{
    return _state;
}