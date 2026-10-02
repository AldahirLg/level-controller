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
    if (_state)
        return;
    digitalWrite(_pin, _activeHigh ? HIGH : LOW);
    _state = true;
    Serial.print("ON");
}

void Pump::off()
{
    if (!_state)
        return;
    digitalWrite(_pin, _activeHigh ? LOW : HIGH);
    _state = false;
    Serial.print("OFF");
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