#include "UI.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "hal/aes_types.h"
#include "widget.h"
#include <stdlib.h>

/* Creates a JSON object representing a widget's properties */
/* @Parameters: */
/*     - widget: A widget_t structure containing the widget's information to be converted into JSON. */
/* @Return: */
/*     - A pointer to a cJSON object representing the widget, or NULL if an error occurs during the creation of the JSON object. */
static cJSON *create_widget_json(widget_t widget)
{
    cJSON *widget_json = cJSON_CreateObject();

    if (widget_json == NULL)
    {
        return NULL;
    }

    // Ajout de la propriété "type"
    cJSON_AddNumberToObject(widget_json, "type", widget.type);

    // Création et ajout de l'objet "pos"
    cJSON *pos = cJSON_CreateObject();
    if (pos == NULL) {
        cJSON_Delete(widget_json);
        return NULL;
    }
    cJSON_AddNumberToObject(pos, "x", widget.pos_x);
    cJSON_AddNumberToObject(pos, "y", widget.pos_y);
    cJSON_AddItemToObject(widget_json, "pos", pos);

    // Création et ajout de l'objet "size"
    cJSON *size = cJSON_CreateObject();
    if (size == NULL) {
        cJSON_Delete(widget_json);
        return NULL;
    }
    cJSON_AddNumberToObject(size, "height", widget.height);
    cJSON_AddNumberToObject(size, "width", widget.width);
    cJSON_AddItemToObject(widget_json, "size", size);

    // Ajout de la propriété "flag"
    cJSON_AddNumberToObject(widget_json, "flag", widget.flag);

    return widget_json;
}

/* Updates a widget structure using the data from a JSON object */
/* @Parameters: */
/*     - widget: Pointer to a widget_t structure to be updated with data from JSON. */
/*     - widget_json: Pointer to a cJSON object containing the widget's data. */
/* @Return: */
/*     - None. This function directly modifies the widget structure. */
void update_widget_struct_from_json(widget_t *widget, cJSON *widget_json) {
    cJSON *type = cJSON_GetObjectItem(widget_json, "type");
    cJSON *pos = cJSON_GetObjectItem(widget_json, "pos");
    cJSON *size = cJSON_GetObjectItem(widget_json, "size");
    cJSON *flag = cJSON_GetObjectItem(widget_json, "flag");

    if (cJSON_IsNumber(type)) {
        widget->type = type->valueint;
    }
    if (cJSON_IsObject(pos)) {
        cJSON *x = cJSON_GetObjectItem(pos, "x");
        cJSON *y = cJSON_GetObjectItem(pos, "y");
        if (cJSON_IsNumber(x) && cJSON_IsNumber(y)) {
            widget->pos_x = x->valueint;
            widget->pos_y = y->valueint;
        }
    }
    if (cJSON_IsObject(size)) {
        cJSON *height = cJSON_GetObjectItem(size, "height");
        cJSON *width = cJSON_GetObjectItem(size, "width");
        if (cJSON_IsNumber(height) && cJSON_IsNumber(width)) {
            widget->height = height->valueint;
            widget->width = width->valueint;
        }
    }
    if (cJSON_IsNumber(flag)) {
        widget->flag = flag->valueint;
    }
}

/* Initializes a widget from a JSON file, or creates a new one if the file doesn't exist */
/* @Parameters: */
/*     - widget: Pointer to a widget_t structure to be initialized. */
/*     - json_path: Path to the JSON file containing the widget's data. */
/* @Return: */
/*     - None. This function modifies the widget structure and writes to the file system if necessary. */
void init_widget_from_file(widget_t *widget, const char *json_path)
{
    cJSON *widget_json = NULL;
    if (check_file_fat_fs(json_path) == ESP_OK) 
    {
        widget_json = read_json_file(json_path);
        if (widget_json != NULL)
        {
            update_widget_struct_from_json(widget, widget_json);
        }
    } 
    else 
    {
        widget_json = create_widget_json(*widget);
        if (widget_json != NULL) 
        {
            char *widget_str = cJSON_Print(widget_json);
            if (widget_str != NULL)
            {
                write_file_fat_fs(json_path, widget_str);
                free(widget_str);
            }
        }
    }
    cJSON_Delete(widget_json);
}

/* Generates the filename for a widget's JSON file based on its type */
/* @Parameters: */
/*     - widget_type: The type of the widget to generate the filename for. */
/* @Return: */
/*     - A dynamically allocated string containing the widget's filename with ".json" extension, or NULL if memory allocation fails. */
static char *get_widget_filename_with_json(widget_type_t widget_type)
{
    const char *widget_name = get_widget_type_to_string(widget_type);
    size_t len = strlen(widget_name) + 6;  // 5 caractères pour ".json" + 1 pour le '\0'
    char *filename = malloc(len);
    if (filename == NULL)
    {
        return NULL;
    }

    snprintf(filename, len, "%s.json", widget_name);
    return filename;
}


/* Updates the JSON file representing a widget from its structure */
/* @Parameters: */
/*     - widget: Pointer to the widget_t structure to be converted into JSON and written to the file. */
/* @Return: */
/*     - None. This function modifies the file system by writing the widget's data to a JSON file. */
void update_widget_json_from_struct(widget_t *widget)
{
    mount_fat_fs();
    cJSON *widget_json = create_widget_json(*widget);
    if (widget_json != NULL) 
    {
        char *widget_str = cJSON_Print(widget_json);
        char *widget_filename = get_widget_filename_with_json(widget->type);
        if (widget_str != NULL && widget_filename != NULL)
        {
            write_file_fat_fs(widget_filename, widget_str);
            free(widget_str);
            free(widget_filename);
        }
    }
    cJSON_Delete(widget_json);
    unmount_fat_fs();
}
