#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_home() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.home = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xf5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // tab_view
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.tab_view = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_BOTTOM);
            lv_tabview_set_tab_bar_size(obj, 32);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tab_panel
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Inicio");
                    objects.tab_panel = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, -6, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Panel de control");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj1 = obj;
                            lv_obj_set_pos(obj, -6, 117);
                            lv_obj_set_size(obj, 226, 39);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // bar_cis
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_cis = obj;
                                    lv_obj_set_pos(obj, -5, 6);
                                    lv_obj_set_size(obj, 173, 10);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj2 = obj;
                                    lv_obj_set_pos(obj, -4, -12);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Cisterna");
                                }
                                {
                                    // lbl_cis_level
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_cis_level = obj;
                                    lv_obj_set_pos(obj, 167, 3);
                                    lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "100");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj3 = obj;
                                    lv_obj_set_pos(obj, 199, 6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "%");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj4 = obj;
                                    lv_obj_set_pos(obj, 142, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Sensor :");
                                }
                                {
                                    // lbl_cis_sensor
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_cis_sensor = obj;
                                    lv_obj_set_pos(obj, 183, -9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_label_state(obj);
                                    lv_label_set_text(obj, "Falla");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj5 = obj;
                            lv_obj_set_pos(obj, -6, 159);
                            lv_obj_set_size(obj, 226, 106);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // sw_bomba
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.sw_bomba = obj;
                                    lv_obj_set_pos(obj, 64, 56);
                                    lv_obj_set_size(obj, 72, 30);
                                    lv_obj_add_event_cb(obj, action_call_pump, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_INDICATOR | LV_STATE_CHECKED);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_KNOB | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_KNOB | LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj6 = obj;
                                    lv_obj_set_pos(obj, -2, -12);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Modo");
                                }
                                {
                                    // matrix_mode
                                    lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
                                    objects.matrix_mode = obj;
                                    lv_obj_set_pos(obj, -2, 5);
                                    lv_obj_set_size(obj, 204, 39);
                                    static const char *map[3] = {
                                        "Manual",
                                        "Auto",
                                        NULL,
                                    };
                                    static lv_buttonmatrix_ctrl_t ctrl_map[2] = {
                                        1 | LV_BUTTONMATRIX_CTRL_CHECKABLE,
                                        1 | LV_BUTTONMATRIX_CTRL_CHECKABLE,
                                    };
                                    lv_buttonmatrix_set_map(obj, map);
                                    lv_buttonmatrix_set_ctrl_map(obj, ctrl_map);
                                    lv_buttonmatrix_set_one_checked(obj, true);
                                    lv_obj_add_event_cb(obj, action_call_modes, LV_EVENT_PRESSED, (void *)0);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_ITEMS | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_ITEMS | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_ITEMS | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x0b1220), LV_PART_ITEMS | LV_STATE_CHECKED);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj7 = obj;
                                    lv_obj_set_pos(obj, -2, 46);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Bomba");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj8 = obj;
                            lv_obj_set_pos(obj, -6, 34);
                            lv_obj_set_size(obj, 226, 80);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj9 = obj;
                                    lv_obj_set_pos(obj, 130, 42);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Sensor :");
                                }
                                {
                                    // lbl_tin_sensor
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_tin_sensor = obj;
                                    lv_obj_set_pos(obj, 179, 42);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_label_state(obj);
                                    lv_label_set_text(obj, "Falla");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj10 = obj;
                                    lv_obj_set_pos(obj, 131, -1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Bateria:");
                                }
                                {
                                    // lbl_tin_bat
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_tin_bat = obj;
                                    lv_obj_set_pos(obj, 179, -1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_label_state(obj);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj11 = obj;
                                    lv_obj_set_pos(obj, 120, 21);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Conexion:");
                                }
                                {
                                    // lbl_tin_con
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_tin_con = obj;
                                    lv_obj_set_pos(obj, 179, 22);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_label_state(obj);
                                    lv_label_set_text(obj, "Falla");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj12 = obj;
                                    lv_obj_set_pos(obj, 49, 2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Tinaco");
                                }
                                {
                                    // bar_tin
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_tin = obj;
                                    lv_obj_set_pos(obj, -4, -8);
                                    lv_obj_set_size(obj, 50, 70);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj13 = obj;
                                    lv_obj_set_pos(obj, 87, 25);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "%");
                                }
                                {
                                    // lbl_tin_level
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_tin_level = obj;
                                    lv_obj_set_pos(obj, 52, 19);
                                    lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "100");
                                }
                            }
                        }
                        {
                            // panel_msg_state
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.panel_msg_state = obj;
                            lv_obj_set_pos(obj, -6, 11);
                            lv_obj_set_size(obj, 225, 20);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x3a2e0f), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_mgs_state
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_mgs_state = obj;
                                    lv_obj_set_pos(obj, -5, -8);
                                    lv_obj_set_size(obj, 208, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfbbf24), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_label_set_text_static(obj, "Tinaco desconectado");
                                }
                            }
                        }
                    }
                }
                {
                    // tab_param
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Ajustes");
                    objects.tab_param = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // btn_param
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_param = obj;
                            lv_obj_set_pos(obj, 0, 236);
                            lv_obj_set_size(obj, 214, 29);
                            lv_obj_add_event_cb(obj, action_call_save_values_param, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x38bdf8), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_editar
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_editar = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_label_set_text_static(obj, "Editar");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj14 = obj;
                            lv_obj_set_pos(obj, -6, 34);
                            lv_obj_set_size(obj, 227, 189);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 1, -9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "Altura de tinaco cm");
                                }
                                {
                                    // lbl_sdr_height_tin
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_sdr_height_tin = obj;
                                    lv_obj_set_pos(obj, 179, -9);
                                    lv_obj_set_size(obj, 21, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "0");
                                }
                                {
                                    // sdr_height_tin
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.sdr_height_tin = obj;
                                    lv_obj_set_pos(obj, 7, 9);
                                    lv_obj_set_size(obj, 193, 13);
                                    lv_slider_set_range(obj, 0, 400);
                                    lv_obj_add_event_cb(obj, action_call_param_srd, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    add_style_sdr_param(obj);
                                    lv_obj_set_style_pad_top(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 1, 29);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "Altura de cisterna cm");
                                }
                                {
                                    // lbl_sdr_height_cis
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_sdr_height_cis = obj;
                                    lv_obj_set_pos(obj, 179, 29);
                                    lv_obj_set_size(obj, 21, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "0");
                                }
                                {
                                    // sdr_height_cis
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.sdr_height_cis = obj;
                                    lv_obj_set_pos(obj, 7, 46);
                                    lv_obj_set_size(obj, 193, 13);
                                    lv_slider_set_range(obj, 0, 400);
                                    lv_obj_add_event_cb(obj, action_call_param_srd, LV_EVENT_VALUE_CHANGED, (void *)1);
                                    add_style_sdr_param(obj);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 1, 66);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "Nivel alto");
                                }
                                {
                                    // lbl_sdr_level_high
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_sdr_level_high = obj;
                                    lv_obj_set_pos(obj, 179, 66);
                                    lv_obj_set_size(obj, 21, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "0");
                                }
                                {
                                    // sdr_level_high
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.sdr_level_high = obj;
                                    lv_obj_set_pos(obj, 7, 83);
                                    lv_obj_set_size(obj, 193, 13);
                                    lv_obj_add_event_cb(obj, action_call_param_srd, LV_EVENT_VALUE_CHANGED, (void *)2);
                                    add_style_sdr_param(obj);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 1, 103);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "Nivel bajo");
                                }
                                {
                                    // lbl_sdr_level_low
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_sdr_level_low = obj;
                                    lv_obj_set_pos(obj, 179, 103);
                                    lv_obj_set_size(obj, 21, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "0");
                                }
                                {
                                    // sdr_level_low
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.sdr_level_low = obj;
                                    lv_obj_set_pos(obj, 7, 120);
                                    lv_obj_set_size(obj, 193, 13);
                                    lv_obj_add_event_cb(obj, action_call_param_srd, LV_EVENT_VALUE_CHANGED, (void *)3);
                                    add_style_sdr_param(obj);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 1, 140);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "Nivel minimo cisterna");
                                }
                                {
                                    // lbl_sdr_min_cis
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_sdr_min_cis = obj;
                                    lv_obj_set_pos(obj, 179, 140);
                                    lv_obj_set_size(obj, 21, LV_SIZE_CONTENT);
                                    add_style_label_param(obj);
                                    lv_label_set_text_static(obj, "0");
                                }
                                {
                                    // sdr_cis_level_min
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.sdr_cis_level_min = obj;
                                    lv_obj_set_pos(obj, 7, 156);
                                    lv_obj_set_size(obj, 193, 13);
                                    lv_slider_set_range(obj, 0, 50);
                                    lv_obj_add_event_cb(obj, action_call_param_srd, LV_EVENT_VALUE_CHANGED, (void *)4);
                                    add_style_sdr_param(obj);
                                }
                                {
                                    // lbl_error_parameters_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_error_parameters_1 = obj;
                                    lv_obj_set_pos(obj, -5, 235);
                                    lv_obj_set_size(obj, 185, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj15 = obj;
                            lv_obj_set_pos(obj, -6, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Parametros");
                        }
                        {
                            // panel_msg_param
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.panel_msg_param = obj;
                            lv_obj_set_pos(obj, -6, 10);
                            lv_obj_set_size(obj, 225, 20);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x3a2e0f), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lbl_msg_param
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_msg_param = obj;
                                    lv_obj_set_pos(obj, -13, -8);
                                    lv_obj_set_size(obj, 225, LV_SIZE_CONTENT);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfbbf24), LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_label_set_text_static(obj, "");
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Mas");
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj16 = obj;
                            lv_obj_set_pos(obj, -4, 37);
                            lv_obj_set_size(obj, 223, 73);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj17 = obj;
                                    lv_obj_set_pos(obj, -8, 9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Red");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj18 = obj;
                                    lv_obj_set_pos(obj, -8, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Version");
                                }
                                {
                                    // lbl_ssid_wifi
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.lbl_ssid_wifi = obj;
                                    lv_obj_set_pos(obj, 121, 9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "casa_3");
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj19 = obj;
                                    lv_obj_set_pos(obj, 121, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "1.0");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj20 = obj;
                            lv_obj_set_pos(obj, 108, 119);
                            lv_obj_set_size(obj, 111, 30);
                            lv_obj_add_event_cb(obj, action_call_reset, LV_EVENT_PRESSED, (void *)0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Restablecer");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj21 = obj;
                            lv_obj_set_pos(obj, -4, 119);
                            lv_obj_set_size(obj, 110, 30);
                            lv_obj_add_event_cb(obj, action_call_restart, LV_EVENT_PRESSED, (void *)0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Reiniciar");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj22 = obj;
                            lv_obj_set_pos(obj, -6, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Informacion");
                        }
                    }
                }
            }
        }
        {
            // lbl_conexion
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_conexion = obj;
            lv_obj_set_pos(obj, 166, 10);
            lv_obj_set_size(obj, 66, LV_SIZE_CONTENT);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x4ade80), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xf87171), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_label_set_text_static(obj, "Sin conexion");
        }
    }
    
    tick_screen_home();
}

void tick_screen_home() {
}

void create_screen_configless() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.configless = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0b1220), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj23 = obj;
            lv_obj_set_pos(obj, 13, 12);
            lv_obj_set_size(obj, 215, 177);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x172033), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 13, 23);
            lv_obj_set_size(obj, 215, LV_SIZE_CONTENT);
            lv_obj_set_style_text_line_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xe2e8f0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Realizar la configuracion desde tu app");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 45, 75);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Ecuentra tu dispositivo como:");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj26 = obj;
            lv_obj_set_pos(obj, 68, 86);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x94a3b8), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "\"Control de nivel\"");
        }
    }
    
    tick_screen_configless();
}

void tick_screen_configless() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_home,
    tick_screen_configless,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 2) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_home();
    create_screen_configless();
}