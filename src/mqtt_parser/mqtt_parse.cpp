#include "mqtt_parse.h"

void MqttParser::handle(
    const String &topic,
    const String &payload)
{
    JsonDocument doc;

    DeserializationError error =
        deserializeJson(doc, payload);

    if (error)
    {
        Serial.printf(
            "[MQTT] Error parseando JSON: %s\n",
            error.c_str());

        return;
    }
    parseMedidor(doc);

    /*if (topic.startsWith("medidor/"))
    {
        parseMedidor(doc);
    }
    else if (topic.startsWith("configState/"))
    {
        parseConfigState(doc);
    }
    else if (topic.startsWith("command/"))
    {
        parseCommand(doc);
    }
    else
    {
        Serial.printf(
            "[MQTT] Topic no reconocido: %s\n",
            topic.c_str());
    }*/
}

void MqttParser::parseMedidor(const JsonDocument &doc)
{
    if (!doc["level"].is<int>() ||
        !doc["sensorState"].is<bool>() ||
        !doc["battery"].is<int>())
    {
        Serial.println(
            "[MQTT] Payload medidor invalido");

        return;
    }

    uint16_t distance =
        doc["level"].as<uint16_t>();

    bool sensorState =
        doc["sensorState"].as<bool>();

    int battery =
        doc["battery"].as<int>();

    gSystemState.tinaco.sensorState =
        sensorState;

    gSystemState.tinaco.battery =
        battery;

    if (sensorState)
    {
        Processing::updateTinaco(distance);
    }

    Serial.printf(
        "[MQTT] Tinaco -> "
        "distance: %u cm, "
        "level: %d%%, "
        "sensor: %s, "
        "battery: %d%%\n",
        distance,
        gSystemState.tinaco.levelPercent,
        sensorState ? "OK" : "ERROR",
        battery);
}

void MqttParser::parseConfigState(
    const JsonDocument &doc)
{
    Serial.println(
        "[MQTT] ConfigState recibido");
}

void MqttParser::parseCommand(
    const JsonDocument &doc)
{

    Serial.println(
        "[MQTT] Command recibido");
}