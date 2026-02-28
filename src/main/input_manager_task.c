#include "UI.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_flash_partitions.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "input_manager.h"
#include "main.h"
#include "screen_manager.h"

static QueueHandle_t input_event_queue;
static TaskHandle_t input_manager_task_handle;
static TaskHandle_t input_event_task_handle;

static void handle_switch_1(input_event_t event);
static void handle_switch_2(input_event_t event);

static input_switch_ctx_t switches[] = {
    {
        .source = INPUT_SOURCE_SWITCH_1,
        .gpio = SWITCH_1_GPIO,
    },
    {
        .source = INPUT_SOURCE_SWITCH_2,
        .gpio = SWITCH_2_GPIO,
    }
};

#define SWITCH_COUNT (sizeof(switches) / sizeof(switches[0]))

void suspend_input_manager_task(void)
{
    if (input_manager_task_handle != NULL)
    {
        vTaskSuspend(input_manager_task_handle);
        ESP_LOGI("", "Input manager task suspended");
    }
}

void resume_input_manager_task(void)
{
    if (input_manager_task_handle)
    {
        vTaskResume(input_manager_task_handle);
        ESP_LOGI("", "Input manager task resumed");
    }
}

static inline bool switch_is_pressed(gpio_num_t gpio)
{
    return gpio_get_level(gpio) == 0; // pull-up
}

