#include <Arduino.h>
#include "mqtt/mqtt_manager.h"
#include "system_state/system_state.h"
#include "processing/processing.h"
#include <ArduinoJson.h>
#include "mqtt_parser/mqtt_parse.h"
#include "mqtt_parser/status_publisher.h"
#include "wifi/wifi_manager.h"
#include "ble/ble_manager.h"
#include "claim/claim.h"
#include "pump/pump.h"
#include "sensor/sensor.h"

enum State
{
  PROVISIONING,
  CLAIM,
  NORMAL,
  DISCONNECT,
};

Pump pump(5, false);
Sensor sensor(14, 13);
MqttManager mqttManager;
WiFiManager wifiManager;
BleManager bleManager(wifiManager);
Claim claimHandler(wifiManager, mqttManager);
Control control(pump, mqttManager);

MqttParser mqttParser(control);
StatusPublisher statusPublisher(mqttManager);

State state;
String deviceId;
uint8_t resetPin = 4;

void resetCredentials()
{
  if (digitalRead(resetPin) == LOW)
  {
    wifiManager.resetSettings();
    delay(1000);
    ESP.restart();
  }
}

void handleMqttMessage(String &topic, String &payload)
{
  Serial.printf(
      "[MQTT] Mensaje en [%s]: %s\n",
      topic.c_str(),
      payload.c_str());

  mqttParser.handle(topic, payload);
}

void setup()
{
  Serial.begin(115200);
  wifiManager.begin();
  if (wifiManager.getStatus() == WiFiManagerStatus::CONNECTED)
  {
    deviceId = wifiManager.getDeviceUid();
    mqttManager.setDeviceId(deviceId);
    mqttManager.setMessageCallback(handleMqttMessage);
    mqttManager.begin();
    state = State::NORMAL;
  }
  else if (wifiManager.getStatus() == WiFiManagerStatus::DISCONNECTED)
  {
    state = State::DISCONNECT;
  }
  else if (wifiManager.getStatus() == WiFiManagerStatus::PROVISIONING)
  {
    state = State::PROVISIONING;
    bleManager.begin();
  }
}

void normal()
{
  wifiManager.loop();
  mqttManager.loop(wifiManager.isConnected());
  statusPublisher.loop();
  sensor.loop();
  control.loop();
}

void loop()
{
  switch (state)
  {
  case State::PROVISIONING:
    bleManager.loop();
    wifiManager.loop();
    if (wifiManager.getStatus() == WiFiManagerStatus::CONNECTED)
      state = State::CLAIM;
    break;
  case State::CLAIM:
    bleManager.loop();
    wifiManager.loop();
    claimHandler.loop();
    mqttManager.loop(wifiManager.isConnected());
    if (claimHandler.isDone())
    {
      claimHandler.reset();
      state = State::NORMAL;
    }
    break;
  case State::NORMAL:
    normal();
    break;
  default:
    break;
  }
}