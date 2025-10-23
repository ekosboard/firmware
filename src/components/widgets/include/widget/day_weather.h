#ifndef DAY_WEATHER_H
#define DAY_WEATHER_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define DAY_WEATHER_FILE_PATH "day_weather.json"

typedef struct day_weather_s {
    lv_obj_t    *container_weather;
    lv_obj_t    *container_temp_range;
    lv_obj_t    *container_min_temp;
    lv_obj_t    *container_max_temp;

    lv_obj_t    *weather_icon_label;
    lv_obj_t    *weather_temp_label;
    lv_obj_t    *min_temp_icon;
    lv_obj_t    *min_temp_label;
    lv_obj_t    *max_temp_icon;
    lv_obj_t    *max_temp_label;
} day_weather_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_day_weather_draw(lv_obj_t *screen);
    esp_err_t   widget_day_weather_erase(void);
    esp_err_t   widget_day_weather_update(void);
    esp_err_t   widget_day_weather_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
