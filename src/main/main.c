#include "main.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_event_loop_create_default()); //TODO: setup fn
    init_display();
    start_wifi();

    xTaskCreate(http_server, "http_server", 4096, NULL, 2, NULL);
}
