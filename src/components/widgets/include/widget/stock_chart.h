#ifndef STOCK_CHART_H
#define STOCK_CHART_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define STOCK_CHART_FILE_PATH "stock_chart.json"
#define STOCK_HISTORY_MAX_POINTS 50

typedef struct stock_chart_s {
    lv_obj_t    *container_content;
    lv_obj_t    *container_row[2];
    lv_obj_t    *container_symbol[2];
    lv_obj_t    *container_symbol_top[2];
    lv_obj_t    *container_price[2];
    lv_obj_t    *container_chart[2];

    lv_obj_t    *symbol_label[2];
    lv_obj_t    *timeframe_label[2];
    lv_obj_t    *arrow_label[2];
    lv_obj_t    *diff_label[2];
    lv_obj_t    *chart_data[2];
    lv_obj_t    *price_label[2];

    lv_chart_series_t   *series[2];
    float               history[50];
    uint32_t            history_count;
    float               current_min;
    float               current_max;
} stock_chart_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_stock_chart_draw(lv_obj_t *screen);
    esp_err_t   widget_stock_chart_erase(void);
    esp_err_t   widget_stock_chart_update(void);
    esp_err_t   widget_stock_chart_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
