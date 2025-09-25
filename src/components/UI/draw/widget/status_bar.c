#include "UI.h"
#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style.h"
#include "core/lv_obj_style_gen.h"
#include "display/lv_display.h"
#include "esp_err.h"
#include "esp_log.h"
#include "font/lv_font.h"
#include "freertos/projdefs.h"
#include "layouts/flex/lv_flex.h"
#include "layouts/lv_layout.h"
#include "lv_api_map_v8.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_style.h"
#include "misc/lv_style_gen.h"
#include "misc/lv_text.h"
#include "misc/lv_timer.h"
#include "misc/lv_timer_private.h"
#include "misc/lv_types.h"
#include "widget.h"
#include "widgets/label/lv_label.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/* static void separator(lv_obj_t *status_bar) */
/* { */
/*     static lv_point_precise_t line_points[2]; */
/*     line_points[0].x = lv_pct(0); */
/*     line_points[0].y = lv_pct(100); */
/*     line_points[1].x = lv_pct(100); */
/*     line_points[1].y = lv_pct(100); */

/*     static lv_style_t style_line; */
/*     lv_style_init(&style_line); */
/*     lv_style_set_line_width(&style_line, 2); */
/*     lv_style_set_line_color(&style_line, lv_color_black()); */
/*     lv_style_set_line_rounded(&style_line, true); */

/*     lv_obj_t * separator = lv_line_create(status_bar); */
/*     lv_line_set_points(separator, line_points, 2); */
/*     lv_obj_add_style(separator, &style_line, 0); */
/*     lv_obj_set_size(separator, lv_pct(120) , lv_pct(100)); */
/*     lv_obj_align(separator, LV_ALIGN_BOTTOM_MID, 0, lv_pct(-30)); */
/* } */

static lv_obj_t *create_date_label(lv_obj_t *status_bar)
{
    time_t now = time(NULL);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);

    char date_str[10];
    strftime(date_str, sizeof(date_str), "%b %d", &timeinfo);

    lv_obj_t *date_label = lv_label_create(status_bar);
    lv_obj_set_pos(date_label, 0, 0);
    lv_obj_set_size(date_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(date_label, date_str);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    return date_label;
}

