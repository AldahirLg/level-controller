#include "ui_callbacks.h"

static WiFiManager *wifiManager = nullptr;
static Control *sysControl = nullptr;

static void set_parameters_enabled(bool enabled)
{
    if (enabled)
    {
        lv_obj_remove_state(objects.sdr_height_tin, LV_STATE_DISABLED);
        lv_obj_remove_state(objects.sdr_height_cis, LV_STATE_DISABLED);
        lv_obj_remove_state(objects.sdr_level_high, LV_STATE_DISABLED);
        lv_obj_remove_state(objects.sdr_level_low, LV_STATE_DISABLED);
        lv_obj_remove_state(objects.sdr_cis_level_min, LV_STATE_DISABLED);
    }
    else
    {
        lv_obj_add_state(objects.sdr_height_tin, LV_STATE_DISABLED);
        lv_obj_add_state(objects.sdr_height_cis, LV_STATE_DISABLED);
        lv_obj_add_state(objects.sdr_level_high, LV_STATE_DISABLED);
        lv_obj_add_state(objects.sdr_level_low, LV_STATE_DISABLED);
        lv_obj_add_state(objects.sdr_cis_level_min, LV_STATE_DISABLED);
    }
}

static bool validate_parameters()
{
    int heightTin = lv_slider_get_value(objects.sdr_height_tin);
    int heightCis = lv_slider_get_value(objects.sdr_height_cis);
    int levelHigh = lv_slider_get_value(objects.sdr_level_high);
    int levelLow = lv_slider_get_value(objects.sdr_level_low);
    int minCis = lv_slider_get_value(objects.sdr_cis_level_min);
    // Altura del tinaco
    if (heightTin <= 60)
    {
        lv_label_set_text(
            objects.lbl_msg_param,
            "Altura del tinaco debe ser mayor a 60");

        lv_obj_add_state(objects.lbl_msg_param, LV_STATE_CHECKED);
        lv_obj_add_state(objects.panel_msg_param, LV_STATE_CHECKED);
        return false;
    }

    // Altura de la cisterna
    if (heightCis <= 60)
    {
        lv_label_set_text(
            objects.lbl_msg_param,
            "Altura de cisterna debe ser mayor a 60");

        lv_obj_add_state(objects.lbl_msg_param, LV_STATE_CHECKED);
        lv_obj_add_state(objects.panel_msg_param, LV_STATE_CHECKED);
        return false;
    }

    // Nivel alto debe superar al nivel bajo por al menos 20
    if (levelHigh < levelLow + 20 || levelHigh == levelLow)
    {
        lv_label_set_text(
            objects.lbl_msg_param,
            "Nivel alto debe ser 20 mayor que nivel bajo");

        lv_obj_add_state(objects.lbl_msg_param, LV_STATE_CHECKED);
        lv_obj_add_state(objects.panel_msg_param, LV_STATE_CHECKED);
        return false;
    }

    // Nivel bajo debe ser mayor a 10
    if (levelLow < 10)
    {
        lv_label_set_text(
            objects.lbl_msg_param,
            "Nivel bajo debe ser mayor a 10");

        lv_obj_add_state(objects.lbl_msg_param, LV_STATE_CHECKED);
        lv_obj_add_state(objects.panel_msg_param, LV_STATE_CHECKED);
        return false;
    }
    SystemConfig config;
    config.tinaco.height_cm = heightTin;
    config.tinaco.levelHigh = levelHigh;
    config.tinaco.levelLow = levelLow;
    config.cisterna.height_cm = heightCis;
    config.cisterna.minLevel = minCis;
    sysControl->setConfig(config);
    lv_label_set_text(objects.lbl_msg_param, "");
    lv_obj_remove_state(objects.lbl_msg_param, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.panel_msg_param, LV_STATE_CHECKED);
    return true;
}

