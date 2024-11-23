#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include "esp_event.h"
#include "esp_tls.h"
#include "esp_check.h"
#include "nvs.h"
#include "cJSON.h"
#include <esp_system.h>
#include "esp_err.h"

#include "wifi.h"
#include "filesystem_interface.h"
#include "EPD.h"
#include "UI.h"

#include "API_system.h"
#include "API_ui.h"


#define BUF_SIZE            1024
#define MAX_WIDGETS_QUEUE   4

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  HTTP_SERVER MAIN
    ////////////////////////////////////////////////////////////////////////////////
    void    http_server(void *pvParameters);

    ////////////////////////////////////////////////////////////////////////////////
    //  QUEUE
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t init_widget_update_queue(void);
    esp_err_t push_widget_update_queue(widget_update_t *widget);
    esp_err_t pop_widget_update_queue(widget_update_t *widget);

    ////////////////////////////////////////////////////////////////////////////////
    //  UTILS
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t get_json_object_item(cJSON *json, const char *key, cJSON **item);
    esp_err_t get_json_string_item(cJSON *json, const char *key, cJSON **item, const char **string_value);
    esp_err_t get_json_number_item(cJSON *json, const char *key, cJSON **item, int *number_value);
    esp_err_t read_http_request_content(httpd_req_t *req, char **content);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
