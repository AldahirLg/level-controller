#include <Arduino.h>
#include <lvgl.h>
#include "ui/ui.h"


extern "C" void action_nav_home(lv_event_t *e) {
    Serial.println("CLICK: parametros");
    loadScreen(SCREEN_ID_HOME);
}