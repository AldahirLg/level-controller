#pragma once
#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/ui.h"
#include "wifi/wifi_manager.h"
#include "system_state/system_state.h"
#include "control/control.h"

void init_ui_callbacks(WiFiManager &wifi, Control &control);
void init_screen_configless();
void tick_values();