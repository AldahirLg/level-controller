#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: sdr_param
lv_style_t *get_style_sdr_param_KNOB_DEFAULT();
lv_style_t *get_style_sdr_param_KNOB_DISABLED();
lv_style_t *get_style_sdr_param_INDICATOR_DEFAULT();
lv_style_t *get_style_sdr_param_INDICATOR_DISABLED();
lv_style_t *get_style_sdr_param_MAIN_DEFAULT();
void add_style_sdr_param(lv_obj_t *obj);
void remove_style_sdr_param(lv_obj_t *obj);

// Style: label_param
lv_style_t *get_style_label_param_MAIN_DEFAULT();
void add_style_label_param(lv_obj_t *obj);
void remove_style_label_param(lv_obj_t *obj);

// Style: label_state
lv_style_t *get_style_label_state_MAIN_DEFAULT();
lv_style_t *get_style_label_state_MAIN_CHECKED();
void add_style_label_state(lv_obj_t *obj);
void remove_style_label_state(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/