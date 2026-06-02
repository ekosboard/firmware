#ifndef WIDGET_H
#define WIDGET_H

#include <src/misc/lv_types.h>

typedef struct widget_s {
    lv_obj_t        *lv_obj;
    void            *child;
    uint16_t        pos_x;
    uint16_t        pos_y;
    uint16_t        height;
    uint16_t        width;
    uint32_t        flag;
    uint32_t        update_data_interval_ms;
    uint32_t        update_data_timestamp;
} widget_t;

#endif
