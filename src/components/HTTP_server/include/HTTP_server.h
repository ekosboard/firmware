#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

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
#include "wifi.h"
#include "filesystem_interface.h"

#include "API_system.h"

#ifdef __cplusplus
extern "C" {
#endif

    void    http_server(void *pvParameters);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
