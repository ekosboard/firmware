#ifndef OTA_CONTEXT_H
#define OTA_CONTEXT_H

#include <stdbool.h>
#include "esp_partition.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_ota_ops.h"

typedef struct {
    esp_ota_handle_t        handle;
    const esp_partition_t   *update_partition;
    size_t                  offset;        // bytes written so far
    size_t                  total_size;    // 0 if unknown
    bool                    in_progress;
    char                    session_id[33];  // null-terminated session id (optional)
    SemaphoreHandle_t       lock;
} ota_context_t;

#ifdef __cplusplus
extern "C" {
#endif


    void        ota_context_init(void);
    esp_err_t   ota_context_start(size_t total_size, const char *session_id);
    esp_err_t   ota_context_write(size_t offset, const uint8_t *data, size_t len, size_t *written);
    esp_err_t   ota_context_commit(void);
    esp_err_t   ota_context_abort(void);
    void        ota_context_get_status(size_t *offset, size_t *total_size, bool *in_progress);

    const esp_partition_t* ota_context_get_update_partition(void);

#ifdef __cplusplus
}
#endif
#endif
