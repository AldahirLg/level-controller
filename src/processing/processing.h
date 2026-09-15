#pragma once
// #include <cstdint>
#include <system_state/system_state.h>
#include <Arduino.h>
class Processing
{
public:
    static int distanceToPercent(
        uint16_t distance_cm,
        uint16_t height_cm,
        uint16_t min_distance_cm);

    static void updateTinaco(uint16_t level_percent);
    static void updateCisterna(uint16_t raw_distance_cm);
};