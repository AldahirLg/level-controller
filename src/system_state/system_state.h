#pragma once
// #include <Arduino.h>
#include <cstdint>

enum ControlMode
{
    AUTO,
    MANUAL
};

struct TinacoState
{
    int levelPercent{-1};
    uint8_t battery{0};
    bool sensorState{false};
    bool ConnectionState{false};
    uint32_t lastUpdateMs{0};
};

struct CisternaState
{
    int levelPercent{-1};
    bool SensorState{false};
};

struct TinacoConfig
{
    unsigned int height_cm{0};
    unsigned int levelLow{0};
    unsigned int levelHigh{0};
};

struct CisternaConfig
{
    unsigned int height_cm{0};
    unsigned int minLevel{0};
};

struct BombaState
{
    ControlMode controlMode{ControlMode::MANUAL};
    bool isOn{false};
};

struct SystemState
{
    TinacoState tinaco{};
    CisternaState cisterna{};
    BombaState bomba{};
};

struct SystemConfig
{
    TinacoConfig tinaco{};
    CisternaConfig cisterna{};
};

extern SystemConfig gSystemConfig;
extern SystemState gSystemState;