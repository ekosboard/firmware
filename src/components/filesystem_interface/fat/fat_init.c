#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"
#include "filesystem_interface.h"

// Mount path for the partition
const char *base_path = "/spiflash";
static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;


/* Mounts the FAT file system on SPI Flash for read/write access */
/* @Parameters: */
/*     - None */
/* @Return: */
/*     - ESP_OK: Successfully mounted the file system. */
/*     - ESP_FAIL: Failed to mount the file system. */
esp_err_t mount_fat_fs()
{
    ESP_LOGI("MOUNT FLASH", );
    const esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
        .use_one_fat = false,
    };

    esp_err_t err = esp_vfs_fat_spiflash_mount_rw_wl(base_path, "fatfs", &mount_config, &s_wl_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE("MOUNT FLASH", "Error mounting FAT partition: %s", esp_err_to_name(err));
        return ESP_FAIL;
    }

    return ESP_OK;
}

/* Unmounts the FAT file system on SPI Flash */
/* @Parameters: */
/*     - None */
/* @Return: */
/*     - ESP_OK: Successfully unmounted the file system. */
/*     - ESP_FAIL: Failed to unmount the file system. */
esp_err_t unmount_fat_fs()
{
    ESP_LOGI("UNMOUNT FLASH", );
    esp_err_t err = esp_vfs_fat_spiflash_unmount_rw_wl(base_path, s_wl_handle);
    if (err != ESP_OK)
    {
        return ESP_FAIL;
    }

    return ESP_OK;
}

/* Checks if a file exists on the FAT file system stored on SPI Flash */
/* @Parameters: */
/*     - path: Path to the file to check. */
/* @Return: */
/*     - ESP_OK: The file exists on the file system. */
/*     - ESP_FAIL: The file does not exist on the file system. */
esp_err_t check_file_fat_fs(const char *path)
{
    char full_path[128];
    struct stat st;

    snprintf(full_path, sizeof(full_path), "/spiflash/%s", path);
    if (stat(full_path, &st) == 0)
    {
        return ESP_OK;
    }

    ESP_LOGI("CHECK FILE FLASH", "path: %s", path);
    return ESP_FAIL;
}

/* Writes data to a file on the FAT file system stored on SPI Flash */
/* @Parameters: */
/*     - path: Path to the file where data should be written. */
/*     - data: The data to write to the file. */
/* @Return: */
/*     - ESP_OK: Successfully wrote data to the file. */
/*     - ESP_FAIL: Failed to write data to the file. */
esp_err_t write_file_fat_fs(const char *path, char *data)
{
    char full_path[128];

    snprintf(full_path, sizeof(full_path), "/spiflash/%s", path);
    ESP_LOGI("WRITE FAT", "Path: %s\nData:%s", full_path, data);
    FILE *f = fopen(full_path, "wb");
    if (f == NULL)
    {
        ESP_LOGI("WRITE FAT", "Failed to open file for writing, errno: %d", errno);
        return ESP_FAIL;
    }

    fprintf(f, "%s", data);
    fclose(f);

    return ESP_OK;
}

/* Reads the first line of a file from the FAT file system stored on SPI Flash */
/* @Parameters: */
/*     - path: Path to the file to read. */
/*     - len: The length of the buffer for storing the file's line. */
/* @Return: */
/*     - ESP_OK: Successfully read the file's line. */
/*     - ESP_FAIL: Failed to read the file. */
esp_err_t read_file_fat_fs(const char *path, int len)
{
    char full_path[128];

    snprintf(full_path, sizeof(full_path), "/spiflash/%s", path);
    FILE *f = fopen(full_path, "rb");
    if (f == NULL)
    {
        return ESP_FAIL;
    }

    char line[len];
    fgets(line, sizeof(line), f);
    fclose(f);

    // strip newline
    char *pos = strchr(line, '\n');
    if (pos)
    {
        *pos = '\0';
    }
    return ESP_OK;
}

