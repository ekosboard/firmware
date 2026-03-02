#include "config_timeout_ctx.h"
#include "esp_err.h"
#include "esp_timer.h"
#include <stdlib.h>

static config_timeout_ctx_t *config_timeout_ctx;


esp_err_t   config_timeout_ctx_init(TaskHandle_t setup_timeout_task_handle)
{
    if (!setup_timeout_task_handle)
        return ESP_FAIL;

    config_timeout_ctx = calloc(1, sizeof(config_timeout_ctx_t));
    if (!config_timeout_ctx)
        return ESP_ERR_NO_MEM;

    config_timeout_ctx->timeout_task_handle = setup_timeout_task_handle;
    config_timeout_ctx->lock = xSemaphoreCreateMutex();
    if (!config_timeout_ctx->lock)
    {
        free(config_timeout_ctx);
        config_timeout_ctx = NULL;
        return ESP_ERR_NO_MEM;
    }

    return ESP_OK;
}

esp_err_t   config_timeout_ctx_set_timeout(uint32_t timeout_ms)
{
    xSemaphoreTake(config_timeout_ctx->lock, portMAX_DELAY);
    config_timeout_ctx->timeout_ms = timeout_ms;
    config_timeout_ctx->timeout_start_us = esp_timer_get_time();
    xSemaphoreGive(config_timeout_ctx->lock);
    return ESP_OK;
}

config_timeout_ctx_t *config_timeout_ctx_get()
{
    return config_timeout_ctx;
}
