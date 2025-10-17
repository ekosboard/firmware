#include "esp_event.h"
#include "esp_log.h"
#include "main.h"
#include "portmacro.h"
#include "state_manager.h"


/**
 * @brief Task to handle a configurable timeout for configuration state.
 *
 * Waits for a notification to update the timeout duration. If the timeout
 * elapses without receiving a notification, the task triggers a CONFIG_EXIT
 * event and resets the timeout to infinite (portMAX_DELAY).
 *
 * @param pvParameter Unused parameter required by FreeRTOS task signature.
 */
void setup_timeout_task(void *pvParameter)
{
    uint32_t timeout = portMAX_DELAY;
    uint32_t notification_val;
    TickType_t wait_ticks;

    while (true)
    {
        if (timeout == portMAX_DELAY)
            wait_ticks = portMAX_DELAY;
        else
            wait_ticks = pdMS_TO_TICKS(timeout);

        ESP_LOGI("CONFIG_TIMEOUT", "Attente de %s", (timeout == portMAX_DELAY) ? "infini" : (char[32]){0});
        if (xTaskNotifyWait(0, ULONG_MAX, &notification_val, wait_ticks) == pdFALSE)
        {
            if (timeout != portMAX_DELAY)
            {
                ESP_LOGI("CONFIG_TIMEOUT", "Timeout atteint, retour à l'état IDLE");
                esp_event_post_to(state_manager_loop,
                        CONFIG_EVENT,
                        CONFIG_EXIT,
                        NULL,
                        0,
                        portMAX_DELAY);

                timeout = portMAX_DELAY;
            }
        }
        else
        {
            timeout = notification_val;
            if (timeout == portMAX_DELAY)
                ESP_LOGI("CONFIG_TIMEOUT", "Timeout mis à jour: attente infinie");
            else
                ESP_LOGI("CONFIG_TIMEOUT", "Timeout mis à jour: %"PRIu32" ms", timeout);
        }
    }
}
