#include <unity.h>

#include "control/control.h"
#include "../test/fake_pump.h"

// ============================================================
// SETUP
// ============================================================

void setUp(void)
{
    gSystemConfig = SystemConfig{};
    gSystemState = SystemState{};
}

void tearDown(void)
{
}

// ============================================================
// AUTOMATIC MODE - LEVEL CONTROL
// ============================================================

void test_low_level_enciende_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 50;
    gSystemConfig.tinaco.levelHigh = 60;
    gSystemConfig.cisterna.minLevel = 20;

    // Sistema funcionando correctamente
    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = true;
    gSystemState.cisterna.SensorState = true;

    gSystemState.tinaco.levelPercent = 40;
    gSystemState.cisterna.levelPercent = 100;

    control.loop();

    TEST_ASSERT_TRUE(pump.isOn);
    TEST_ASSERT_TRUE(gSystemState.bomba.isOn);
}

void test_high_level_apaga_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 50;
    gSystemConfig.tinaco.levelHigh = 60;
    gSystemConfig.cisterna.minLevel = 20;

    // Sistema funcionando correctamente
    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = true;
    gSystemState.cisterna.SensorState = true;

    gSystemState.tinaco.levelPercent = 65;
    gSystemState.cisterna.levelPercent = 100;

    // Simulamos bomba encendida
    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);
}

// ============================================================
// AUTOMATIC MODE - DEADBAND / HYSTERESIS
// ============================================================

void test_deadband_mantiene_estado_previo(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 50;
    gSystemConfig.tinaco.levelHigh = 60;
    gSystemConfig.cisterna.minLevel = 20;

    // Sistema funcionando correctamente
    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = true;
    gSystemState.cisterna.SensorState = true;

    gSystemState.cisterna.levelPercent = 100;

    // Nivel bajo -> ENCIENDE
    gSystemState.tinaco.levelPercent = 40;

    control.loop();

    TEST_ASSERT_TRUE(pump.isOn);
    TEST_ASSERT_TRUE(gSystemState.bomba.isOn);

    // Banda muerta -> mantiene estado
    gSystemState.tinaco.levelPercent = 55;

    control.loop();

    TEST_ASSERT_TRUE(pump.isOn);
    TEST_ASSERT_TRUE(gSystemState.bomba.isOn);
}

// ============================================================
// AUTOMATIC MODE - CISTERNA
// ============================================================

void test_cisterna_baja_tiene_prioridad(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 50;
    gSystemConfig.tinaco.levelHigh = 60;
    gSystemConfig.cisterna.minLevel = 20;

    // Sistema funcionando correctamente
    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = true;
    gSystemState.cisterna.SensorState = true;

    // Tinaco pide bomba
    gSystemState.tinaco.levelPercent = 30;

    // Pero cisterna está vacía
    gSystemState.cisterna.levelPercent = 5;

    // Simulamos bomba encendida
    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    // Protección dry-run
    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);
}

// ============================================================
// ERROR - SENSOR TINACO
// ============================================================

void test_error_sensor_tinaco_apaga_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 20;
    gSystemConfig.tinaco.levelHigh = 80;
    gSystemConfig.cisterna.minLevel = 20;

    gSystemState.cisterna.SensorState = true;
    gSystemState.cisterna.levelPercent = 100;

    gSystemState.tinaco.sensorState = false;
    gSystemState.tinaco.ConnectionState = true;

    // Probamos con nivel bajo.
    // Normalmente pediría ENCENDER.
    gSystemState.tinaco.levelPercent = 10;

    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    // El error debe ganar al nivel
    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);

    // Según tu implementación actual:
    TEST_ASSERT_EQUAL(
        ControlMode::MANUAL,
        gSystemConfig.control_mode);
}

// ============================================================
// ERROR - SENSOR CISTERNA
// ============================================================

