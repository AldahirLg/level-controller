#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_nav_param(lv_event_t * e);
extern void action_nav_home(lv_event_t * e);
extern void action_call_modes(lv_event_t * e);
extern void action_call_pump(lv_event_t * e);
extern void action_call_param_srd(lv_event_t * e);
extern void action_call_save_values_param(lv_event_t * e);
extern void action_call_reset(lv_event_t * e);
extern void action_call_restart(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/