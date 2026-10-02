#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: sdr_param
//

void init_style_sdr_param_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_pad_top(style, 3);
    lv_style_set_pad_bottom(style, 3);
    lv_style_set_pad_left(style, 3);
    lv_style_set_pad_right(style, 3);
    lv_style_set_bg_color(style, lv_color_hex(0x38bdf8));
    lv_style_set_border_color(style, lv_color_hex(0xe2e8f0));
};

lv_style_t *get_style_sdr_param_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_sdr_param_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_sdr_param_KNOB_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x334155));
};

lv_style_t *get_style_sdr_param_KNOB_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_sdr_param_KNOB_DISABLED(style);
    }
    return style;
};

void init_style_sdr_param_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x38bdf8));
};

lv_style_t *get_style_sdr_param_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_sdr_param_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_sdr_param_INDICATOR_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x334155));
};

lv_style_t *get_style_sdr_param_INDICATOR_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_sdr_param_INDICATOR_DISABLED(style);
    }
    return style;
};

void init_style_sdr_param_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xe2e8f0));
};

lv_style_t *get_style_sdr_param_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_sdr_param_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_sdr_param(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_sdr_param_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_sdr_param_KNOB_DISABLED(), LV_PART_KNOB | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_sdr_param_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_sdr_param_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_sdr_param_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_sdr_param(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_sdr_param_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_sdr_param_KNOB_DISABLED(), LV_PART_KNOB | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_sdr_param_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_sdr_param_INDICATOR_DISABLED(), LV_PART_INDICATOR | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_sdr_param_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: label_param
//

void init_style_label_param_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xe2e8f0));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_param_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_param_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_param(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_param_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_param(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_param_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: label_state
//

void init_style_label_state_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0x4ade80));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_font(style, &lv_font_montserrat_10);
};

lv_style_t *get_style_label_state_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_state_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_label_state_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xfbbf24));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_label_state_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_state_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_label_state(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_state_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_label_state_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_label_state(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_state_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_label_state_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_sdr_param,
        add_style_label_param,
        add_style_label_state,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_sdr_param,
        remove_style_label_param,
        remove_style_label_state,
    };
    remove_style_funcs[styleIndex](obj);
}