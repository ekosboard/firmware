#include "main.h"
#include "esp_event.h"
#include "esp_sleep.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "hal/gpio_types.h"
#include "portmacro.h"
#include "soc/gpio_num.h"
#include "state_manager.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define BTN_GPIO  GPIO_NUM_1

static void init_button(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BTN_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_HIGH_LEVEL
    };
    gpio_config(&io_conf);
    gpio_wakeup_enable(BTN_GPIO, GPIO_INTR_HIGH_LEVEL);
    esp_sleep_enable_gpio_wakeup();
}

static TaskHandle_t setup_task_handle[SETUP_TASK_COUNT];

void app_main(void)
{
    init_button();
    vTaskDelay(pdMS_TO_TICKS(5000));

    xTaskCreate(power_manager_task,
            "power_manager_task",
            4096,
            &setup_task_handle[UPDATE_MANAGER_TASK],
            3,
            &setup_task_handle[POWER_MANAGER_TASK]
            );

    xTaskCreate(update_manager_task,
            "update_manager_task",
            4096,
            &setup_task_handle[POWER_MANAGER_TASK],
            3,
            &setup_task_handle[UPDATE_MANAGER_TASK]
            );

    xTaskCreate(setup_ui_tasks,
            "setup_ui",
            4096,
            NULL,
            2,
            &setup_task_handle[SETUP_UI_TASK]
            );

    xTaskCreate(setup_timeout_task,
            "setup_timeout",
            4096,
            NULL,
            2,
            &setup_task_handle[SETUP_TIMEOUT_TASK]
            );

    state_manager_init(setup_task_handle);
    esp_event_post_to(state_manager_loop,
            INIT_EVENT,
            INIT_BEGIN,
            NULL,
            0,
            portMAX_DELAY
            );
}
