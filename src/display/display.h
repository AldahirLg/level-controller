#pragma once

// Inicializa TFT, touch, backlight y LVGL (display + indev).
// Llamar antes de ui_init().
void display_init();

// Avanza el tick de LVGL y procesa sus timers. Llamar en loop().
void display_update();