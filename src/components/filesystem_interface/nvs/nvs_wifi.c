#include "filesystem_interface.h"
#include <stddef.h>
#include <stdio.h>


/* Writes Wi-Fi credentials (SSID and password) to the NVS (Non-Volatile Storage). */
/* Parameters: */
/* - Pointer to the SSID string to be stored. */
/* - Pointer to the password string to be stored. */
/* @Return Values: */
/* - ESP_OK if the credentials are written successfully. */
/* - an error code (esp_err_t) indicating the type of failure if an operation fails. */
esp_err_t nvs_wifi_write_credential(char *ssid, char *password)
{
    nvs_handle_t nvs_wifi;
    esp_err_t ret;

    ret = nvs_open("wifi_info", NVS_READWRITE, &nvs_wifi);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_str(nvs_wifi, "ssid", ssid);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_str(nvs_wifi, "password", password);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_commit(nvs_wifi);
    if (ret != ESP_OK)
        return ret;

    nvs_close(nvs_wifi);
    return ret;
}

/* Reads Wi-Fi credentials (SSID and password) from the NVS (Non-Volatile Storage). */
/* @Parameters: */
/* - Buffer to store the retrieved SSID string. */
/* - Size of the SSID buffer. The size is updated with the actual size of the stored string upon successful read. */
/* - Buffer to store the retrieved password string. */
/* - Size of the password buffer. The size is updated with the actual size of the stored string upon successful read. */
/* @Return Values: */
/* - ESP_OK if the credentials are read successfully. */
/* - an error code (esp_err_t) indicating the type of failure if an operation fails. */
esp_err_t nvs_wifi_read_credential(char *ssid_buf, size_t ssid_buf_size, char *password_buf, size_t password_buf_size)
{
    nvs_handle_t nvs_wifi;
    esp_err_t ret;

    ret = nvs_open("wifi_info", NVS_READONLY, &nvs_wifi);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_get_str(nvs_wifi, "ssid", ssid_buf, &ssid_buf_size);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_get_str(nvs_wifi, "password", password_buf, &password_buf_size);
    if (ret != ESP_OK)
        return ret;

    nvs_close(nvs_wifi);
    return ret;
}
