#include "main.h"

/* Initializes the network setup and starts necessary services */
/* @Parameters: */
/*     - pvParameters: Pointer to the task parameters, not used in this implementation. */
/* @Behavior: */
/*     - Waits for a task notification before proceeding. */
/*     - Starts the Wi-Fi connection process. */
/*     - Checks the network status in NVS; if connected, starts the HTTP server. */
/*     - Notifies the "app_start" task once the network setup is complete. */
/* @Return: */
/*     - None */
void setup_network(void *pvParameters)
{
    TaskHandle_t app_start_handle = NULL;

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("NETWORK", "NOTIF");
            start_wifi();
            if (nvs_setup_state_read_network_status() == STA_CONNECTED)
            {
                xTaskCreate(http_server, "http_server", 4096, NULL, 2, NULL);
            }
            app_start_handle = xTaskGetHandle("app_start");
            if (app_start_handle != NULL)
                xTaskNotifyGive(app_start_handle);
        }
    }
}