static void init_tab_view(void)
{
    lv_obj_t *tab_bar = lv_tabview_get_tab_bar(objects.tab_view);
    lv_obj_set_style_bg_color(tab_bar, lv_color_hex(0x172033), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tab_bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(tab_bar, true, LV_PART_MAIN);
    lv_obj_set_style_text_color(tab_bar, lv_color_hex(0xE2E8F0),
                                LV_PART_ITEMS | LV_STATE_DEFAULT);

    static const char *icons[] = {
        LV_SYMBOL_HOME,
        LV_SYMBOL_SETTINGS,
        LV_SYMBOL_LIST,
    };

    uint32_t n = lv_tabview_get_tab_count(objects.tab_view);
    for (uint32_t i = 0; i < n; i++)
    {
        lv_obj_t *btn = lv_obj_get_child(tab_bar, i);
        if (!btn)
            continue;

        lv_obj_t *label = lv_obj_get_child(btn, 0);
        if (!label)
            continue;
        if (i < sizeof(icons) / sizeof(icons[0]))
        {
            lv_label_set_text(label, icons[i]);
        }

        lv_obj_set_style_text_color(label, lv_color_hex(0xB6BECE), LV_PART_MAIN);
        lv_obj_set_style_text_color(label, lv_color_hex(0x38BDF8),
                                    LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN);
    }
}

void init_ui_callbacks(WiFiManager &wifi, Control &control)
{

    // Modo Manual
    wifiManager = &wifi;
    sysControl = &control;
    init_tab_view();
    lv_buttonmatrix_set_selected_button(objects.matrix_mode, 0);
    lv_buttonmatrix_set_button_ctrl(
        objects.matrix_mode,
        0,
        LV_BUTTONMATRIX_CTRL_CHECKED);
    lv_label_set_text(objects.lbl_ssid_wifi, gSystemState.red.ssid);
    set_parameters_enabled(false);
}

extern "C" void action_call_modes(lv_event_t *e)
{
    lv_obj_t *btnm = (lv_obj_t *)lv_event_get_target(e);
    uint32_t selected = lv_buttonmatrix_get_selected_button(btnm);

    if (selected == 0)
    {
        sysControl->setControlMode(ControlMode::MANUAL);
    }
    else if (selected == 1)
    {
        sysControl->setControlMode(ControlMode::AUTO);
    }
}

extern "C" void action_call_pump(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *sw = (lv_obj_t *)lv_event_get_target(e);
    bool wantOn = lv_obj_has_state(sw, LV_STATE_CHECKED);
    if (gSystemState.bomba.controlMode != MANUAL)
    {
        if (gSystemState.bomba.isOn)
            lv_obj_add_state(sw, LV_STATE_CHECKED);
        else
            lv_obj_remove_state(sw, LV_STATE_CHECKED);
        return;
    }

    Serial.printf("Bomba manual: %s\n", wantOn ? "ON" : "OFF");
    sysControl->setManualPump(wantOn);
}

extern "C" void action_call_param_srd(lv_event_t *e)
{
    lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);

    int value = lv_slider_get_value(slider);

    if (slider == objects.sdr_height_tin)
    {
        Serial.printf("HEIGHT TIN: %d\n", value);
        lv_label_set_text_fmt(objects.lbl_sdr_height_tin, "%d", value);
    }
    else if (slider == objects.sdr_height_cis)
    {
        Serial.printf("HEIGHT CIS: %d\n", value);
        lv_label_set_text_fmt(objects.lbl_sdr_height_cis, "%d", value);
    }
    else if (slider == objects.sdr_level_high)
    {
        Serial.printf("LEVEL HIGH: %d\n", value);
        lv_label_set_text_fmt(objects.lbl_sdr_level_high, "%d", value);
    }
    else if (slider == objects.sdr_level_low)
    {
        Serial.printf("LEVEL LOW: %d\n", value);
        lv_label_set_text_fmt(objects.lbl_sdr_level_low, "%d", value);
    }
    else if (slider == objects.sdr_cis_level_min)
    {
        Serial.printf("MIN CIS: %d\n", value);
        lv_label_set_text_fmt(objects.lbl_sdr_min_cis, "%d", value);
    }
}

extern "C" void action_call_save_values_param(lv_event_t *e)
{
    lv_obj_t *toggle = (lv_obj_t *)lv_event_get_target(e);
    bool editing = lv_obj_has_state(toggle, LV_STATE_CHECKED);

    if (editing)
    {
        lv_label_set_text(objects.lbl_editar, "Guardar");
        lv_obj_add_state(objects.lbl_editar, LV_STATE_CHECKED);
        set_parameters_enabled(true);
        return;
    }

    // Intento de guardar
    if (!validate_parameters())
    {
        Serial.println("ERROR: Parámetros inválidos");
        lv_obj_add_state(toggle, LV_STATE_CHECKED); // se queda en edición
        return;
    }

    Serial.println("Parámetros válidos");
    lv_label_set_text(objects.lbl_editar, "Editar");
    lv_obj_remove_state(objects.lbl_editar, LV_STATE_CHECKED);
    set_parameters_enabled(false);
}

