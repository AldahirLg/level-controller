#include <unity.h>
#include "processing/processing.h"

void setUp(void)
{
    gSystemConfig = SystemConfig{};
    gSystemState = SystemState{};
    gSystemConfig.tinaco.height_cm = 100;
    gSystemConfig.cisterna.height_cm = 100;
}

void tearDown(void)
{
}

void test_distanceToPercent_configuracion_invalida(void)
{
    int percent = Processing::distanceToPercent(
        50,
        0,
        0);

    TEST_ASSERT_EQUAL(-1, percent);
}

void test_distanceToPercent_tanque_lleno(void)
{
    // Distancia mínima = 0
    // Distancia 1 cm ≈ 99%
    int percent = Processing::distanceToPercent(
        1,
        100,
        0);

    TEST_ASSERT_EQUAL(99, percent);
}

void test_distanceToPercent_tanque_mitad(void)
{
    int percent = Processing::distanceToPercent(
        50,
        100,
        0);

    TEST_ASSERT_EQUAL(50, percent);
}

void test_distanceToPercent_tanque_vacio(void)
{
    int percent = Processing::distanceToPercent(
        100,
        100,
        0);

    TEST_ASSERT_EQUAL(0, percent);
}

void test_distanceToPercent_distancia_mayor_altura(void)
{
    int percent = Processing::distanceToPercent(
        150,
        100,
        0);

    TEST_ASSERT_EQUAL(0, percent);
}

void test_distanceToPercent_cisterna_minima(void)
{
    // 30 cm = 100%
    int percent = Processing::distanceToPercent(
        30,
        100,
        30);

    TEST_ASSERT_EQUAL(100, percent);
}

void test_distanceToPercent_cisterna_menor_minima(void)
{
    // Menor a 30 cm también se considera 100%
    int percent = Processing::distanceToPercent(
        20,
        100,
        30);

    TEST_ASSERT_EQUAL(100, percent);
}

void test_distanceToPercent_cisterna_mitad(void)
{
    // Rango real:
    // 30 cm = 100%
    // 100 cm = 0%
    //
    // 65 cm está exactamente a la mitad.
    int percent = Processing::distanceToPercent(
        65,
        100,
        30);

    TEST_ASSERT_EQUAL(50, percent);
}

void test_distanceToPercent_cisterna_vacia(void)
{
    int percent = Processing::distanceToPercent(
        100,
        100,
        30);

    TEST_ASSERT_EQUAL(0, percent);
}

void test_distanceToPercent_cisterna_mayor_altura(void)
{
    int percent = Processing::distanceToPercent(
        120,
        100,
        30);

    TEST_ASSERT_EQUAL(0, percent);
}

void test_updateTinaco_actualiza_porcentaje(void)
{
    gSystemState.tinaco.level_percent = 0;

    Processing::updateTinaco(50);

    TEST_ASSERT_EQUAL(
        50,
        gSystemState.tinaco.level_percent);
}

void test_updateTinaco_distancia_cero_no_modifica_estado(void)
{
    gSystemState.tinaco.level_percent = 75;

    Processing::updateTinaco(0);

    TEST_ASSERT_EQUAL(
        75,
        gSystemState.tinaco.level_percent);
}

void test_updateTinaco_distancia_mayor_altura_da_cero(void)
{
    Processing::updateTinaco(150);

    TEST_ASSERT_EQUAL(
        0,
        gSystemState.tinaco.level_percent);
}

void test_updateCisterna_actualiza_porcentaje(void)
{
    Processing::updateCisterna(50);

    TEST_ASSERT_EQUAL(
        71,
        gSystemState.cisterna.level_percent);

    TEST_ASSERT_TRUE(
        gSystemState.cisterna.sensor_ok);
}

void test_updateCisterna_30cm_es_100_por_ciento(void)
{
    Processing::updateCisterna(30);

    TEST_ASSERT_EQUAL(
        100,
        gSystemState.cisterna.level_percent);

    TEST_ASSERT_TRUE(
        gSystemState.cisterna.sensor_ok);
}

void test_updateCisterna_menor_a_30cm_es_100_por_ciento(void)
{
    Processing::updateCisterna(20);

    TEST_ASSERT_EQUAL(
        100,
        gSystemState.cisterna.level_percent);

    TEST_ASSERT_TRUE(
        gSystemState.cisterna.sensor_ok);
}

void test_updateCisterna_distancia_cero_no_modifica_estado(void)
{
    gSystemState.cisterna.level_percent = 60;
    gSystemState.cisterna.sensor_ok = true;

    Processing::updateCisterna(0);

    TEST_ASSERT_EQUAL(
        60,
        gSystemState.cisterna.level_percent);

    TEST_ASSERT_TRUE(
        gSystemState.cisterna.sensor_ok);
}

void test_updateCisterna_tanque_vacio(void)
{
    Processing::updateCisterna(100);

    TEST_ASSERT_EQUAL(
        0,
        gSystemState.cisterna.level_percent);

    TEST_ASSERT_TRUE(
        gSystemState.cisterna.sensor_ok);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    // distanceToPercent
    RUN_TEST(test_distanceToPercent_configuracion_invalida);
    RUN_TEST(test_distanceToPercent_tanque_lleno);
    RUN_TEST(test_distanceToPercent_tanque_mitad);
    RUN_TEST(test_distanceToPercent_tanque_vacio);
    RUN_TEST(test_distanceToPercent_distancia_mayor_altura);

    // Cisterna
    RUN_TEST(test_distanceToPercent_cisterna_minima);
    RUN_TEST(test_distanceToPercent_cisterna_menor_minima);
    RUN_TEST(test_distanceToPercent_cisterna_mitad);
    RUN_TEST(test_distanceToPercent_cisterna_vacia);
    RUN_TEST(test_distanceToPercent_cisterna_mayor_altura);

    // Tinaco
    RUN_TEST(test_updateTinaco_actualiza_porcentaje);
    RUN_TEST(test_updateTinaco_distancia_cero_no_modifica_estado);
    RUN_TEST(test_updateTinaco_distancia_mayor_altura_da_cero);

    // Cisterna
    RUN_TEST(test_updateCisterna_actualiza_porcentaje);
    RUN_TEST(test_updateCisterna_30cm_es_100_por_ciento);
    RUN_TEST(test_updateCisterna_menor_a_30cm_es_100_por_ciento);
    RUN_TEST(test_updateCisterna_distancia_cero_no_modifica_estado);
    RUN_TEST(test_updateCisterna_tanque_vacio);

    return UNITY_END();
}
