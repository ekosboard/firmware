#ifndef SIMPLE_DATE_H
#define SIMPLE_DATE_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define SIMPLE_DATE_FILE_PATH "simple_date.json"

typedef struct simple_date_s {
    lv_obj_t    *container_date;

    lv_obj_t    *day_of_week_label;
    lv_obj_t    *day_of_month_label;
} simple_date_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_simple_date_draw(lv_obj_t *screen);
    esp_err_t   widget_simple_date_erase(void);
    esp_err_t   widget_simple_date_update(void);
    esp_err_t   widget_simple_date_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
