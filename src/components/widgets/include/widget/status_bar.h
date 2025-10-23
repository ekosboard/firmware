#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define STATUS_BAR_FILE_PATH "status_bar.json"

typedef struct status_bar_s {
    lv_obj_t    *container_clock;
    lv_obj_t    *container_date;
    lv_obj_t    *container_battery;

    lv_obj_t    *clock_label;
    lv_obj_t    *date_label;
    lv_obj_t    *battery_label;
    lv_obj_t    *network_label;
    lv_timer_t  *clock_timer;
} status_bar_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_status_bar_draw(lv_obj_t *screen);
    esp_err_t   widget_status_bar_erase(void);
    esp_err_t   widget_status_bar_update(void);
    esp_err_t   widget_status_bar_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
