#include "main.h"

/* Initializes the hardware setup, including NVS and default configuration states */
/* @Parameters: */
/*     - pvParameters: Pointer to the task parameters, not used in this implementation. */
/* @Behavior: */
/*     - Waits for a task notification before proceeding. */
/*     - Initializes the default event loop and NVS interface. */
/*     - Reads the setup state from NVS; if not found, writes default values. */
/*     - Notifies the "setup_ui" task once the hardware setup is complete. */
/* @Return: */
/*     - None */
void setup_hardware(void *pvParameters)
{
    setup_state_t setup_state;
    esp_err_t ret;
    TaskHandle_t setup_ui_handle = NULL;

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("HARDWARE", "NOTIF");
            ESP_ERROR_CHECK(esp_event_loop_create_default());
            ESP_ERROR_CHECK(nvs_init_interface());

            ret = nvs_setup_state_read_all(&setup_state);
            if (ret == ESP_ERR_NOT_FOUND)
            {
                setup_state.magic_key = SETUP_MAGIC_KEY;
                setup_state.setup_status = -1;
                setup_state.network_status = -1;
                setup_state.screen_id = 0;
                setup_state.timestamp = 0;
                memcpy(setup_state.timezone, "NA", 3);
                nvs_setup_state_write_all(&setup_state);
                nvs_setup_state_write_magic_key();
            }
            setup_ui_handle = xTaskGetHandle("setup_ui");
            if (setup_ui_handle != NULL)
                xTaskNotifyGive(setup_ui_handle);
        }
    }
}
