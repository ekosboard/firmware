#ifndef SENSOR_BME680_H
#define SENSOR_BME680_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define SENSOR_BME680_FILE_PATH "sensor_BME680.json"

typedef struct sensor_BME680_s {
    lv_obj_t    *temperature_label;
    lv_obj_t    *humidity_label;
    lv_obj_t    *air_quality_label;
} sensor_BME680_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_sensor_BME680_draw(lv_obj_t *screen);
    esp_err_t   widget_sensor_BME680_erase(void);
    esp_err_t   widget_sensor_BME680_update(void);
    esp_err_t   widget_sensor_BME680_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif
