#ifndef SEEDBOX_MONITORING_H
#define SEEDBOX_MONITORING_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define SEEDBOX_MONITORING_FILE_PATH "seedbox_monitoring.json"

typedef struct seedbox_monitoring_s {
    lv_obj_t    *container_header;
    lv_obj_t    *container_content;
    lv_obj_t    *container_disk;
    lv_obj_t    *container_traffic;
    lv_obj_t    *container_footer;


    lv_obj_t    *title_label;
    lv_obj_t    *header_label;
    lv_obj_t    *disk_arc;
    lv_obj_t    *disk_label;
    lv_obj_t    *traffic_arc;
    lv_obj_t    *traffic_label;
    lv_obj_t    *footer_label;

} seedbox_monitoring_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_seedbox_monitoring_draw(lv_obj_t *screen);
    esp_err_t   widget_seedbox_monitoring_erase(void);
    esp_err_t   widget_seedbox_monitoring_update(void);
    esp_err_t   widget_seedbox_monitoring_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
