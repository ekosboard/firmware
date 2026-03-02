#ifndef SIDE_BAR_H
#define SIDE_BAR_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define SIDE_BAR_FILE_PATH "side_bar.json"

typedef struct side_bar_s {
    lv_obj_t    *container_status;
    lv_obj_t    *container_widget;;

    lv_obj_t    *status_icon[2];
    lv_obj_t    *widget_icon[5];
} side_bar_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_side_bar_draw(lv_obj_t *screen);
    esp_err_t   widget_side_bar_erase(void);
    esp_err_t   widget_side_bar_update(void);
    esp_err_t   widget_side_bar_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
