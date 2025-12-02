#ifndef CONFIG_TIMEOUT_CTX_H
#define CONFIG_TIMEOUT_CTX_H

#include "esp_err.h"
#include "freertos/idf_additions.h"
#include <stdint.h>

typedef struct config_timeout_ctx_s {
    uint32_t            timeout_ms;
    uint64_t            timeout_start_us;
    TaskHandle_t        timeout_task_handle;
    SemaphoreHandle_t   lock;
} config_timeout_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t               config_timeout_ctx_init(TaskHandle_t setup_timeout_task_handle);
    esp_err_t               config_timeout_ctx_set_timeout(uint32_t timeout_ms);
    config_timeout_ctx_t    *config_timeout_ctx_get();

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif
