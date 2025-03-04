#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "sys/dirent.h"
#include <string.h>


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

    DIR *d = opendir("/widget_fs");
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

    char full_path[128];
    snprintf(full_path, sizeof(full_path), "/widget_fs/%s", json_file_path);

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

/* List and logs all files founds in "/widget_fs" */
esp_err_t list_files_lfs()
{
    DIR *dir = opendir("/widget_fs");
    if (dir == NULL) {
        ESP_LOGE("LS LittleFS", "Failed to open directory %s", "/widget_fs");
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
