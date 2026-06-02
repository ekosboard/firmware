#include "main.h"
#include "esp_event.h"
#include "freertos/idf_additions.h"
#include "portmacro.h"
#include "screen_scheduler_task.h"
#include "state_manager.h"
#include "wake_coordinator.h"
#include <stdbool.h>


static TaskHandle_t setup_task_handle[SETUP_TASK_COUNT];

void app_main(void)
{

    xTaskCreate(power_manager_task,
            "power_manager_task",
            4096,
            &setup_task_handle,
            3,
            &setup_task_handle[POWER_MANAGER_TASK]);

    xTaskCreate(update_manager_task,
            "update_manager_task",
            (4096 * 2),
            &setup_task_handle[POWER_MANAGER_TASK],
            3,
            &setup_task_handle[UPDATE_MANAGER_TASK]);

    xTaskCreate(setup_ui_tasks,
            "setup_ui",
            4096,
            NULL,
            2,
            &setup_task_handle[SETUP_UI_TASK]);

    xTaskCreate(setup_timeout_task,
            "setup_timeout",
            4096,
            NULL,
            2,
            &setup_task_handle[SETUP_TIMEOUT_TASK]);

    xTaskCreate(screen_scheduler_task,
            "screen_scheduler",
            4096,
            &setup_task_handle[UPDATE_MANAGER_TASK],
            3,
            &setup_task_handle[SCREEN_SCHEDULER_TASK]);

    wake_coordinator_init(&setup_task_handle[POWER_MANAGER_TASK]);
    state_manager_init(setup_task_handle);
    esp_event_post_to(state_manager_loop,
            INIT_EVENT,
            INIT_BEGIN,
            NULL,
            0,
            portMAX_DELAY);

}
