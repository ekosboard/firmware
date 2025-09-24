#include "filesystem_interface.h"
#include "wifi.h"

/* Initializes SNTP to synchronize ESP32 system time with an NTP server */
/* and sets the timezone to Europe/Paris. */
/* https://www.iana.org/time-zones */
/* @Parameters: */ 
/*     - A pointer to a POSIX timezone string, such as "CET-1CEST,M3.5.0,M10.5.0/3" */
/*     for Europe/Paris. */
/* @Return: */
/*     - ESP_OK on successful time update */
/*     - ESP_FAIL if synchronization fails. */
esp_err_t init_sntp(char *timezone)
{
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    esp_netif_sntp_init(&config);

    if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK) 
    {
        ESP_LOGE("wifi SNTP", "Failed to update system time within 10s timeout");
        return ESP_FAIL;
    }

    time_t now = time(NULL);
    struct tm timeinfo;
    char strftime_buf[64];

    setenv("TZ", timezone, 1);
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    nvs_setup_state_write_timestamp((int64_t)now);

    ESP_LOGI("wifi SNTP", "The current date/time in Paris is: %s", strftime_buf);

    esp_netif_sntp_deinit();
    return ESP_OK;
}
