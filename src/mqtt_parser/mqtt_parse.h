#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include "system_state/system_state.h"
#include "processing/processing.h"
#include "control/control.h"
#include <cstring>

class MqttParser
{
public:
    MqttParser(Control &control);
    void handle(
        const String &topic,
        const String &payload);

private:
    Control &_control;
    void parseMedidor(const JsonDocument &doc);
    void parseConfigState(const JsonDocument &doc);
    void parseComand(const JsonDocument &doc);
};