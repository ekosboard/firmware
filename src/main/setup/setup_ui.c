#include "main.h"

/* Sets up the user interface and manages screen initialization */
/* @Parameters: */
/*     - pvParameters: Pointer to the task parameters, not used in this implementation. */
/* @Behavior: */
/*     - Waits for a task notification before proceeding. */
/*     - Initializes the UI and screen manager tasks. */
/*     - Checks if a valid screen ID exists in NVS; if so, starts widget and screen manager tasks. */
/*     - Notifies the "setup_network" task once the UI setup is complete. */
/* @Return: */
/*     - None */
void setup_ui(void *pvParameters)
{
    TaskHandle_t setup_network_handle = NULL;

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("UI", "NOTIF");
            ESP_ERROR_CHECK(init_ui());
            if (nvs_setup_state_read_screen_id() != -1)
            {
                xTaskCreate(widget_manager_task, "widget_manager_task", 4096, NULL, 2, NULL);
                xTaskCreate(screen_manager_task, "screen_manager_task", 4096, NULL, 2, NULL);
            }
            setup_network_handle = xTaskGetHandle("setup_network");
            if (setup_network_handle != NULL)
                xTaskNotifyGive(setup_network_handle);
        }
    }
}
