#include <unity.h>
#include "control/control.h"
#include "../test/fake_pump.h"

void setUp(void)
{
    gSystemConfig = SystemConfig{};
    gSystemState = SystemState{};
}
void tearDown(void)
{
}

void test_low_level_enciende_bomba(void)
{
    FakePump pump;
    Control control(pump);

    gSystemConfig.control_mode = ControlMode::AUTOMATIC;
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

    gSystemConfig.control_mode = ControlMode::AUTOMATIC;
    gSystemState.tinaco.levelPercent = 65; // >= 60 (high)
    gSystemState.cisterna.levelPercent = 100;

    control.loop();

    TEST_ASSERT_FALSE(pump.isOn);
}

void test_deadband_mantiene_estado_previo(void)
{
    FakePump pump;
    Control control(pump);
    gSystemConfig.control_mode = ControlMode::AUTOMATIC;
    gSystemState.cisterna.levelPercent = 100;

    // Primero forzamos encendido bajando el nivel
    gSystemState.tinaco.levelPercent = 40;
    control.loop();
    TEST_ASSERT_TRUE(pump.isOn);

    // Ahora subimos a la banda muerta (50-59): no debe apagarse
    gSystemState.tinaco.levelPercent = 55;
    control.loop();
    TEST_ASSERT_TRUE(pump.isOn); // sigue encendida, histéresis funcionando
}

void test_cisterna_baja_tiene_prioridad(void)
{
    FakePump pump;
    Control control(pump);
    gSystemConfig.control_mode = ControlMode::AUTOMATIC;

    gSystemState.tinaco.levelPercent = 30;  // pediría encender
    gSystemState.cisterna.levelPercent = 5; // pero cisterna seca

    control.loop();

    TEST_ASSERT_FALSE(pump.isOn); // protección dry-run gana
}

void test_manual_enciende_y_apaga_directo(void)
{
    FakePump pump;
    Control control(pump);
    gSystemConfig.control_mode = ControlMode::MANUAL;
    gSystemState.cisterna.levelPercent = 100;

    control.setManualPump(true);
    control.loop();
    TEST_ASSERT_TRUE(pump.isOn);

    control.setManualPump(false);
    control.loop();
    TEST_ASSERT_FALSE(pump.isOn);
}

void test_manual_respeta_proteccion_cisterna(void)
{
    FakePump pump;
    Control control(pump);
    gSystemConfig.control_mode = ControlMode::MANUAL;
    gSystemState.cisterna.levelPercent = 5; // baja

    control.setManualPump(true);
    control.loop();

    TEST_ASSERT_FALSE(pump.isOn); // no debería encender aunque sea manual
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_low_level_enciende_bomba);
    RUN_TEST(test_high_level_apaga_bomba);
    RUN_TEST(test_deadband_mantiene_estado_previo);
    RUN_TEST(test_cisterna_baja_tiene_prioridad);
    RUN_TEST(test_manual_enciende_y_apaga_directo);
    RUN_TEST(test_manual_respeta_proteccion_cisterna);
    return UNITY_END();
}