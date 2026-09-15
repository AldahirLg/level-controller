#include "processing.h"

int Processing::distanceToPercent(
    uint16_t distance_cm,
    uint16_t height_cm,
    uint16_t min_distance_cm)
{
    if (height_cm == 0)
    {
        Serial.println("[PROCESSING] Error: height_cm es 0");
        return -1;
    }

    if (distance_cm <= min_distance_cm)
    {
        Serial.printf(
            "[PROCESSING] Distancia %u cm -> 100%%\n",
            distance_cm);
        return 100;
    }

    if (distance_cm >= height_cm)
    {
        Serial.printf(
            "[PROCESSING] Distancia %u cm -> 0%%\n",
            distance_cm);
        return 0;
    }

    float percent =
        (static_cast<float>(height_cm - distance_cm) /
         static_cast<float>(height_cm - min_distance_cm)) *
        100.0f;

    int result = static_cast<int>(percent);

    Serial.printf(
        "[PROCESSING] Distancia: %u cm, Altura: %u cm, Min: %u cm -> %d%%\n",
        distance_cm,
        height_cm,
        min_distance_cm,
        result);

    return result;
}

void Processing::updateTinaco(uint16_t raw_distance_cm)
{
    if (raw_distance_cm == 0)
    {
        Serial.println("[PROCESSING] Tinaco: distancia invalida (0)");
        return;
    }

    int percent = distanceToPercent(
        raw_distance_cm,
        gSystemConfig.tinaco.height_cm,
        0);

    if (percent >= 0)
    {
        gSystemState.tinaco.levelPercent = percent;

        Serial.printf(
            "[PROCESSING] Tinaco actualizado: %d%%\n",
            percent);
    }
}

void Processing::updateCisterna(uint16_t raw_distance_cm)
{
    constexpr uint16_t MIN_DISTANCE_CM = 30;

    if (raw_distance_cm == 0)
    {
        Serial.println("[PROCESSING] Cisterna: distancia invalida (0)");
        return;
    }

    int percent = distanceToPercent(
        raw_distance_cm,
        gSystemConfig.cisterna.height_cm,
        MIN_DISTANCE_CM);

    if (percent >= 0)
    {
        gSystemState.cisterna.levelPercent = percent;

        Serial.printf(
            "[PROCESSING] Cisterna actualizada: %d%%\n",
            percent);

        // gSystemState.cisterna.SensorState = true;
    }
}