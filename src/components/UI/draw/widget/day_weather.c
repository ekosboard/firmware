#include "widget/day_weather.h"
#include "HTTPS_request.h"
#include "esp_err.h"
#include "esp_log.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "widget.h"
#include "wifi.h"

static const char *TAG = "WIDGET_DAY_WEATHER";

static void widget_day_weather(lv_obj_t *screen, widget_t *widget)
{
    static day_weather_t day_weather_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &day_weather_child;

    // simple_day_weather
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(widget->lv_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(widget->lv_obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(widget->lv_obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(widget->lv_obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(widget->lv_obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        // weather container
        day_weather_child.container_weather = lv_obj_create(widget->lv_obj);
        lv_obj_set_pos(day_weather_child.container_weather, 0, 0);
        lv_obj_set_size(day_weather_child.container_weather, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_pad_left(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(day_weather_child.container_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_layout(day_weather_child.container_weather, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_flow(day_weather_child.container_weather, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            // weather icon
            day_weather_child.weather_icon_label = lv_label_create(day_weather_child.container_weather);
            lv_obj_set_pos(day_weather_child.weather_icon_label, 0, 0);
            lv_obj_set_size(day_weather_child.weather_icon_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(day_weather_child.weather_icon_label, SYMBOL_WEATHER_FEW_CLOUDS);
            lv_obj_set_style_text_font(day_weather_child.weather_icon_label, &symbol_nerdfont_96, LV_PART_MAIN | LV_STATE_DEFAULT);

            // weather temp
            day_weather_child.weather_temp_label = lv_label_create(day_weather_child.container_weather);
            lv_obj_set_pos(day_weather_child.weather_temp_label, 0, 0);
            lv_obj_set_size(day_weather_child.weather_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(day_weather_child.weather_temp_label, "18°");
            lv_obj_set_style_text_font(day_weather_child.weather_temp_label, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_top(day_weather_child.weather_temp_label, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        // temp range container
        day_weather_child.container_temp_range = lv_obj_create(widget->lv_obj);
        lv_obj_set_pos(day_weather_child.container_temp_range, 0, 0);
        lv_obj_set_size(day_weather_child.container_temp_range, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_pad_left(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(day_weather_child.container_temp_range, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_layout(day_weather_child.container_temp_range, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_flow(day_weather_child.container_temp_range, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            // min temp container
            day_weather_child.container_min_temp = lv_obj_create(day_weather_child.container_temp_range);
            lv_obj_set_pos(day_weather_child.container_min_temp, 0, 0);
            lv_obj_set_size(day_weather_child.container_min_temp, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_left(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(day_weather_child.container_min_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(day_weather_child.container_min_temp, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(day_weather_child.container_min_temp, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(day_weather_child.container_min_temp, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(day_weather_child.container_min_temp, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                {
                    day_weather_child.min_temp_icon = lv_label_create(day_weather_child.container_min_temp);
                    lv_obj_set_pos(day_weather_child.min_temp_icon, 0, 0);
                    lv_obj_set_size(day_weather_child.min_temp_icon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.min_temp_icon, SYMBOL_ARROW_DOWN);
                    lv_obj_set_style_text_font(day_weather_child.min_temp_icon, &symbol_nerdfont_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    day_weather_child.min_temp_label = lv_label_create(day_weather_child.container_min_temp);
                    lv_obj_set_pos(day_weather_child.min_temp_label, 0, 0);
                    lv_obj_set_size(day_weather_child.min_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.min_temp_label, "8°");
                    lv_obj_set_style_text_font(day_weather_child.min_temp_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }

            // max temp container
            day_weather_child.container_max_temp = lv_obj_create(day_weather_child.container_temp_range);
            lv_obj_set_pos(day_weather_child.container_max_temp, 0, 0);
            lv_obj_set_size(day_weather_child.container_max_temp, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_left(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(day_weather_child.container_max_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(day_weather_child.container_max_temp, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(day_weather_child.container_max_temp, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(day_weather_child.container_max_temp, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(day_weather_child.container_max_temp, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                {
                    day_weather_child.max_temp_icon = lv_label_create(day_weather_child.container_max_temp);
                    lv_obj_set_pos(day_weather_child.max_temp_icon, 0, 0);
                    lv_obj_set_size(day_weather_child.max_temp_icon, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.max_temp_icon, SYMBOL_ARROW_UP);
                    lv_obj_set_style_text_font(day_weather_child.max_temp_icon, &symbol_nerdfont_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    day_weather_child.max_temp_label = lv_label_create(day_weather_child.container_max_temp);
                    lv_obj_set_pos(day_weather_child.max_temp_label, 0, 0);
                    lv_obj_set_size(day_weather_child.max_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.max_temp_label, "21°");
                    lv_obj_set_style_text_font(day_weather_child.max_temp_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

esp_err_t   widget_day_weather_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_day_weather(screen, widget);
    return ESP_OK;
}


esp_err_t   widget_day_weather_erase()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t   widget_day_weather_update()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}

static void open_weather_map_request(void);

esp_err_t   widget_day_weather_update_data()
{
    ESP_LOGW(TAG, "UPDATE DATA");

    open_weather_map_request();
    return ESP_OK;
}

static void open_weather_map_request(void)
{

    char out_buf[1048];
    int out_status = 0, out_len = 0;

    esp_err_t ret = https_get("https://api.openweathermap.org/data/3.0/onecall?lat=50.63&lon=3.05&units=metric&exclude=minutely,hourly,daily,alerts&appid=aeb66237ca8b7ea5c11d8f6c1bbedc87", out_buf, 2048, &out_status, &out_len);

    if (ret == ESP_OK && out_status == 200)
        ESP_LOGI("APP", "Reçu (%d octets): %s", out_len, out_buf);
    else
        ESP_LOGE("APP", "Erreur HTTPS: err=%d, status=%d", ret, out_status);
}
