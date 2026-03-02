#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include "esp_err.h"
#include <stdio.h>

typedef struct {
    char device_name[32];
    char hostname[32];
    char firmware_version[16];
    char serial[32];
} device_info_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t device_info_load(device_info_t *info);
    esp_err_t device_info_save(const device_info_t *info);

    // Fonction utilitaire pour initialiser les valeurs par défaut
    void device_info_set_defaults(device_info_t *info);

    esp_err_t device_info_get_hostname(char *buff, size_t len);
    esp_err_t device_info_get_name(char *buff, size_t len);
    esp_err_t device_info_set_name(const char *name);
    esp_err_t device_info_set_hostname(const char *hostname);

#ifdef __cplusplus
}
#endif
#endif