static lv_obj_t *create_network_label(lv_obj_t *status_bar)
{
    lv_obj_t *network_label = lv_label_create(status_bar);
    lv_obj_set_pos(network_label, 0, 0);
    lv_obj_set_size(network_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(network_label, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(network_label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    return network_label;
}

static lv_obj_t *create_battery_label(lv_obj_t *status_bar)
{
    lv_obj_t *battery_label = lv_label_create(status_bar);
    lv_obj_set_pos(battery_label, 0, 0);
    lv_obj_set_size(battery_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_3);
    lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    return battery_label;
}

static lv_obj_t *create_clock_label(lv_obj_t *status_bar)
{
    time_t now;
    struct tm timeinfo;
    char time_str[8];
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(time_str, sizeof(time_str), "%H : %M", &timeinfo);

    lv_obj_t *clock_label = lv_label_create(status_bar);
    lv_obj_set_pos(clock_label, 0, 0);
    lv_obj_set_size(clock_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(clock_label, time_str);
    lv_obj_set_style_text_font(clock_label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    return clock_label;
}

/* static void sync_timer_callback(lv_timer_t *timer) */
/* { */
/*     status_bar_t *status_bar_child = timer->user_data; */
/*     time_t now; */
/*     struct tm timeinfo; */
/*     char time_str[8]; */

/*     time(&now); */
/*     localtime_r(&now, &timeinfo); */
/*     strftime(time_str, sizeof(time_str), "%H : %M", &timeinfo); */

/*     ESP_LOGI("DEBUG TIME", "Hour: %d, Min: %d, Sec: %d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec); */
/*     lv_label_set_text(status_bar_child->clock_label, time_str); */

/*     // Vérifier si on est à minuit pour mettre à jour la date */
/*     if (timeinfo.tm_hour == 0 && timeinfo.tm_min == 0) */
/*     { */
/*         char date_str[10]; */
/*         strftime(date_str, sizeof(date_str), "%b %d", &timeinfo); */
/*         lv_label_set_text(status_bar_child->date_label, date_str); */
/*     } */

/*     //Re-synchro timer */
/*     int next_minute_delay = (60 - timeinfo.tm_sec) * 1000; */
/*     lv_timer_set_period(timer, next_minute_delay); */
/* } */

/* TODO: add uint8_t flag for display clock/battery/network/date */
static void widget_status_bar(lv_obj_t *screen, widget_t *widget)
{
    static status_bar_t status_bar_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &status_bar_child;

    /* separator(widget->lv_obj); */

    // status bar
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    lv_obj_set_style_pad_left(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_SPACE_AROUND, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // date label container
    status_bar_child.container_date = lv_obj_create(widget->lv_obj);
    lv_obj_set_pos(status_bar_child.container_date, 0, 0);
    lv_obj_set_size(status_bar_child.container_date, LV_SIZE_CONTENT, lv_pct(100));
    lv_obj_set_style_pad_top(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(status_bar_child.container_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(status_bar_child.container_date, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(status_bar_child.container_date, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(status_bar_child.container_date, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(status_bar_child.container_date, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_grow(status_bar_child.container_date, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(status_bar_child.container_date, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    status_bar_child.date_label = create_date_label(status_bar_child.container_date);

    // clock label container
    status_bar_child.container_clock = lv_obj_create(widget->lv_obj);
    lv_obj_set_pos(status_bar_child.container_clock, 0, 0);
    lv_obj_set_size(status_bar_child.container_clock, LV_SIZE_CONTENT, lv_pct(100));
    lv_obj_set_style_pad_top(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(status_bar_child.container_clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(status_bar_child.container_clock, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(status_bar_child.container_clock, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(status_bar_child.container_clock, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(status_bar_child.container_clock, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    status_bar_child.clock_label = create_clock_label(status_bar_child.container_clock);

    // status bar icon container
    status_bar_child.container_battery = lv_obj_create(widget->lv_obj);
    lv_obj_set_pos(status_bar_child.container_battery, 0, 0);
    lv_obj_set_size(status_bar_child.container_battery, LV_SIZE_CONTENT, lv_pct(100));
    lv_obj_set_style_pad_left(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(status_bar_child.container_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(status_bar_child.container_battery, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(status_bar_child.container_battery, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_grow(status_bar_child.container_battery, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(status_bar_child.container_battery, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(status_bar_child.container_battery, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(status_bar_child.container_battery, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    status_bar_child.network_label = create_network_label(status_bar_child.container_battery);
    status_bar_child.battery_label = create_battery_label(status_bar_child.container_battery);

    // clock timer
    /* status_bar_child.clock_timer = lv_timer_create(sync_timer_callback, 1000, &status_bar_child); */
    /* lv_timer_set_repeat_count(status_bar_child.clock_timer, -1); */
    /* lv_timer_ready(status_bar_child.clock_timer); */
}

esp_err_t widget_status_bar_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STATUS_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_status_bar(screen, widget);
    return ESP_OK;
}


esp_err_t widget_status_bar_erase()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STATUS_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    /* status_bar_t *status_bar_child = widget->child; */
    /* lv_timer_delete(status_bar_child->clock_timer); */
    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t   widget_status_bar_update()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STATUS_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}

static void update_clock(status_bar_t *status_bar_child)
{
    time_t now;
    struct tm timeinfo;
    char time_str[8];

    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(time_str, sizeof(time_str), "%H : %M", &timeinfo);

    ESP_LOGI("DEBUG TIME", "Hour: %d, Min: %d, Sec: %d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    lv_label_set_text(status_bar_child->clock_label, time_str);

    // Vérifier si on est à minuit pour mettre à jour la date
    if (timeinfo.tm_hour == 0 && timeinfo.tm_min == 0)
    {
        char date_str[10];
        strftime(date_str, sizeof(date_str), "%b %d", &timeinfo);
        lv_label_set_text(status_bar_child->date_label, date_str);
    }
}

esp_err_t   widget_status_bar_update_data()
{
    ESP_LOGW("STATUS_BAR", "UPDATE DATA");

    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STATUS_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    update_clock(widget->child);
    return ESP_OK;
}
