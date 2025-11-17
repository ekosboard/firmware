#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "wifi_switch.h"

static QueueHandle_t wifi_switch_queue;

esp_err_t init_wifi_switch_queue(void)
{
    wifi_switch_queue = xQueueCreate(2, sizeof(wifi_switch_request_t));
    if (!wifi_switch_queue)
        return ESP_FAIL;
    return ESP_OK;
}

void delete_wifi_switch_queue(void)
{
    vQueueDelete(wifi_switch_queue);
    wifi_switch_queue = NULL;
}

esp_err_t push_wifi_switch_queue(wifi_switch_request_t req)
{
    if (wifi_switch_queue != NULL)
    {
        if (xQueueSend(wifi_switch_queue, &req, pdMS_TO_TICKS(100)) == pdTRUE)
            return ESP_OK;
    }
    return ESP_FAIL;
}

esp_err_t pop_wifi_switch_queue(wifi_switch_request_t *req)
{
    if (wifi_switch_queue != NULL)
    {
        if (xQueueReceive(wifi_switch_queue, req, portMAX_DELAY) == pdTRUE)
            return ESP_OK;
    }
    return ESP_FAIL;
}