void test_error_sensor_cisterna_apaga_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 20;
    gSystemConfig.tinaco.levelHigh = 80;
    gSystemConfig.cisterna.minLevel = 20;

    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = true;

    gSystemState.cisterna.SensorState = false;
    gSystemState.cisterna.levelPercent = 100;

    // Tinaco bajo -> normalmente pediría ENCENDER
    gSystemState.tinaco.levelPercent = 10;

    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    // El error del sensor debe ganar
    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);

    TEST_ASSERT_EQUAL(
        ControlMode::MANUAL,
        gSystemConfig.control_mode);
}

// ============================================================
// ERROR - CONEXION TINACO
// ============================================================

void test_error_conexion_tinaco_apaga_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 20;
    gSystemConfig.tinaco.levelHigh = 80;
    gSystemConfig.cisterna.minLevel = 20;

    gSystemState.tinaco.sensorState = true;
    gSystemState.tinaco.ConnectionState = false;

    gSystemState.cisterna.SensorState = true;
    gSystemState.cisterna.levelPercent = 100;

    // Nivel bajo -> normalmente pediría ENCENDER
    gSystemState.tinaco.levelPercent = 10;

    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    // Error de conexión gana al nivel
    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);

    // Según tu implementación actual
    TEST_ASSERT_EQUAL(
        ControlMode::MANUAL,
        gSystemConfig.control_mode);
}

// ============================================================
// ERROR PRIORITY - HIGH LEVEL
// ============================================================

void test_error_sensor_gana_a_nivel_alto(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTO;

    gSystemConfig.tinaco.levelLow = 20;
    gSystemConfig.tinaco.levelHigh = 80;
    gSystemConfig.cisterna.minLevel = 20;

    gSystemState.tinaco.levelPercent = 90;
    gSystemState.tinaco.sensorState = false;
    gSystemState.tinaco.ConnectionState = true;

    gSystemState.cisterna.levelPercent = 100;
    gSystemState.cisterna.SensorState = true;

    pump.on();
    gSystemState.bomba.isOn = true;

    control.loop();

    // Aunque 90% normalmente sería HIGH_LEVEL,
    // el error del sensor tiene prioridad.
    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);

    TEST_ASSERT_EQUAL(
        ControlMode::MANUAL,
        gSystemConfig.control_mode);
}

// ============================================================
// MANUAL MODE
// ============================================================

void test_manual_enciende_y_apaga_directo(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::MANUAL;

    gSystemState.cisterna.levelPercent = 100;

    control.setManualPump(true);
    control.loop();

    TEST_ASSERT_TRUE(pump.isOn);
    TEST_ASSERT_TRUE(gSystemState.bomba.isOn);

    control.setManualPump(false);
    control.loop();

    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);
}

void test_manual_respeta_proteccion_cisterna(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::MANUAL;

    gSystemConfig.cisterna.minLevel = 20;

    gSystemState.cisterna.levelPercent = 5;

    control.setManualPump(true);
    control.loop();

    TEST_ASSERT_FALSE(pump.isOn);
    TEST_ASSERT_FALSE(gSystemState.bomba.isOn);
}

// ============================================================
// MAIN
// ============================================================

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    // Automatic
    RUN_TEST(test_low_level_enciende_bomba);
    RUN_TEST(test_high_level_apaga_bomba);
    RUN_TEST(test_deadband_mantiene_estado_previo);
    RUN_TEST(test_cisterna_baja_tiene_prioridad);

    // Errors
    RUN_TEST(test_error_sensor_tinaco_apaga_bomba);
    RUN_TEST(test_error_sensor_cisterna_apaga_bomba);
    RUN_TEST(test_error_conexion_tinaco_apaga_bomba);
    RUN_TEST(test_error_sensor_gana_a_nivel_alto);

    // Manual
    RUN_TEST(test_manual_enciende_y_apaga_directo);
    RUN_TEST(test_manual_respeta_proteccion_cisterna);

    return UNITY_END();
}
