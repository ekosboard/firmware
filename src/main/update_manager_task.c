#include "UI.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "esp_timer.h"

#define MERGE_THRESHOLD_MS 5000  // Regroupe les updates ayant moins de 1s d'écart

/**
 * @brief Task responsible for managing widget updates.
 *
 * This task listens for notifications and updates widgets based on their scheduled
 * update intervals. If multiple widgets have updates scheduled within a short time
 * window, their updates are merged to minimize wake-ups and optimize power consumption.
 *
 * Behavior:
 * - If the elapsed time since the last update exceeds the interval, the widget is updated.
 * - If a widget update is scheduled within `MERGE_THRESHOLD_MS`, it is updated immediately.
 * - Widgets requiring WiFi wait for a connection before updating.
 * - Notifies `power_manager_handle` with the next update delay.
 *
 * @param pvParameters Pointer to the power manager task handle.
 */
void update_manager_task(void *pvParameters)
{
    TaskHandle_t *power_manager_handle = (TaskHandle_t*)pvParameters;
    bool wifi_required = true;
    uint32_t next_update_delay = UINT32_MAX;
    uint64_t current_time;
    uint64_t elapsed_time;
    uint64_t time_until_next_update;
    screen_t *screen = NULL;
    widget_node_t *current = NULL;
    EventBits_t wifi_event_bits;

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("UPDATE MANAGER", "GET NOTIF");

            next_update_delay = UINT32_MAX;
            current_time = xTaskGetTickCount() * portTICK_PERIOD_MS;

            current_time = esp_timer_get_time() / 1000; // Convertir en millisecondes
            screen = get_active_screen();
            current = screen->widget_display_list;

            while (current != NULL)
            {
                elapsed_time = current_time - current->widget->update_data_timestamp;
                ESP_LOGI("UPDATE MANAGER", "Current time: %lld\n Widget update_data_timestamp: %ld\n elapsed_time: %lld\n", current_time, current->widget->update_data_timestamp, elapsed_time);
                if (elapsed_time >= current->widget->update_data_interval_ms)
                {
                    if (current->widget->flag & WIFI_REQUIRED)
                    {
                        wifi_required = true;
                    }
                    else
                    {
                        current->widget->update_data_function();
                        current->widget->update_data_timestamp = current_time;
                    }
                }


                time_until_next_update = (current->widget->update_data_timestamp + current->widget->update_data_interval_ms) - current_time;
                ESP_LOGI("UPDATE MANAGER", "time_until_next_update: %lld\n", time_until_next_update);
                if (time_until_next_update < MERGE_THRESHOLD_MS)
                {
                    ESP_LOGI("UPDATE MANAGER", "Merging update for widget scheduled in %lld ms", time_until_next_update);
                    current->widget->update_data_function();
                    current->widget->update_data_timestamp = current_time;
                    time_until_next_update = current->widget->update_data_interval_ms;
                }
                if (time_until_next_update < next_update_delay)
                {
                    ESP_LOGI("UPDATE MANAGER", "Schedule next update delay");
                    next_update_delay = time_until_next_update;
                }

                current = current->next;
            }

            if (wifi_required)
            {
                wifi_event_bits = xEventGroupWaitBits(s_wifi_event_group,
                                                      WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT,
                                                      pdFALSE,
                                                      pdFALSE,
                                                      pdMS_TO_TICKS(5000));
                if (wifi_event_bits & WIFI_STA_CONNECTED_BIT)
                {
                    current = screen->widget_display_list;
                    while (current != NULL)
                    {
                        if (current->widget->flag & WIFI_REQUIRED)
                        {
                            current->widget->update_data_function();
                            current->widget->update_data_timestamp = current_time;
                        }
                        current = current->next;
                    }
                }
                next_update_delay |= WIFI_REQUIRED;
                wifi_required = false;
            }

            /* xEventGroupWaitBits(get_epd_event_group(), */
            /*         EPD_EVENT_FLUSH_COMPLETE, */
            /*         pdTRUE, */
            /*         pdFALSE, */
            /*         portMAX_DELAY); */

            ESP_LOGI("UPDATE MANAGER: ", "send notif: %ld\n wifi asked: %d", next_update_delay & TIMER_MASK, (next_update_delay & WIFI_REQUIRED) != 0);
            xTaskNotify(*power_manager_handle, next_update_delay, eSetValueWithOverwrite);
        }
    }
}

