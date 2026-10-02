#include "sensor.h"

Sensor::Sensor(uint8_t triggerPin, uint8_t echoPin)
    : _sonar(triggerPin, echoPin, 400), _pingTimer(0)
{
}

void Sensor::start()
{
    _attempts = 0;
    _sum = 0;
    _pingTimer = millis();
}

bool Sensor::measure()
{
    unsigned long currentTime = millis();
    if (currentTime - _pingTimer >= _pingSpeed)
    {
        _pingTimer = currentTime;
        unsigned int distance = _sonar.ping_cm();
        _sum += distance;
        _attempts++;
        if (_attempts >= 10)
        {
            if (_sum != 0)
            {
                _distance = round(_sum / 10.0);
                _sensorState = true;
            }
            else
            {
                _sensorState = false;
            }

            return true;
        }
    }
    return false;
}

void Sensor::idle()
{
    start();
    _state = SensorMode::MEASURING;
}

void Sensor::measuring()
{
    if (measure())
    {
        _state = SensorMode::DONE;
    }
}

void Sensor::loop()
{
    unsigned long currentTime = millis();

    if (currentTime - _lastTime > _interval &&
        _state == SensorMode::DONE)
    {
        _state = SensorMode::IDLE;
        _lastTime = currentTime;
    }

    switch (_state)
    {
    case SensorMode::IDLE:
        idle();
        break;

    case SensorMode::MEASURING:
        if (measure())
        {
            Processing::updateCisterna(_distance);
            gSystemState.cisterna.SensorState = _sensorState;

            _state = SensorMode::DONE;
        }
        break;

    case SensorMode::DONE:
        break;
    }
}

void Sensor::reset()
{
    _state = SensorMode::IDLE;
}

float Sensor::getDistance()
{
    return _distance;
}

bool Sensor::sensorState()
{
    return _sensorState;
}

SensorMode Sensor::state()
{
    return _state;
}