#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_wifi.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "main.h"
#include "portmacro.h"
#include "state_manager.h"
#include <stdint.h>


/**
 * @brief Manages power state and handles sleep transitions.
 * @param pvParameters Pointer to the task parameters, expected to be a TaskHandle_t* for update_manager_task.
 * @details
 * - Waits for a notification containing a wake-up time and a Wi-Fi requirement flag.
 * - Stops Wi-Fi if it was previously needed and is no longer required.
 * - Configures and enters light sleep mode.
 * - Upon wake-up:
 *   - If the wake-up was triggered by a GPIO event, posts an event to `state_manager_loop`.
 *   - If the wake-up was triggered by a timer, restarts Wi-Fi if needed and notifies `update_manager_task`.
 * @note
 * - The notification value is a bitmask:
 *   - Lower bits (`TIMER_MASK`) store the sleep duration.
 *   - The `WIFI_REQUIRED` flag indicates if Wi-Fi should be restarted after sleep.
 * - Uses `esp_sleep_enable_timer_wakeup()` and `esp_light_sleep_start()` for sleep management.
 * - Ensures wake-up reason is valid before proceeding.
 */
void power_manager_task(void *pvParameters)
{
    TaskHandle_t *update_manager_task_handle = (TaskHandle_t*)pvParameters;
    uint32_t wakeup_time;
    static bool wifi_needed_to_stop = true;

    while (42)
    {
        if (xTaskNotifyWait(0, ULONG_MAX, &wakeup_time, portMAX_DELAY) == pdPASS)
        {
            uint32_t timer_value = wakeup_time & TIMER_MASK;
            bool wifi_needed_to_start = (wakeup_time & WIFI_REQUIRED) != 0;

            ESP_LOGI("POWER MANAGER: ", "get notif: %lu\n wifi needed: %d", timer_value, wifi_needed_to_start);

            if (wifi_needed_to_stop == true)
            {
                esp_wifi_stop();
                wifi_needed_to_stop = false;
            }

            // Programmer le sleep
            ESP_LOGW("POWER MANAGER: ", "sleep start");
            esp_sleep_enable_timer_wakeup(timer_value * 1000ULL);
            esp_light_sleep_start();

            while (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UNDEFINED)
            {
                __asm__("nop");
            }

            esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
            ESP_LOGW("POWER MANAGER", "Wakeup reason: %d", wakeup_reason);

            if (wakeup_reason == ESP_SLEEP_WAKEUP_GPIO) // ISR
            {
                ESP_LOGW("POWER MANAGER: ", "awake: GPIO");
                wifi_needed_to_stop = true;
                esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
                esp_event_post_to(state_manager_loop, CONFIG_EVENT, CONFIG_BEGIN_ISR, NULL, 0, portMAX_DELAY);
            }
            else if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER)
            {
                ESP_LOGW("POWER MANAGER: ", "awake: TIMER");
                if (wifi_needed_to_start == true)
                {
                    esp_wifi_start();
                    wifi_needed_to_stop = true;
                }
                xTaskNotifyGive(*update_manager_task_handle);
            }
        }
    }
}
