#include "esp_wifi.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "wifi.h"
#include "wifi_switch.h"
#include "esp_log.h"
#include <stdbool.h>

static const char *TAG = "wifi_switch_task";
static TaskHandle_t wifi_swtich_task_handle = NULL;
static bool wifi_is_switching = false;

void wifi_switch_task(void *pvParameter)
{
    wifi_switch_request_t req;

    while (42)
    {
        if (pop_wifi_switch_queue(&req) == ESP_OK)
        {
            ESP_LOGI(TAG, "WiFi switch request received: %s", req.ssid);
            vTaskDelay(pdMS_TO_TICKS(200));

            wifi_is_switching = true;

            esp_wifi_disconnect();

            // Attendre proprement l’évènement de déconnexion
            xEventGroupWaitBits(s_wifi_event_group,
                    WIFI_STA_FAIL_BIT,
                    pdTRUE,
                    pdFALSE,
                    pdMS_TO_TICKS(3000));

            wifi_config_t new_config = {};
            strcpy((char*)new_config.sta.ssid, req.ssid);
            strcpy((char*)new_config.sta.password, req.pass);

            esp_wifi_set_config(WIFI_IF_STA, &new_config);
            esp_wifi_connect();

            xEventGroupClearBits(s_wifi_event_group, WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT);
            EventBits_t bits = xEventGroupWaitBits(
                    s_wifi_event_group,
                    WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT,
                    pdTRUE,
                    pdFALSE,
                    pdMS_TO_TICKS(15000)
                    );

            if (bits & WIFI_STA_CONNECTED_BIT)
            {
                ESP_LOGI(TAG, "WiFi switch successful");
                nvs_wifi_write_credential(req.ssid, req.pass);
            }
            else
            {
                ESP_LOGW(TAG, "WiFi switch failed");
                wifi_start_sta();
            }

            wifi_is_switching = false;
        }
    }
}

TaskHandle_t *wifi_swtich_task_get_handle(void)
{
    return &wifi_swtich_task_handle;
}

bool check_wifi_is_switching()
{
    return wifi_is_switching;
}
