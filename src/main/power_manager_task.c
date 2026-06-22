#include "UI.h"
#include "driver/gpio.h"
#include "esp_bit_defs.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "lvgl_tick.h"
#include "main.h"
#include "portmacro.h"
#include "soc/gpio_num.h"
#include "state_manager.h"
#include "wifi.h"
#include <stdint.h>


static void enable_gpio_wakeup()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = ((1ULL << GPIO_NUM_3) | (1ULL << GPIO_NUM_4)),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_LOW_LEVEL
    };
    gpio_config(&io_conf);
    gpio_wakeup_enable(GPIO_NUM_3, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable(GPIO_NUM_4, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
}

static void disable_gpio_wakeup()
{
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_GPIO);

    gpio_wakeup_disable(GPIO_NUM_3);
    gpio_wakeup_disable(GPIO_NUM_4);

    gpio_intr_disable(GPIO_NUM_3);
    gpio_intr_disable(GPIO_NUM_4);

    gpio_set_intr_type(GPIO_NUM_3, GPIO_INTR_DISABLE);
    gpio_set_intr_type(GPIO_NUM_4, GPIO_INTR_DISABLE);

    while (gpio_get_level(GPIO_NUM_3) == 0 || \
            gpio_get_level(GPIO_NUM_4) == 0)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    gpio_config_t io_conf = {
        .pin_bit_mask = ((1ULL << GPIO_NUM_3) | (1ULL << GPIO_NUM_4)),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

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
    TaskHandle_t *setup_task_handle = (TaskHandle_t*)pvParameters;

    uint32_t wakeup_time;
    static bool wifi_needed_to_stop = true;
    display_t *display = get_main_display();

    while (42)
    {
        if (xTaskNotifyWait(0, ULONG_MAX, &wakeup_time, portMAX_DELAY) == pdPASS)
        {
            uint32_t timer_value = wakeup_time & TIMER_MASK;
            bool wifi_needed_to_start = (wakeup_time & WIFI_REQUIRED) != 0;

            ESP_LOGI("POWER MANAGER",
                    "Get notif: %" PRIu32
                    " | wifi needed: %d",
                    timer_value,
                    wifi_needed_to_start);

            if (lvgl_tick_stop() != ESP_OK)
                ESP_LOGE("POWER MANAGER", "LVGL timer stop errorr");

            if (wifi_needed_to_stop == true)
            {
                clean_stop_wifi();
                xEventGroupClearBits(s_wifi_event_group, WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT);
                //FIXME: utiliser WIFI_EVENT_STA_STOP
                vTaskDelay(pdMS_TO_TICKS(2000));
                wifi_needed_to_stop = false;
            }

            // Programmer le sleep
            ESP_LOGW("POWER MANAGER: ", "sleep start");
            esp_sleep_enable_timer_wakeup(timer_value * 1000ULL);
            enable_gpio_wakeup();

            esp_light_sleep_start();
            while (esp_sleep_get_wakeup_causes() & BIT(ESP_SLEEP_WAKEUP_UNDEFINED))
            {
                __asm__("nop");
            }

            uint32_t wakeup_reason = esp_sleep_get_wakeup_causes();
            ESP_LOGW("POWER MANAGER", "Wakeup reason: %d", wakeup_reason);
            disable_gpio_wakeup();

            if (lvgl_tick_start() != ESP_OK)
                ESP_LOGE("POWER MANAGER", "LVGL timer start errorr");

            display->display_driver->set_basemap(epd_get_basemap());

            if (wakeup_reason & BIT(ESP_SLEEP_WAKEUP_GPIO)) // ISR
            {
                ESP_LOGW("POWER MANAGER: ", "awake: GPIO");
                clean_start_wifi();
                wifi_needed_to_stop = true;
                esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
                esp_event_post_to(state_manager_loop, CONFIG_EVENT, CONFIG_BEGIN_ISR, NULL, 0, portMAX_DELAY);
            }
            else if (wakeup_reason & BIT(ESP_SLEEP_WAKEUP_TIMER))
            {
                ESP_LOGW("POWER MANAGER: ", "awake: TIMER");
                if (wifi_needed_to_start == true)
                {
                    clean_start_wifi();
                    wifi_needed_to_stop = true;
                }
                xTaskNotifyGive(setup_task_handle[SCREEN_SCHEDULER_TASK]);
            }
        }
    }
}
