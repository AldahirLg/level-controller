#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include "system_state/system_state.h"
#include "processing/processing.h"

class MqttParser
{
public:
    void handle(
        const String &topic,
        const String &payload);

private:
    void parseMedidor(const JsonDocument &doc);
    void parseConfigState(const JsonDocument &doc);
    void parseCommand(const JsonDocument &doc);
};