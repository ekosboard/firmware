#ifndef SIMPLE_DATE_H
#define SIMPLE_DATE_H

#include "widget.h"
#include <src/misc/lv_types.h>

typedef struct simple_date_s {

    lv_obj_t    *container_date;

    lv_obj_t    *day_of_week_label;
    lv_obj_t    *day_of_month_label;
} simple_date_t;


#ifdef __cplusplus
extern "C" {
#endif

    void simple_date_draw(lv_obj_t *screen, widget_t *widget);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
