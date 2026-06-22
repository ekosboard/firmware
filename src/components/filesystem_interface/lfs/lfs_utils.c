#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "dirent.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>


/* Updates the JSON file containing the list of available widget templates */
/* @Parameters: */
/*     - json_file_path: Path to the JSON file where the list should be saved. */
/* @Behavior: */
/*     - Opens the LittleFS partition and scans for widget template files. */
/*     - Creates a JSON array containing the names of all detected widget templates. */
/*     - Writes the JSON array to the specified file in LittleFS. */
/* @Return: */
/*     - ESP_OK if the operation is successful. */
/*     - ESP_FAIL if an error occurs (e.g., failure to open directory, memory allocation issues, or file write failure). */
esp_err_t update_file_index_json(const char *json_file_path)
{

    char template_dir[MAX_PATH_LEN];
    snprintf(template_dir, sizeof(template_dir),"%s/%s", LFS_BASE_PATH, LFS_TEMPLATE_DIR);

    DIR *d = opendir(template_dir);
    if (d == NULL) 
    {
        return ESP_FAIL;
    }

    cJSON *files_array = cJSON_CreateArray();
    if (files_array == NULL)
    {
        closedir(d);
        return ESP_FAIL;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
        {
            if (strcmp(dir->d_name, json_file_path + 1) == 0)
            {
                continue;
            }
            cJSON_AddItemToArray(files_array, cJSON_CreateString(dir->d_name));
        }
    }

    closedir(d);

    char full_path[MAX_PATH_LEN];
    snprintf(full_path, sizeof(full_path), "%s/%s", LFS_BASE_PATH, json_file_path);

    FILE *file = fopen(full_path, "w");
    if (file == NULL)
    {
        cJSON_Delete(files_array);
        return ESP_FAIL;
    }

    char *json_str = cJSON_Print(files_array);
    if (json_str != NULL)
    {
        fprintf(file, "%s", json_str);
        free(json_str);
    }
    else 
    {
        return ESP_FAIL;
    }

    fclose(file);
    cJSON_Delete(files_array);
    return ESP_OK;
}

/* List and logs all files founds in LFS_BASE_PATH */
esp_err_t list_files_lfs()
{
    DIR *dir = opendir(LFS_BASE_PATH);
    if (dir == NULL) {
        ESP_LOGE("LS LittleFS", "Failed to open directory %s", LFS_BASE_PATH);
        return ESP_FAIL;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            ESP_LOGI("LS LittleFS", "Found file: %s", entry->d_name);
        }
    }

    closedir(dir);
    return ESP_OK;
}

/**
 * @brief Builds the full path to a file stored in the LFS partition.
 *
 * This helper concatenates the base path, subdirectory, and filename
 * into a single full path string.
 *
 * @param dir         Subdirectory (e.g. LFS_TEMPLATE_DIR or LFS_INSTANCE_DIR)
 * @param filename    File name (e.g. "status_bar.json")
 * @param out_path    Output buffer for the resulting path
 * @param out_size    Size of the output buffer
 *
 * @return ESP_OK on success, or ESP_FAIL if the buffer size is insufficient
 *         or any argument is invalid.
 */
static esp_err_t lfs_build_path(const char *dir, const char *filename, char *out_path, size_t out_size)
{
    if (!dir || !filename || !out_path)
        return ESP_FAIL;

    int written = snprintf(out_path, out_size,"%s/%s/%s", LFS_BASE_PATH, dir, filename);
    if (written < 0 || written >= out_size)
    {
        return ESP_FAIL; // buffer trop petit
    }

    return ESP_OK;
}

/**
 * @brief Returns the full path to a template file.
 *
 * Builds the complete path to a template JSON file stored in the
 * LFS template directory.
 *
 * @param filename    JSON file name (e.g. "status_bar.json")
 * @param out_path    Output buffer for the resulting path
 * @param out_size    Size of the output buffer
 *
 * @return ESP_OK on success, or ESP_FAIL if the buffer size is insufficient
 *         or any argument is invalid.
 */
esp_err_t lfs_get_template_path(const char *filename, char *out_path, size_t out_size)
{
    return lfs_build_path(LFS_TEMPLATE_DIR, filename, out_path, out_size);
}

/**
 * @brief Returns the full path to an instance file.
 *
 * Builds the complete path to an instance JSON file stored in the
 * LFS instance directory.
 *
 * @param filename    JSON file name (e.g. "status_bar.json")
 * @param out_path    Output buffer for the resulting path
 * @param out_size    Size of the output buffer
 *
 * @return ESP_OK on success, or ESP_FAIL if the buffer size is insufficient
 *         or any argument is invalid.
 */
esp_err_t lfs_get_instance_path(const char *filename, char *out_path, size_t out_size)
{
    return lfs_build_path(LFS_INSTANCE_DIR, filename, out_path, out_size);
}

/* Checks if a file exists on the LFS */
/* @Parameters: */
/*     - path: Path to the file to check. */
/* @Return: */
/*     - ESP_OK: The file exists on the file system. */
/*     - ESP_FAIL: The file does not exist on the file system. */
esp_err_t check_file_lfs(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0)
    {
        return ESP_OK;
    }

    ESP_LOGI("CHECK FILE LFS", "path: %s", path);
    return ESP_FAIL;
}

/* Writes data to a file on the LFS */
/* @Parameters: */
/*     - path: Path to the file where data should be written. */
/*     - data: The data to write to the file. */
/* @Return: */
/*     - ESP_OK: Successfully wrote data to the file. */
/*     - ESP_FAIL: Failed to write data to the file. */
esp_err_t write_file_lfs(const char *path, char *data)
{
    ESP_LOGI("WRITE LFS", "Path: %s\nData:%s", path, data);

    FILE *f = fopen(path, "wb");
    if (f == NULL)
    {
        ESP_LOGI("WRITE LFS", "Failed to open file for writing, errno: %d", errno);
        return ESP_FAIL;
    }

    fprintf(f, "%s", data);
    fclose(f);

    return ESP_OK;
}

