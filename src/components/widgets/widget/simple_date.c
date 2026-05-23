#include "widget/simple_date.h"
#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "widget.h"
#include <time.h>

static const char *TAG = "WIDGET_SIMPLE_DATE";
static void widget_date_update(simple_date_t *child);
static void widget_simple_date(lv_obj_t *screen, widget_t *widget);

esp_err_t   widget_simple_date_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIMPLE_DATE, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_simple_date(screen, widget);
    return ESP_OK;
}


esp_err_t   widget_simple_date_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIMPLE_DATE, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}


esp_err_t   widget_simple_date_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIMPLE_DATE, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}


esp_err_t   widget_simple_date_update_data(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIMPLE_DATE, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_date_update(widget->child);
    return ESP_OK;
}

static void widget_simple_date(lv_obj_t *screen, widget_t *widget)
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
            lv_label_set_text(simple_date_child.day_of_week_label, "Sunday");
            lv_obj_set_style_text_font(simple_date_child.day_of_week_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // day of month
            simple_date_child.day_of_month_label = lv_label_create(widget->lv_obj);
            lv_obj_set_pos(simple_date_child.day_of_month_label, 0, 0);
            lv_obj_set_size(simple_date_child.day_of_month_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(simple_date_child.day_of_month_label, "01");
            lv_obj_set_style_text_font(simple_date_child.day_of_month_label, &roboto_bold_96, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

static void widget_date_update(simple_date_t *child)
{
    time_t now = time(NULL);

    // Sécurité : si le temps n'est pas encore synchronisé
    if (now < 100000)
    {
        lv_label_set_text(child->day_of_week_label, "--");
        lv_label_set_text(child->day_of_month_label, "--");
        return;
    }

    struct tm timeinfo;
    localtime_r(&now, &timeinfo);

    char day_str[16];
    char date_str[4];   // "31" + '\0'

    // Jour complet (Monday / Lundi selon locale)
    strftime(day_str, sizeof(day_str), "%A", &timeinfo);

    // Jour du mois uniquement
    strftime(date_str, sizeof(date_str), "%d", &timeinfo);

    lv_label_set_text(child->day_of_week_label, day_str);
    lv_label_set_text(child->day_of_month_label, date_str);
}