void init_screen_configless()
{
    loadScreen(SCREEN_ID_CONFIGLESS);
}

extern "C" void action_call_reset(lv_event_t *e)
{
    wifiManager->resetSettings();
    delay(100);
    ESP.restart();
}

extern "C" void action_call_restart(lv_event_t *e)
{
    delay(500);
    ESP.restart();
}

void tick_values()
{
    static bool firstUpdate = true;
    static int lastTinLevel = -1;
    static int lastTinBattery = -1;
    static bool lastTinSensorState = false;
    static bool lastTinConnectionState = false;
    static int lastCisLevel = -1;
    static bool lastCisSensorState = false;

    static unsigned int lastTinHeight = 0;
    static unsigned int lastTinLevelHigh = 0;
    static unsigned int lastTinLevelLow = 0;
    static unsigned int lastCisHeight = 0;
    static unsigned int lastCisMinLevel = 0;

    static ControlMode lastControlMode = MANUAL;
    static bool lastPumpState = false;

    static bool lastWifiState = false;

    // Tinaco
    const int tinLevel = gSystemState.tinaco.levelPercent;
    const int tinBattery = gSystemState.tinaco.battery;
    const bool tinSensor = gSystemState.tinaco.sensorState;
    const bool tinConnection = gSystemState.tinaco.ConnectionState;

    if (firstUpdate || tinLevel != lastTinLevel)
    {
        lastTinLevel = tinLevel;
        lv_bar_set_value(objects.bar_tin, tinLevel, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.lbl_tin_level, "%d", tinLevel);
    }

    if (firstUpdate || tinBattery != lastTinBattery)
    {
        lastTinBattery = tinBattery;
        lv_label_set_text_fmt(objects.lbl_tin_bat, "%d", tinBattery);

        if (tinBattery < 40)
            lv_obj_add_state(objects.lbl_tin_bat, LV_STATE_CHECKED);
        else
            lv_obj_remove_state(objects.lbl_tin_bat, LV_STATE_CHECKED);
    }

    if (firstUpdate || tinSensor != lastTinSensorState)
    {
        lastTinSensorState = tinSensor;

        if (tinSensor)
        {
            lv_label_set_text(objects.lbl_tin_sensor, "OK");
            lv_obj_remove_state(objects.lbl_tin_sensor, LV_STATE_CHECKED);
        }
        else
        {
            lv_label_set_text(objects.lbl_tin_sensor, "Falla");
            lv_obj_add_state(objects.lbl_tin_sensor, LV_STATE_CHECKED);
        }
    }

    if (firstUpdate || tinConnection != lastTinConnectionState)
    {
        lastTinConnectionState = tinConnection;

        if (tinConnection)
        {
            lv_label_set_text(objects.lbl_tin_con, "OK");
            lv_obj_remove_state(objects.lbl_tin_con, LV_STATE_CHECKED);
        }
        else
        {
            lv_label_set_text(objects.lbl_tin_con, "Falla");
            lv_obj_add_state(objects.lbl_tin_con, LV_STATE_CHECKED);
        }
    }

    // Cisterna
    const int cisLevel = gSystemState.cisterna.levelPercent;
    const bool cisSensor = gSystemState.cisterna.SensorState;

    if (firstUpdate || cisLevel != lastCisLevel)
    {
        lastCisLevel = cisLevel;
        lv_bar_set_value(objects.bar_cis, cisLevel, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.lbl_cis_level, "%d", cisLevel);
    }

    if (firstUpdate || cisSensor != lastCisSensorState)
    {
        lastCisSensorState = cisSensor;

        if (cisSensor)
        {
            lv_label_set_text(objects.lbl_cis_sensor, "OK");
            lv_obj_remove_state(objects.lbl_cis_sensor, LV_STATE_CHECKED);
        }
        else
        {
            lv_label_set_text(objects.lbl_cis_sensor, "Falla");
            lv_obj_add_state(objects.lbl_cis_sensor, LV_STATE_CHECKED);
        }
    }

    // Configuración
    const bool editing = lv_obj_has_state(objects.lbl_editar, LV_STATE_CHECKED);

    if (!editing)
    {
        const unsigned int tinHeight = gSystemConfig.tinaco.height_cm;
        const unsigned int tinLevelHigh = gSystemConfig.tinaco.levelHigh;
        const unsigned int tinLevelLow = gSystemConfig.tinaco.levelLow;
        const unsigned int cisHeight = gSystemConfig.cisterna.height_cm;
        const unsigned int cisMinLevel = gSystemConfig.cisterna.minLevel;

        if (firstUpdate || tinHeight != lastTinHeight)
        {
            lastTinHeight = tinHeight;
            lv_slider_set_value(objects.sdr_height_tin, tinHeight, LV_ANIM_OFF);
            lv_label_set_text_fmt(objects.lbl_sdr_height_tin, "%u", tinHeight);
        }

        if (firstUpdate || tinLevelHigh != lastTinLevelHigh)
        {
            lastTinLevelHigh = tinLevelHigh;
            lv_slider_set_value(objects.sdr_level_high, tinLevelHigh, LV_ANIM_OFF);
            lv_label_set_text_fmt(objects.lbl_sdr_level_high, "%u", tinLevelHigh);
        }

        if (firstUpdate || tinLevelLow != lastTinLevelLow)
        {
            lastTinLevelLow = tinLevelLow;
            lv_slider_set_value(objects.sdr_level_low, tinLevelLow, LV_ANIM_OFF);
            lv_label_set_text_fmt(objects.lbl_sdr_level_low, "%u", tinLevelLow);
        }

        if (firstUpdate || cisHeight != lastCisHeight)
        {
            lastCisHeight = cisHeight;
            lv_slider_set_value(objects.sdr_height_cis, cisHeight, LV_ANIM_OFF);
            lv_label_set_text_fmt(objects.lbl_sdr_height_cis, "%u", cisHeight);
        }

        if (firstUpdate || cisMinLevel != lastCisMinLevel)
        {
            lastCisMinLevel = cisMinLevel;
            lv_slider_set_value(objects.sdr_cis_level_min, cisMinLevel, LV_ANIM_OFF);
            lv_label_set_text_fmt(objects.lbl_sdr_min_cis, "%u", cisMinLevel);
        }
    }

    // Bomba
    const ControlMode controlMode = gSystemState.bomba.controlMode;
    const bool pumpState = gSystemState.bomba.isOn;

    if (firstUpdate || controlMode != lastControlMode)
    {
        lastControlMode = controlMode;

        if (controlMode == MANUAL)
        {
            lv_buttonmatrix_set_selected_button(objects.matrix_mode, 0);

            lv_buttonmatrix_set_button_ctrl(
                objects.matrix_mode,
                0,
                LV_BUTTONMATRIX_CTRL_CHECKED);
        }
        else
        {
            lv_buttonmatrix_set_selected_button(objects.matrix_mode, 1);
            lv_buttonmatrix_set_button_ctrl(
                objects.matrix_mode,
                1,
                LV_BUTTONMATRIX_CTRL_CHECKED);
        }
        if (controlMode == MANUAL)
            lv_obj_remove_state(objects.sw_bomba, LV_STATE_DISABLED);
        else
            lv_obj_add_state(objects.sw_bomba, LV_STATE_DISABLED);
    }

    if (firstUpdate || pumpState != lastPumpState)
    {
        lastPumpState = pumpState;

        if (pumpState)
            lv_obj_add_state(objects.sw_bomba, LV_STATE_CHECKED);
        else
            lv_obj_remove_state(objects.sw_bomba, LV_STATE_CHECKED);
    }

    // red
    const bool wifiState = gSystemState.red.connection;

    if (firstUpdate || wifiState != lastWifiState)
    {
        lastWifiState = wifiState;
        if (wifiState)
        {
            lv_obj_remove_state(objects.lbl_conexion, LV_STATE_CHECKED);
            lv_label_set_text(objects.lbl_conexion, "Conectado");
        }
        else
        {
            lv_obj_add_state(objects.lbl_conexion, LV_STATE_CHECKED);
            lv_label_set_text(objects.lbl_conexion, "Sin conexion");
        }
    }

    firstUpdate = false;
}