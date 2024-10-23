#ifndef FILESYSTEM_INTERFACE_H
#define FILESYSTEM_INTERFACE_H

#include "esp_err.h"
#include "nvs_flash.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t nvs_init_interface();
    esp_err_t nvs_wifi_write_credential(char *ssid, char *password);
    esp_err_t nvs_wifi_read_credential(char *ssid_buf, size_t ssid_buf_size, char *password_buf, size_t password_buf_size);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
