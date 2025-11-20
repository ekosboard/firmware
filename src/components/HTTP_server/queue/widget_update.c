#include "HTTP_server.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "portmacro.h"
#include "widget.h"

static QueueHandle_t widget_update_queue;


/* Initialize the widget update queue. */
/* @return: */
/*     - ESP_OK: Queue created successfully. */
/*     - ESP_FAIL: Queue creation failed. */
esp_err_t init_widget_update_queue(void)
{
    widget_update_queue = xQueueCreate(MAX_WIDGETS_QUEUE, sizeof(widget_update_t));
    if (widget_update_queue == NULL)
        return ESP_FAIL;

    return ESP_OK;
}

/* Delete the widget update queue. */
void delete_widget_update_queue(void)
{
    vQueueDelete(widget_update_queue);
    widget_update_queue = NULL;
}

/* Push a widget update to the queue. */
/* @Parameters: */
/*     - Pointer to the widget update to be queued. */
/* @Return: */
/*     - ESP_OK: Successfully added to the queue. */
/*     - ESP_FAIL: Queue is either uninitialized or full within the timeout (100ms). */
esp_err_t push_widget_update_queue(widget_update_t *widget)
{
    if (widget_update_queue != NULL)
    {
        if (xQueueSend(widget_update_queue, widget, pdMS_TO_TICKS(100)) == pdTRUE)
            return ESP_OK;
    }
    return ESP_FAIL;
}

/* Pop a widget update from the queue, blocking until an item is available. */
/* @Parameters: */
/*     - Pointer to the widget update where the dequeued item will be stored. */
/* @Return: */
/*     - ESP_OK: Successfully retrieved from the queue. */
/*     - ESP_FAIL: Queue is uninitialized or unavailable. */
esp_err_t pop_widget_update_queue(widget_update_t *widget)
{
    if (widget_update_queue != NULL)
    {
        if (xQueueReceive(widget_update_queue, widget, portMAX_DELAY) == pdTRUE)
            return ESP_OK;
    }
    return ESP_FAIL;
}
