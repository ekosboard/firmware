#include "simple_date.h"
#include "widget.h"
#include <lvgl.h>
#include <stdlib.h>
#include "icons.h"
#include "font.h"

void simple_date_draw(lv_obj_t *screen, widget_t *widget)
{
    static simple_date_t simple_date_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &simple_date_child;

    // simple date
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(widget->lv_obj, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(widget->lv_obj, LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        {
            // day of week
            simple_date_child.day_of_week_label = lv_label_create(widget->lv_obj);
            lv_obj_set_pos(simple_date_child.day_of_week_label, 0, 0);
            lv_obj_set_size(simple_date_child.day_of_week_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(simple_date_child.day_of_week_label, "Monday");
            lv_obj_set_style_text_font(simple_date_child.day_of_week_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // day of month
            simple_date_child.day_of_month_label = lv_label_create(widget->lv_obj);
            lv_obj_set_pos(simple_date_child.day_of_month_label, 0, 0);
            lv_obj_set_size(simple_date_child.day_of_month_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(simple_date_child.day_of_month_label, "18");
            lv_obj_set_style_text_font(simple_date_child.day_of_month_label, &roboto_bold_96, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}
