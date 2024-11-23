#ifndef FILESYSTEM_INTERFACE_H
#define FILESYSTEM_INTERFACE_H

#include "cJSON.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include <stddef.h>
#include <stdint.h>

#define SETUP_MAGIC_KEY 0xCAFEBABE

typedef struct {
    int32_t magic_key;
    int8_t  setup_status;
    int8_t  network_status;
    int8_t  screen_id;
    int64_t timestamp;
    char    timezone[64];
} setup_state_t;

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  NVS
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t   nvs_init_interface(void);
    esp_err_t   nvs_wifi_write_credential(char *ssid, char *password);
    esp_err_t   nvs_wifi_read_credential(char *ssid_buf, size_t ssid_buf_size, char *password_buf, size_t password_buf_size);
    esp_err_t   nvs_setup_state_write_magic_key();
    esp_err_t   nvs_setup_state_read_all(setup_state_t *setup_state);
    esp_err_t   nvs_setup_state_write_all(setup_state_t *setup_state);
    esp_err_t   nvs_setup_state_write_setup_status(int8_t setup_status);
    esp_err_t   nvs_setup_state_write_network_status(int8_t network_status);
    esp_err_t   nvs_setup_state_write_screen_id(int8_t screen_id);
    esp_err_t   nvs_setup_state_write_timestamp(int64_t timestamp);
    esp_err_t   nvs_setup_state_write_timezone(char *timezone);
    int8_t      nvs_setup_state_read_setup_status();
    int8_t      nvs_setup_state_read_network_status();
    int8_t      nvs_setup_state_read_screen_id();
    int64_t     nvs_setup_state_read_timestamp();
    esp_err_t   nvs_setup_state_read_timezone(char *timezone);

    ////////////////////////////////////////////////////////////////////////////////
    //  FAT
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t   mount_fat_fs(void);
    esp_err_t   unmount_fat_fs(void);
    esp_err_t   check_file_fat_fs(const char *path);
    esp_err_t   write_file_fat_fs(const char *path, char *data);
    esp_err_t   read_file_fat_fs(const char *path, int len);

    ////////////////////////////////////////////////////////////////////////////////
    //  FAT/JSON
    ////////////////////////////////////////////////////////////////////////////////
    cJSON       *read_json_file(const char *path);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
