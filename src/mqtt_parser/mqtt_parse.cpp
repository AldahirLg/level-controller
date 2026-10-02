#include "mqtt_parse.h"

MqttParser::MqttParser(Control &control)
    : _control(control)
{
}

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

    if (!doc["medidor"].isNull())
    {
        parseMedidor(doc);
    }
    else if (!doc["parameters"].isNull())
    {
        parseConfigState(doc);
    }
    else if (!doc["pump"].isNull())
    {
        parseComand(doc);
    }
    else
    {
        Serial.println(
            "[MQTT] Tipo de mensaje desconocido");
    }
}

void MqttParser::parseMedidor(
    const JsonDocument &doc)
{
    JsonObjectConst status =
        doc["medidor"]["status"];

    if (status.isNull() ||
        !status["level"].is<int>() ||
        !status["sensorState"].is<bool>() ||
        !status["battery"].is<int>())
    {
        Serial.println(
            "[MQTT] Payload medidor invalido");

        return;
    }

    _control.notifyTinacoData();

    uint16_t distance =
        status["level"].as<uint16_t>();

    bool sensorState =
        status["sensorState"].as<bool>();

    int battery =
        status["battery"].as<int>();

    gSystemState.tinaco.sensorState =
        sensorState;

    gSystemState.tinaco.battery =
        battery;

    Processing::updateTinaco(distance);

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
    JsonObjectConst configJson =
        doc["parameters"];

    if (configJson.isNull() ||
        !configJson["levelLow"].is<int>() ||
        !configJson["levelHigh"].is<int>() ||
        !configJson["hCis"].is<int>() ||
        !configJson["hTin"].is<int>() ||
        !configJson["minCis"].is<int>())
    {
        Serial.println(
            "[MQTT] Payload config invalido");

        return;
    }

    SystemConfig config;

    config.tinaco.height_cm =
        configJson["hTin"].as<unsigned int>();

    config.tinaco.levelHigh =
        configJson["levelHigh"].as<unsigned int>();

    config.tinaco.levelLow =
        configJson["levelLow"].as<unsigned int>();

    config.cisterna.height_cm =
        configJson["hCis"].as<unsigned int>();

    config.cisterna.minLevel =
        configJson["minCis"].as<unsigned int>();

    _control.setConfig(config);

    Serial.println(
        "[MQTT] ConfigState recibido");
}

void MqttParser::parseComand(
    const JsonDocument &doc)
{
    JsonObjectConst pump =
        doc["pump"];

    if (pump.isNull())
    {
        Serial.println(
            "[MQTT] Payload command invalido");

        return;
    }

    if (!pump["mode"].isNull())
    {
        if (!pump["mode"].is<const char *>())
        {
            Serial.println(
                "[MQTT] pump.mode invalido");

            return;
        }

        const char *controlMode =
            pump["mode"];

        ControlMode mode =
            strcmp(controlMode, "AUTO") == 0
                ? ControlMode::AUTO
                : ControlMode::MANUAL;

        _control.setControlMode(mode);
    }

    if (!pump["isOn"].isNull())
    {
        if (!pump["isOn"].is<bool>())
        {
            Serial.println(
                "[MQTT] pump.isOn invalido");

            return;
        }

        bool pumpState =
            pump["isOn"].as<bool>();

        _control.setManualPump(pumpState);
    }

    Serial.println(
        "[MQTT] Command recibido");
}
