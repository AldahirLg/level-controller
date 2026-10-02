#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_HOME = 1,
    SCREEN_ID_CONFIGLESS = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *home;
    lv_obj_t *configless;
    lv_obj_t *tab_view;
    lv_obj_t *tab_panel;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *bar_cis;
    lv_obj_t *obj2;
    lv_obj_t *lbl_cis_level;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *lbl_cis_sensor;
    lv_obj_t *obj5;
    lv_obj_t *sw_bomba;
    lv_obj_t *obj6;
    lv_obj_t *matrix_mode;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *lbl_tin_sensor;
    lv_obj_t *obj10;
    lv_obj_t *lbl_tin_bat;
    lv_obj_t *obj11;
    lv_obj_t *lbl_tin_con;
    lv_obj_t *obj12;
    lv_obj_t *bar_tin;
    lv_obj_t *obj13;
    lv_obj_t *lbl_tin_level;
    lv_obj_t *panel_msg_state;
    lv_obj_t *lbl_mgs_state;
    lv_obj_t *tab_param;
    lv_obj_t *btn_param;
    lv_obj_t *lbl_editar;
    lv_obj_t *obj14;
    lv_obj_t *lbl_sdr_height_tin;
    lv_obj_t *sdr_height_tin;
    lv_obj_t *lbl_sdr_height_cis;
    lv_obj_t *sdr_height_cis;
    lv_obj_t *lbl_sdr_level_high;
    lv_obj_t *sdr_level_high;
    lv_obj_t *lbl_sdr_level_low;
    lv_obj_t *sdr_level_low;
    lv_obj_t *lbl_sdr_min_cis;
    lv_obj_t *sdr_cis_level_min;
    lv_obj_t *lbl_error_parameters_1;
    lv_obj_t *obj15;
    lv_obj_t *panel_msg_param;
    lv_obj_t *lbl_msg_param;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *lbl_ssid_wifi;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *lbl_conexion;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
} objects_t;

extern objects_t objects;

void create_screen_home();
void tick_screen_home();

void create_screen_configless();
void tick_screen_configless();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/