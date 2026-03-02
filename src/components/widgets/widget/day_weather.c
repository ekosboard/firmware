#include "widget/day_weather.h"
#include "HTTPS_request.h"
#include "cJSON.h"
#include "core/lv_obj.h"
#include "esp_err.h"
#include "esp_log.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "icons.h"
#include "widget.h"
#include "wifi.h"

static const char *TAG = "WIDGET_DAY_WEATHER";
static void widget_day_weather(lv_obj_t *screen, widget_t *widget);
static esp_err_t build_open_weather_map_url(widget_config_t *cfg, char *buffer, size_t buffer_size);
static void open_weather_map_request(day_weather_t *child, const char *url);
static const char *get_weather_symbol(const char *owm_code);


esp_err_t   widget_day_weather_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_day_weather(screen, widget);
    return ESP_OK;
}


esp_err_t   widget_day_weather_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}


esp_err_t   widget_day_weather_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}


esp_err_t   widget_day_weather_update_data(void)
{
    ESP_LOGW(TAG, "UPDATE DATA");
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_DAY_WEATHER, &widget) != ESP_OK)
        return ESP_FAIL;
  
    char url[512];
    build_open_weather_map_url(widget->config, url, sizeof(url));
    open_weather_map_request(widget->child, url);
    return ESP_OK;
}

