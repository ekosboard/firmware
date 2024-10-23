#include "main.h"
#include "esp_log.h"

void app_main(void)
{
    ESP_ERROR_CHECK(esp_event_loop_create_default()); //TODO: setup fn
    init_display();
    start_wifi();
    http_server();
}
