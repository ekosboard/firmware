#ifndef BATTERY_DISPLAY_H
#define BATTERY_DISPLAY_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define BATTERY_DISPLAY_FILE_PATH "battery_display.json"

typedef struct battery_display_s {
    lv_obj_t *icon_label;
    lv_obj_t *pct_label;
    lv_obj_t *voltage_label;
} battery_display_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t widget_battery_display_draw(lv_obj_t *screen);
    esp_err_t widget_battery_display_erase(void);
    esp_err_t widget_battery_display_update(void);
    esp_err_t widget_battery_display_update_data(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BATTERY_DISPLAY_H */
