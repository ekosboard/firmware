#include "main.h"
#include "screen_manager.h"

/* Handles UI-related tasks based on notifications */
/* @Parameters: */
/*     - pvParameters: Pointer to the task parameters, not used in this implementation. */
/* @Behavior: */
/*     - Waits indefinitely for a task notification before proceeding. */
/*     - Checks if a valid screen ID exists in NVS; if so, starts widget and screen manager tasks. */
/* @Return: */
/*     - None */
void setup_ui_tasks(void *pvParameters)
{
    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            if (nvs_setup_state_read_screen_id() != -1)
            {
                xTaskCreate(widget_manager_task, "widget_manager_task", 4096, NULL, 2, NULL);
                xTaskCreate(screen_manager_task, "screen_manager_task", (4096 * 2), NULL, 2, NULL);
            }
        }
    }
}
