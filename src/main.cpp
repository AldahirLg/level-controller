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
#include "display/display.h"
#include "ui/ui.h"
#include "ui_callbacks/ui_callbacks.h"

enum State
{
  PROVISIONING,
  CLAIM,
  NORMAL,
  DISCONNECT,
};

Pump pump(22, true);
Sensor sensor(27, 35);
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
  // Display
  pump.begin();
  display_init();
  ui_init();
  wifiManager.begin();
  if (wifiManager.getStatus() == WiFiManagerStatus::PROVISIONING)
  {
    state = State::PROVISIONING;
    bleManager.begin();
    loadScreen(SCREEN_ID_CONFIGLESS);
  }
  else
  {
    deviceId = wifiManager.getDeviceUid();
    mqttManager.setDeviceId(deviceId);
    mqttManager.setMessageCallback(handleMqttMessage);
    state = State::NORMAL;
  }
  String ssid = wifiManager.getSavedSSID();
  ssid.toCharArray(
      gSystemState.red.ssid,
      sizeof(gSystemState.red.ssid));

  gSystemState.red.connection = wifiManager.isConnected();

  init_ui_callbacks(wifiManager, control);
}

void normal()
{
  wifiManager.loop();
  mqttManager.loop(wifiManager.isConnected());
  statusPublisher.loop();
  sensor.loop();
  control.loop();
  gSystemState.red.connection = wifiManager.isConnected();
  ;
}

void loop()
{
  switch (state)
  {
  case State::PROVISIONING:
    bleManager.loop();
    wifiManager.loop();
    if (wifiManager.getStatus() == WiFiManagerStatus::CONNECTED)
    {
      bleManager.stop();
      state = State::CLAIM;
    }
    break;
  case State::CLAIM:
    wifiManager.loop();
    mqttManager.loop(wifiManager.isConnected());
    claimHandler.loop();
    if (claimHandler.isDone())
    {
      claimHandler.reset();
      state = State::NORMAL;
    }
    break;
  case State::NORMAL:
    normal();
    tick_values();
    break;
  default:
    break;
  }
  ui_tick();
  display_update();
  delay(5);
}