static void widget_day_weather(lv_obj_t *screen, widget_t *widget)
{
    static day_weather_t day_weather_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &day_weather_child;

    // simple_day_weather
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(widget->lv_obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(widget->lv_obj, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(widget->lv_obj, LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_label_set_text(day_weather_child.weather_icon_label, ICON_WEATHER_FEW_CLOUDS);
            lv_obj_set_style_text_font(day_weather_child.weather_icon_label, &symbol_nerdfont_128, LV_PART_MAIN | LV_STATE_DEFAULT);

            // weather temp
            day_weather_child.weather_temp_label = lv_label_create(day_weather_child.container_weather);
            lv_obj_set_pos(day_weather_child.weather_temp_label, 0, 0);
            lv_obj_set_size(day_weather_child.weather_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(day_weather_child.weather_temp_label, "18°");
            lv_obj_set_style_text_font(day_weather_child.weather_temp_label, &roboto_bold_64, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    lv_label_set_text(day_weather_child.max_temp_icon, ICON_SYSTEM_ARROW_UP);
                    lv_obj_set_style_text_font(day_weather_child.max_temp_icon, &symbol_nerdfont_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    day_weather_child.max_temp_label = lv_label_create(day_weather_child.container_max_temp);
                    lv_obj_set_pos(day_weather_child.max_temp_label, 0, 0);
                    lv_obj_set_size(day_weather_child.max_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.max_temp_label, "21°");
                    lv_obj_set_style_text_font(day_weather_child.max_temp_label, &roboto_bold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }

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
                    lv_label_set_text(day_weather_child.min_temp_icon, ICON_SYSTEM_ARROW_DOWN);
                    lv_obj_set_style_text_font(day_weather_child.min_temp_icon, &symbol_nerdfont_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    day_weather_child.min_temp_label = lv_label_create(day_weather_child.container_min_temp);
                    lv_obj_set_pos(day_weather_child.min_temp_label, 0, 0);
                    lv_obj_set_size(day_weather_child.min_temp_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(day_weather_child.min_temp_label, "8°");
                    lv_obj_set_style_text_font(day_weather_child.min_temp_label, &roboto_bold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

static esp_err_t build_open_weather_map_url(widget_config_t *cfg, char *buffer, size_t buffer_size)
{
    const char *lat = widget_config_list_get_value(cfg, "lat");
    const char *lon   = widget_config_list_get_value(cfg, "lon");
    const char *units = widget_config_list_get_value(cfg, "units");
    const char *exclude   = widget_config_list_get_value(cfg, "exclude");
    const char *apikey   = widget_config_list_get_value(cfg, "apikey");

    if(!lat || !lon || !units || !exclude || !apikey)
        return ESP_FAIL;

    snprintf(buffer, buffer_size,
            "https://api.openweathermap.org/data/3.0/onecall?"
            "lat=%s&lon=%s&units=%s&exclude=%s&appid=%s",
            lat,
            lon,
            units,
            exclude,
            apikey);

    return ESP_OK;
}

static void open_weather_map_request(day_weather_t *child, const char *url)
{
    char *resp = NULL;
    int status, len;
    /* "https://api.openweathermap.org/data/3.0/onecall?lat=50.63&lon=3.05&units=metric&exclude=minutely,hourly,alerts&appid=aeb66237ca8b7ea5c11d8f6c1bbedc87", */
    esp_err_t err = https_get_dyn(
            url,
            &resp,
            &status,
            &len);

    if (err == ESP_OK && resp)
    {
        ESP_LOGI(TAG, "HTTP %d, len=%d, body=%s", status, len, resp);

        // Parse JSON
        cJSON *root = cJSON_Parse(resp);
        if (!root)
        {
            ESP_LOGE("APP", "Erreur parsing JSON");
            return;
        }
        // Extraire "current"
        const cJSON *current = cJSON_GetObjectItemCaseSensitive(root, "current");
        if (cJSON_IsObject(current))
        {
            const cJSON *temp = cJSON_GetObjectItemCaseSensitive(current, "temp");
            if (cJSON_IsNumber(temp))
            {
                ESP_LOGI("APP", "Temp: %.2f °C", temp->valuedouble);
                lv_label_set_text_fmt(child->weather_temp_label, "%d°", temp->valueint);
            }

            // Exemple extraction du tableau weather[0].description
            const cJSON *weather = cJSON_GetObjectItemCaseSensitive(current, "weather");
            if (cJSON_IsArray(weather))
            {
                const cJSON *first_weather = cJSON_GetArrayItem(weather, 0);
                const cJSON *icon = cJSON_GetObjectItemCaseSensitive(first_weather, "icon");
                if (cJSON_IsString(icon))
                {
                    ESP_LOGI("APP", "Icon: %s", icon->valuestring);
                    const char *symbol = get_weather_symbol(icon->valuestring);
                    lv_label_set_text(child->weather_icon_label, symbol);
                }
            }
        }
        const cJSON *daily = cJSON_GetObjectItemCaseSensitive(root, "daily");
        if (cJSON_IsArray(daily))
        {
            const cJSON *today = cJSON_GetArrayItem(daily, 0);
            if (cJSON_IsObject(today))
            {
                const cJSON *temp = cJSON_GetObjectItemCaseSensitive(today, "temp");
                if (cJSON_IsObject(temp))
                {
                    const cJSON *min = cJSON_GetObjectItemCaseSensitive(temp, "min");
                    const cJSON *max = cJSON_GetObjectItemCaseSensitive(temp, "max");
                    if (cJSON_IsNumber(min))
                    {
                        ESP_LOGI("APP", "Min: %.2f °", min->valuedouble);
                        lv_label_set_text_fmt(child->min_temp_label, "%d°", min->valueint);
                    }
                    if (cJSON_IsNumber(max))
                    {
                        ESP_LOGI("APP", "Max: %.2f °", max->valuedouble);
                        lv_label_set_text_fmt(child->max_temp_label, "%d°", max->valueint);
                    }
                }
            }
        }
        cJSON_Delete(root);
    }
    else
    {
        ESP_LOGE("TAG", "Erreur HTTPS: err=%d, status=%d", err, status);
    }

    if (resp != NULL)
        free(resp);
}

typedef struct weather_icon_map_s {
    const char *owm_icon;   // code renvoyé par OpenWeatherMap
    const char *symbol;     // symbole LVGL
} weather_icon_map_t;

static const weather_icon_map_t weather_icon_map[] = {
    { "01d", ICON_WEATHER_SUNNY },
    { "02d", ICON_WEATHER_FEW_CLOUDS },
    { "03d", ICON_WEATHER_SCATTERED_CLOUDS },
    { "04d", ICON_WEATHER_BROKEN_CLOUDS },
    { "09d", ICON_WEATHER_SHOWER_RAIN },
    { "10d", ICON_WEATHER_RAIN },
    { "11d", ICON_WEATHER_THUNDERSTORM },
    { "13d", ICON_WEATHER_SNOW },
    { "50d", ICON_WEATHER_MIST },
};

static const char *get_weather_symbol(const char *owm_code)
{
    for (size_t i = 0; i < sizeof(weather_icon_map)/sizeof(weather_icon_map[0]); i++)
    {
        if (strcmp(owm_code, weather_icon_map[i].owm_icon) == 0)
        {
            return weather_icon_map[i].symbol;
        }
    }
    return ICON_WEATHER_FEW_CLOUDS;
}

