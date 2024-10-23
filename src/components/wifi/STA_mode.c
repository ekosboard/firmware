#include "esp_err.h"
#include "esp_wifi.h"
#include "wifi.h"

static const char *TAG = "wifi STA_mode";

/* Checks if the ESP32 is already connected to the network specified by the given SSID. */
/* @Parameters: */
/* - A pointer to a string containing the SSID of the network to check. */
/* @Return: */
/* - ESP_OK: If the ESP32 is not connected or is connected to a different network. */
/* - ESP_FAIL: If the ESP32 is already connected to the network with the given SSID. */
esp_err_t wifi_connected_to(char *ssid)
{
    wifi_mode_t current_mode;
    esp_wifi_get_mode(&current_mode);

    if (current_mode == WIFI_MODE_STA || current_mode == WIFI_MODE_APSTA)
    {
        // Si en STA || APSTA, check si une connexion est active
        wifi_ap_record_t ap_info;
        if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK)
        {
            // Check si le SSID est différent avant de changer
            if (strcmp((char*)ap_info.ssid, ssid) == 0)
            {
                // Pas besoin de changer de réseau
                return ESP_FAIL;
            }
        }
    }
    return ESP_OK;
}

/* Initializes the STA (station) configuration by reading the Wi-Fi credentials stored in NVS (Non-Volatile Storage) and applying them to the ESP32's Wi-Fi interface. */
/* @Return: */
/* - ESP_OK: If the Wi-Fi configuration was successfully applied. */
/* - ESP_FAIL: If an error occurs while reading the Wi-Fi credentials from NVS or applying the configuration. */
esp_err_t wifi_init_sta(void)
{
    esp_err_t err;
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = {0},
            .password = {0}
        },
    };
    err = nvs_wifi_read_credential((char*)wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid), (char*)wifi_config.sta.password, sizeof(wifi_config.sta.password));
    if (err != ESP_OK)
    {
        ESP_LOGI(TAG, "ERREUR: %s", esp_err_to_name(err));
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "READ: SSID: %s\tPASS:%s", wifi_config.sta.ssid, wifi_config.sta.password);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    return ESP_OK;
}

/* Starts the Wi-Fi connection in station mode, checks if a connection to the stored SSID is already active, and attempts to connect. Then waits for either a successful connection or a failure event. */
/* @Return: */
/* - ESP_OK: If the connection to the Wi-Fi network was successfully established. */
/* - ESP_FAIL: If the connection fails or if the SSID is already connected. */
/* @Notes: */
/* This function calls wifi_init_sta() to initialize the STA configuration and wifi_connected_to() to verify if the ESP32 is already connected to the specified network. */
/* @@It waits until the ESP32 is either connected or the connection attempt fails. */
esp_err_t wifi_start_sta(void)
{
    esp_err_t err;
    wifi_config_t wifi_config;

    err = wifi_init_sta();
    if (err != ESP_OK)
        return ESP_FAIL;

    err = esp_wifi_get_config(WIFI_IF_STA, &wifi_config);
    if (err != ESP_OK)
        return ESP_FAIL;

    err = wifi_connected_to((char*)wifi_config.sta.ssid);
    if (err != ESP_OK)
        return ESP_FAIL;

    esp_wifi_connect();

    /* Waiting until either the connection is established (WIFI_STA_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_STA_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_STA_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "Connected to ap SSID:%s password:%s", wifi_config.sta.ssid, wifi_config.sta.password);
        return ESP_OK;
    }
    else if (bits & WIFI_STA_FAIL_BIT)
    {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s", wifi_config.sta.ssid, wifi_config.sta.password);
        return ESP_FAIL;
    }
    else
    {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
        return ESP_FAIL;
    }
}
