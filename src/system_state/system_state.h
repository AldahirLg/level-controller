#pragma once
// #include <Arduino.h>
#include <cstdint>

enum ControlMode
{
    AUTOMATIC,
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
    unsigned int height_cm{100U};
    unsigned int level_low_percent{50U};
    unsigned int level_high_percent{60U};
};

struct CisternaConfig
{
    unsigned int height_cm{100U};
    unsigned int level_low_percent{50U};
    unsigned int level_high_percent{70U};
};

struct BombaState
{
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
    ControlMode control_mode{ControlMode::MANUAL};
};

extern SystemConfig gSystemConfig;
extern SystemState gSystemState;