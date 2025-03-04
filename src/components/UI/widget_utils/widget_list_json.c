#include "UI.h"
#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "widget.h"


/* Initializes a JSON file with an empty array for widgets */
/* @Parameters: */
/*     - json_path: Path to the JSON file to be created. */
/* @Return: */
/*     - ESP_OK: JSON file successfully created with an empty array. */
/*     - ESP_FAIL: Failed to create JSON object or write to file. */
static esp_err_t create_widget_display_list_json(const char *json_path)
{
    cJSON *widget_array = cJSON_CreateArray();
    if (widget_array == NULL)
    {
        return ESP_FAIL;
    }

    char *widget_array_str = cJSON_Print(widget_array);
    if (widget_array_str == NULL)
    {
        cJSON_Delete(widget_array);
        return ESP_FAIL;
    }

    write_file_fat_fs(json_path, widget_array_str);
    free(widget_array_str);
    cJSON_Delete(widget_array);
    return ESP_OK;
}

/* Reads a JSON file containing a list of widgets and populates the widget linked list */
/* @Parameters: */
/*     - head: Pointer to the head of the linked list where widget nodes will be added. */
/*     - widget_list_json: JSON array of widgets to populate the list from. */
/* @Return: */
/*     - None */
static void populate_widget_list_from_json(widget_node_t **head, cJSON *widget_list_json)
{
    cJSON *json_widget = NULL;
    cJSON_ArrayForEach(json_widget, widget_list_json)
    {
        if (cJSON_IsObject(json_widget)) 
        {
            // Récupérer l'ID et mettre à jour la structure du widget
            cJSON *id = cJSON_GetObjectItem(json_widget, "id");
            if (cJSON_IsNumber(id)) 
            {
                // Créer un nouveau widget et le remplir avec les données JSON
                widget_t *new_widget = NULL;
                if (get_widget_by_type(id->valueint, &new_widget) != ESP_OK)
                {
                    continue;
                }

                // Créer un nouveau node 
                widget_node_t *new_node = create_widget_display_list_node(*head, new_widget);
                if (new_node == NULL)
                {
                    return ;
                }
                *head = new_node;
            }
        }
    }
}

/* Initializes the widget display list by checking if a JSON file exists */
/* If the file exists, it reads and populates the linked list; otherwise, creates a new JSON file */
/* @Parameters: */
/*     - head: Pointer to the head of the widget linked list to be populated. */
/*     - json_path: Path to the JSON file for reading or initializing. */
/* @Return: */
/*     - None */
void init_widget_display_list_from_file(widget_node_t **head, const char *json_path)
{
    mount_fat_fs();

    if (check_file_fat_fs(json_path) == ESP_OK) 
    {
        cJSON *widget_list_json = read_json_file(json_path, READ_FAT);
        if (widget_list_json != NULL || !cJSON_IsArray(widget_list_json))
        {
            populate_widget_list_from_json(head, widget_list_json);
        }
        cJSON_Delete(widget_list_json);
    } 
    else 
    {
        create_widget_display_list_json(json_path);
    }

    unmount_fat_fs();
}

/* Creates a JSON array from the current widget linked list and writes it to a JSON file */
/* @Parameters: */
/*     - head: Pointer to the head of the widget linked list to serialize to JSON. */
/* @Return: */
/*     - ESP_OK: JSON array successfully created and written to file. */
/*     - ESP_FAIL: Failed to create JSON array or write to file. */
esp_err_t update_widget_display_list_json(widget_node_t *head, uint8_t screen_id)
{
    cJSON *json_array = cJSON_CreateArray();
    if (json_array == NULL)
    {
        return ESP_FAIL;
    }

    widget_node_t *current = head;
    while (current != NULL)
    {
        cJSON *json_widget = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_widget, "id", current->widget->type);
        cJSON_AddStringToObject(json_widget, "status", "TODO ?");
        cJSON_AddItemToArray(json_array, json_widget);
        current = current->next;
    }

    char *widget_list_str = cJSON_Print(json_array);
    if (widget_list_str == NULL)
    {
        cJSON_Delete(json_array);
        return ESP_FAIL;
    }

    char json_path_file[WIDGET_INDEX_PATH_LEN];
    snprintf(json_path_file, sizeof(json_path_file), "%s%d%s", WIDGET_INDEX_PATH_BASE, screen_id, WIDGET_INDEX_PATH_EXT);

    mount_fat_fs();
    write_file_fat_fs(json_path_file, widget_list_str);
    unmount_fat_fs();

    free(widget_list_str);
    cJSON_Delete(json_array);
    return ESP_OK;
}
