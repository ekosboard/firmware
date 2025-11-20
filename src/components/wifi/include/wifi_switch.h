#ifndef WIFI_SWITCH_H
#define WIFI_SWITCH_H

#include "esp_err.h"
#include "freertos/idf_additions.h"

typedef struct {
    char ssid[33];
    char pass[65];
} wifi_switch_request_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t       init_wifi_switch_queue(void);
    void            delete_wifi_switch_queue(void);
    esp_err_t       push_wifi_switch_queue(wifi_switch_request_t req);
    esp_err_t       pop_wifi_switch_queue(wifi_switch_request_t *req);

    void            wifi_switch_task(void *pvParameter);
    TaskHandle_t    *wifi_swtich_task_get_handle(void);
    bool            check_wifi_is_switching();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
