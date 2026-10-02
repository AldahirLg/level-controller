#include "display.h"

#include <Arduino.h>
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// ---------------- Configuración ----------------
static constexpr uint16_t SCREEN_W = 240;
static constexpr uint16_t SCREEN_H = 320;
static constexpr uint16_t BUF_LINES = 10;

// Touch (bus SPI separado, pines del CYD)
static constexpr uint8_t XPT2046_IRQ = 36;
static constexpr uint8_t XPT2046_MOSI = 32;
static constexpr uint8_t XPT2046_MISO = 39;
static constexpr uint8_t XPT2046_CLK = 25;
static constexpr uint8_t XPT2046_CS = 33;

static constexpr int TOUCH_MIN_X = 200;
static constexpr int TOUCH_MAX_X = 3700;
static constexpr int TOUCH_MIN_Y = 240;
static constexpr int TOUCH_MAX_Y = 3800;

// ---------------- Objetos privados del módulo ----------------
static TFT_eSPI tft = TFT_eSPI();
static SPIClass touchSPI(VSPI);
static XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

static lv_display_t *lv_disp = nullptr;
static lv_indev_t *lv_touch = nullptr;

// *2 por RGB565 (16 bits)
static uint8_t draw_buf[SCREEN_W * BUF_LINES * 2] __attribute__((aligned(4)));

// ---------------- Callbacks de LVGL ----------------
static void disp_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)px_map, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp);
}

static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
        TS_Point p = touchscreen.getPoint();

        int16_t x = map(p.x, TOUCH_MIN_X, TOUCH_MAX_X, 0, SCREEN_W);
        int16_t y = map(p.y, TOUCH_MIN_Y, TOUCH_MAX_Y, 0, SCREEN_H);

        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = constrain(x, 0, SCREEN_W - 1);
        data->point.y = constrain(y, 0, SCREEN_H - 1);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static uint32_t tick_cb() { return millis(); }

// ---------------- API pública ----------------
void display_init()
{
    // Pantalla
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Touch
    touchSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchSPI);
    touchscreen.setRotation(2);

    // LVGL
    lv_init();
    lv_tick_set_cb(tick_cb); // LVGL 9 lleva el tick solo, ya no hace falta lv_tick_inc()

    lv_disp = lv_display_create(SCREEN_W, SCREEN_H);
    lv_display_set_flush_cb(lv_disp, disp_flush_cb);
    lv_display_set_buffers(lv_disp, draw_buf, nullptr, sizeof(draw_buf),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_touch = lv_indev_create();
    lv_indev_set_type(lv_touch, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(lv_touch, touch_read_cb);
}

void display_update()
{
    lv_timer_handler();
}