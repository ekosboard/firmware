#include "ota_context.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_ota_ops.h"
#include <string.h>
#include <stdio.h>

static const char *TAG = "ota_ctx";
static ota_context_t s_ctx;

void ota_context_init(void)
{
    memset(&s_ctx, 0, sizeof(s_ctx));
    s_ctx.lock = xSemaphoreCreateMutex();
    s_ctx.in_progress = false;
    s_ctx.offset = 0;
    s_ctx.total_size = 0;
}

static void _lock(void)   { xSemaphoreTake(s_ctx.lock, portMAX_DELAY); }
static void _unlock(void) { xSemaphoreGive(s_ctx.lock); }

esp_err_t ota_context_start(size_t total_size, const char *session_id)
{
    _lock();

    if (s_ctx.in_progress)
    {
        _unlock();
        ESP_LOGW(TAG, "OTA already in progress");
        return ESP_ERR_INVALID_STATE;
    }

    const esp_partition_t *update_partition = esp_ota_get_next_update_partition(NULL);
    if (update_partition == NULL)
    {
        _unlock();
        ESP_LOGE(TAG, "No OTA partition found");
        return ESP_FAIL;
    }

    esp_err_t err = esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &s_ctx.handle);
    if (err != ESP_OK)
    {
        _unlock();
        ESP_LOGE(TAG, "esp_ota_begin failed: %s", esp_err_to_name(err));
        return err;
    }

    s_ctx.update_partition = update_partition;
    s_ctx.offset = 0;
    s_ctx.total_size = total_size;
    s_ctx.in_progress = true;
    if (session_id)
    {
        strncpy(s_ctx.session_id, session_id, sizeof(s_ctx.session_id)-1);
        s_ctx.session_id[sizeof(s_ctx.session_id)-1] = '\0';
    }
    else
    {
        s_ctx.session_id[0] = '\0';
    }

    ESP_LOGI(TAG, "OTA started on partition %s (size=%u)",
             update_partition->label, (unsigned)total_size);

    _unlock();
    return ESP_OK;
}


esp_err_t ota_context_write(size_t offset, const uint8_t *data, size_t len, size_t *written)
{
    if (written)
        *written = 0;

    _lock();
    if (!s_ctx.in_progress)
    {
        _unlock();
        return ESP_ERR_INVALID_STATE;
    }
    if (offset != s_ctx.offset)
    {
        // offset mismatch: caller should resend from correct offset
        _unlock();
        return ESP_ERR_INVALID_SIZE;
    }

    esp_err_t err = esp_ota_write(s_ctx.handle, (const void*)data, len);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_ota_write failed: %s", esp_err_to_name(err));
        _unlock();
        return err;
    }

    s_ctx.offset += len;
    if (written)
        *written = len;

    _unlock();
    return ESP_OK;
}

esp_err_t ota_context_commit(void)
{
    _lock();
    if (!s_ctx.in_progress)
    {
        _unlock();
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = esp_ota_end(s_ctx.handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_ota_end failed: %s", esp_err_to_name(err));
        // keep in_progress true so we can abort/respond properly
        _unlock();
        return err;
    }

    // set boot partition to the newly written one
    err = esp_ota_set_boot_partition(s_ctx.update_partition);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_ota_set_boot_partition failed: %s", esp_err_to_name(err));
        _unlock();
        return err;
    }

    // keep the context info for status until reboot or explicit abort
    s_ctx.in_progress = false;
    _unlock();
    ESP_LOGI(TAG, "OTA commit success, new partition set: %s", s_ctx.update_partition->label);
    return ESP_OK;
}


esp_err_t ota_context_abort(void)
{
    _lock();
    if (!s_ctx.in_progress)
    {
        _unlock();
        return ESP_ERR_INVALID_STATE;
    }
    // Not much to do: we simply mark not in progress and reset handle
    // esp_ota_abort is not part of IDF API; to discard we just mark it aborted.
    s_ctx.in_progress = false;
    s_ctx.offset = 0;
    s_ctx.total_size = 0;
    s_ctx.session_id[0] = '\0';
    _unlock();
    ESP_LOGI(TAG, "OTA aborted");
    return ESP_OK;
}


void ota_context_get_status(size_t *offset, size_t *total_size, bool *in_progress)
{
    _lock();

    if (offset)
        *offset = s_ctx.offset;

    if (total_size)
        *total_size = s_ctx.total_size;

    if (in_progress)
        *in_progress = s_ctx.in_progress;

    _unlock();
}


const esp_partition_t* ota_context_get_update_partition(void)
{
    const esp_partition_t *p;
    _lock();
    p = s_ctx.update_partition;
    _unlock();
    return p;
}

