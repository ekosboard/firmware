#include "main.h"

/* Main application task responsible for orchestrating setup tasks */
/* @Parameters: */
/*     - pvParameters: Pointer to the task parameters, not used in this implementation. */
/* @Behavior: */
/*     - Creates tasks for hardware, UI, and network setup. */
/*     - Sends an initial notification to the "setup_hardware" task. */
/*     - Monitors setup progress and writes the setup status to NVS upon completion. */
/*     - Notifies the screen manager to draw the active screen once setup is finished. */
/* @Return: */
/*     - None */
void app_start(void *pvParameters)
{
    xTaskCreate(setup_hardware, "setup_hardware", 4096, NULL, 2, NULL);
    xTaskCreate(setup_ui, "setup_ui", 4096, NULL, 2, NULL);
    xTaskCreate(setup_network, "setup_network", 4096, NULL, 2, NULL);

    TaskHandle_t setup_hardware_handle = xTaskGetHandle("setup_hardware");
    if (setup_hardware_handle != NULL)
        xTaskNotifyGive(setup_hardware_handle);

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("APP_START", "NOTIF");
            nvs_setup_state_write_setup_status(0);

            //Create a task awaiting for notif
            vTaskDelay(pdMS_TO_TICKS(15000));
            setup_state_t setup_state;
            nvs_setup_state_read_all(&setup_state);
            if (setup_state.setup_status != -1)
            {
                display_t *display = get_main_display();
                notify_screen_manager(SCREEN_ACTION_DRAW_WITH_DRIVER, display->active_screen);
            }
        }
    }
}

void app_main(void)
{
    xTaskCreate(app_start, "app_start", 4096, NULL, 2, NULL);
}
