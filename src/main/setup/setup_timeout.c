#include "esp_event.h"
#include "esp_log.h"
#include "main.h"
#include "portmacro.h"
#include "state_manager.h"


void setup_timeout_task(void *pvParameter)
{
    uint32_t timeout = portMAX_DELAY;
    uint32_t notification_val;

    while (42) {
        ESP_LOGI("CONFIG_TIMEOUT", "Attente de %ld ms", timeout);

        if (xTaskNotifyWait(0, ULONG_MAX, &notification_val, pdMS_TO_TICKS(timeout)) == pdFALSE) 
        {
            ESP_LOGI("CONFIG_TIMEOUT", "Timeout atteint, retour à l'état IDLE");
            esp_event_post_to(state_manager_loop, CONFIG_EVENT, CONFIG_EXIT, NULL, 0, portMAX_DELAY);
            timeout = portMAX_DELAY;
        } 
        else 
        {
            timeout = notification_val;
            ESP_LOGI("CONFIG_TIMEOUT", "Timeout mis à jour: %ld ms", timeout);
        }
    }
}