void input_manager_task(void *pvParameters)
{
    ESP_LOGI("INPUT_MANAGER_TASK", "Created!");
    while (42)
    {
        for (int i = 0; i < SWITCH_COUNT; i++)
        {
            input_switch_ctx_t *sw = &switches[i];
            sw->event_type = switch_is_pressed(sw->gpio) ? INPUT_EVENT_PRESS : INPUT_EVENT_RELEASE;
            /* ESP_LOGI("INPUT_MANAGER_TASK", "Switch event: %d\nSource: %d", sw->event_type, sw->source); */

            if ((sw->event_type == INPUT_EVENT_PRESS) && (sw->prev_event_type == INPUT_EVENT_RELEASE))
            {
                ESP_LOGI("INPUT_MANAGER_TASK", "SW_PRESSED!");
                sw->press_start_ms = esp_log_timestamp();
            }

            if ((sw->event_type == INPUT_EVENT_RELEASE) && (sw->prev_event_type == INPUT_EVENT_PRESS)) 
            {
                uint32_t duration = esp_log_timestamp() - sw->press_start_ms;

                input_event_t event = {
                    .source = sw->source,
                    .duration_ms = duration
                };

                if (duration < 500) 
                {
                    event.type = INPUT_EVENT_SHORT;
                }
                else if (duration < 3000)
                {
                    event.type = INPUT_EVENT_LONG;
                }
                else
                {
                    event.type = INPUT_EVENT_LONG_LONG;
                }

                xQueueSend(input_event_queue, &event, 0);
            }

            sw->prev_event_type = sw->event_type;
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void input_event_task(void *pvParameters)
{
    uint32_t        last_long_press_ms = 0;
    input_source_t  last_long_source = INPUT_SOURCE_NONE;
    input_event_t   event;
    ESP_LOGI("INPUT_EVENT_TASK", "Created!");

    while (42) {
        if (xQueueReceive(input_event_queue, &event, portMAX_DELAY))
        {
            ESP_LOGI("INPUT_EVENT_TASK", "GET_NOTIF!");
            uint32_t now = esp_log_timestamp();

            if (event.type == INPUT_EVENT_LONG)
            {
                if (last_long_press_ms && \
                        (now - last_long_press_ms < 2000) && \
                        last_long_source != event.source)
                {

                    ESP_LOGW("INPUT", "LONG + LONG => REBOOT");
                    /* system_reboot(); */
                    last_long_press_ms = 0;
                    continue;
                }

                last_long_press_ms = now;
                last_long_source = event.source;
            }

            switch (event.source)
            {

                case INPUT_SOURCE_SWITCH_1:
                    handle_switch_1(event);
                    break;

                case INPUT_SOURCE_SWITCH_2:
                    handle_switch_2(event);
                    break;

                default:
                    break;
            }
        }
    }
}

static uint8_t screen_next_id(uint8_t current)
{
    return (current + 1) % MAX_SCREEN;
}

static uint8_t screen_prev_id(uint8_t current)
{
    return (current + MAX_SCREEN - 1) % MAX_SCREEN;
}

static void handle_switch_1(input_event_t event)
{
    display_t *display = get_main_display();

    switch (event.type)
    {
        // Screen next
        case INPUT_EVENT_SHORT:
            ESP_LOGI("HANDLE_SWITCH_1", \
                    "INPUT_EVENT_SHORT \
                    \nActive screen: %"PRIu8" \
                    \nNext screen: %"PRIu8"", \
                    display->active_screen, screen_next_id(display->active_screen));

            /* notify_screen_manager(SCREEN_ACTION_SWITCH, screen_next_id(display->active_screen)); */
            notify_screen_manager(SCREEN_ACTION_DRAW_ONLY, screen_next_id(display->active_screen));
            break;

        // Notify screen manager clear + redrawn
        case INPUT_EVENT_LONG:
            // clear ghosting
            ESP_LOGI("HANDLE_SWITCH_1", "Clear ghosting");
            notify_screen_manager(SCREEN_ACTION_FORCE_REFRESH, display->active_screen);
            epd_wait_flush_complete(pdMS_TO_TICKS(15000));
            break;

        case INPUT_EVENT_LONG_LONG:
            //reboot
            ESP_LOGI("HANDLE_SWITCH_1", "INPUT_EVENT_LONG_LONG");
            break;

        default:
            break;
    }
}

static void handle_switch_2(input_event_t event)
{
    display_t *display = get_main_display();

    switch (event.type)
    {
        // Screen prev
        case INPUT_EVENT_SHORT:
            ESP_LOGI("HANDLE_SWITCH_2", \
                    "INPUT_EVENT_SHORT \
                    \nActive screen: %"PRIu8" \
                    \nPrev screen: %"PRIu8"", \
                    display->active_screen, screen_prev_id(display->active_screen));

            /* notify_screen_manager(SCREEN_ACTION_SWITCH, screen_prev_id(display->active_screen)); */
            notify_screen_manager(SCREEN_ACTION_DRAW_ONLY, screen_prev_id(display->active_screen));
            break;

        // Config complete
        case INPUT_EVENT_LONG:
            ESP_LOGI("HANDLE_SWITCH_2", "INPUT_EVENT_LONG");
            TaskHandle_t setup_timeout_task_handle = xTaskGetHandle("setup_timeout");
            if (setup_timeout_task_handle == NULL)
                break;

            xTaskNotify(setup_timeout_task_handle, 0, eSetValueWithOverwrite);
            break;

        case INPUT_EVENT_LONG_LONG:
            //reboot
            ESP_LOGI("HANDLE_SWITCH_2", "INPUT_EVENT_LONG_LONG");
            break;

        default:
            break;
    }
}

static esp_err_t init_input_event_queue(void)
{
    input_event_queue = xQueueCreate(MAX_INPUT_EVENT_QUEUE, sizeof(input_event_t));
    if (input_event_queue == NULL)
        return ESP_FAIL;

    return ESP_OK;
}

esp_err_t init_input_manager_task(void)
{
    ESP_LOGI("INIT_INPUT_MANAGER_TASK", "Start init");
    gpio_config_t io_conf = {
        .pin_bit_mask = ((1ULL << SWITCH_1_GPIO) | (1ULL << SWITCH_2_GPIO)),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    if (init_input_event_queue() != ESP_OK)
        ESP_LOGE("INIT_INPUT_MANAGER_TASK", "Error init input queue");

    xTaskCreate(input_manager_task,
            "input",
            4096,
            NULL,
            2,
            &input_manager_task_handle);

    xTaskCreate(input_event_task,
            "input_event",
            4096,
            NULL,
            2,
            &input_event_task_handle);

    if (input_manager_task_handle == NULL || input_event_task_handle == NULL)
        return ESP_FAIL;

    ESP_LOGI("INIT_INPUT_MANAGER_TASK", "Finish init");
    return ESP_OK;
}
