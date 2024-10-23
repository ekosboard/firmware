#include "EPD.h"

void btn_bottom_right(const char *label)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);
    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_color_white());
    lv_style_set_border_opa(&style, LV_OPA_100);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_color_black());
    lv_style_set_pad_all(&style, 10);
    lv_style_set_text_color(&style, lv_color_black());

    lv_obj_t *btn1 = lv_button_create(lv_screen_active());
    lv_obj_remove_style_all(btn1);
    lv_obj_add_style(btn1, &style, 0);
    lv_obj_set_size(btn1, 150, LV_SIZE_CONTENT);
    lv_obj_align(btn1, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    /* Create a label for the symbol */
    lv_obj_t *symbol_label = lv_label_create(btn1);
    lv_label_set_text(symbol_label, LV_SYMBOL_RIGHT);
    lv_obj_align(symbol_label, LV_ALIGN_RIGHT_MID, -5, 0);

    /* Create a label for the text */
    lv_obj_t *text_label = lv_label_create(btn1);
    lv_label_set_text(text_label, label);
    lv_obj_align(text_label, LV_ALIGN_LEFT_MID, 5, 0);
}
