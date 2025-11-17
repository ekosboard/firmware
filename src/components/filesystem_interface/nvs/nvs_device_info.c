#include "device_info.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs.h"
#include <stdio.h>
#include <string.h>

static const char *TAG = "device_info";
static const char *NAMESPACE = "device_info";

void device_info_set_defaults(device_info_t *info)
{
    memset(info, 0, sizeof(device_info_t));
    strcpy(info->device_name, "EKOS");
    strcpy(info->hostname, "ekos.local");
    strcpy(info->firmware_version, "0.0.1");
    strcpy(info->serial, "UNINITIALIZED");
}

esp_err_t device_info_load(device_info_t *info)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGW(TAG, "No device_info namespace found, loading defaults");
        device_info_set_defaults(info);
        return ESP_OK;
    }
    else if (err != ESP_OK)
    {
        return err;
    }

    size_t size;

    size = sizeof(info->device_name);
    err = nvs_get_str(nvs_handle, "device_name", info->device_name, &size);
    if (err != ESP_OK)
    {
        strcpy(info->device_name, "EKOS");
        goto cleanup;
    }

    size = sizeof(info->hostname);
    err = nvs_get_str(nvs_handle, "hostname", info->hostname, &size);
    if (err != ESP_OK)
    {
        strcpy(info->hostname, "ekos.local");
        goto cleanup;
    }

    size = sizeof(info->firmware_version);
    err = nvs_get_str(nvs_handle, "fw_version", info->firmware_version, &size);
    if (err != ESP_OK)
    {
        strcpy(info->firmware_version, "0.0.1");
        goto cleanup;
    }

    size = sizeof(info->serial);
    err = nvs_get_str(nvs_handle, "serial", info->serial, &size);
    if (err != ESP_OK)
    {
        strcpy(info->serial, "UNINITIALIZED");
        goto cleanup;
    }

cleanup:
    nvs_close(nvs_handle);
    return err;
}

esp_err_t device_info_save(const device_info_t *info)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_str(nvs_handle, "device_name", info->device_name);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_set_str(nvs_handle, "hostname", info->hostname);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_set_str(nvs_handle, "fw_version", info->firmware_version);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_set_str(nvs_handle, "serial", info->serial);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return err;
}

esp_err_t device_info_get_name(char *buff, size_t len)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
        return err;

    err = nvs_get_str(nvs_handle, "device_name", buff, &len);
    if (err != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return err;
}

esp_err_t device_info_set_name(const char *name)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_str(nvs_handle, "device_name", name);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return err;
}

esp_err_t device_info_get_hostname(char *buff, size_t len)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
        return err;

    err = nvs_get_str(nvs_handle, "hostname", buff, &len);
    if (err != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return err;
}

esp_err_t device_info_set_hostname(const char *hostname)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_str(nvs_handle, "hostname", hostname);
    if (err != ESP_OK)
        goto cleanup;

    err = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return err;
}
