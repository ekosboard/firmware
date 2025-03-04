#include "esp_err.h"
#include "esp_log.h"
#include "esp_littlefs.h"
#include "filesystem_interface.h"

static const esp_vfs_littlefs_conf_t conf = {
    .base_path = "/widget_fs",
    .partition_label = "widget_fs",
    .format_if_mount_failed = true,
    .dont_mount = false,
};

/* Mounts the LittleFS partition for file access */
/* @Parameters: */
/*     - None */
/* @Behavior: */
/*     - Attempts to mount the LittleFS partition using the configured settings. */
/*     - Logs an error if mounting fails. */
/*     - Retrieves and logs the total and used space of the partition if successful. */
/* @Return: */
/*     - ESP_OK if mounting is successful. */
/*     - ESP_FAIL if mounting fails (e.g., partition not found or initialization error). */
esp_err_t mount_lfs()
{
    ESP_LOGI("MOUNT LittleFS", );

    esp_err_t ret = esp_vfs_littlefs_register(&conf);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE("MOUNT LittleFS", "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE("MOUNT LittleFS", "Failed to find LittleFS partition");
        }
        else
        {
            ESP_LOGE("MOUNT LittleFS", "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    size_t total = 0, used = 0;
    ret = esp_littlefs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE("MOUNT LittleFS", "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI("MOUNT LittleFS", "Partition size: total: %d, used: %d", total, used);
    }

    return ESP_OK;
}

/* Unmounts the LittleFS partition to free system resources */
/* @Parameters: */
/*     - None */
/* @Behavior: */
/*     - Unregisters the LittleFS partition, making it unavailable for further file operations. */
/* @Return: */
/*     - ESP_OK if unmounting is successful. */
/*     - ESP_FAIL if an error occurs. */
esp_err_t unmount_lfs()
{
    ESP_LOGI("UNMOUNT LittleFS",);
    esp_err_t err = esp_vfs_littlefs_unregister(conf.partition_label);
    if (err != ESP_OK)
    {
        return ESP_FAIL;
    }

    return ESP_OK;
}
