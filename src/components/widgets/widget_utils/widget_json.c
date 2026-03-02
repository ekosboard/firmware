#include "UI.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "widget.h"
#include "widget_config_list.h"
#include "widget_template_interval.h"
#include <stdlib.h>

/* Creates a JSON object representing a widget's properties */
/* @Parameters: */
/*     - widget: A widget_t structure containing the widget's information to be converted into JSON. */
/* @Return: */
/*     - A pointer to a cJSON object representing the widget, or NULL if an error occurs during the creation of the JSON object. */
static cJSON *create_widget_json(const widget_t *widget)
{
    if (!widget) 
        return NULL;

    cJSON *root = cJSON_CreateObject();
    if (!root)
        return NULL;

    // Champs simples
    cJSON_AddNumberToObject(root, "id", widget->type);
    cJSON_AddStringToObject(root, "widget_type", get_widget_type_to_string(widget->type));
    /* cJSON_AddNumberToObject(root, "widget_type", widget->type); */
    cJSON_AddNumberToObject(root, "width", widget->width);
    cJSON_AddNumberToObject(root, "height", widget->height);
    cJSON_AddNumberToObject(root, "flag", widget->flag);

    char interval_str[32];
    widget_template_format_interval_ms(widget->update_data_interval_ms, interval_str, sizeof(interval_str));
    cJSON_AddStringToObject(root, "update_interval", interval_str);

    // Position (x, y)
    cJSON *pos = cJSON_AddObjectToObject(root, "position");
    if (pos)
    {
        cJSON_AddNumberToObject(pos, "x", widget->pos_x);
        cJSON_AddNumberToObject(pos, "y", widget->pos_y);
    }

    // Config (liste chaînée key/value)
    if (widget->config)
    {
        cJSON *config = cJSON_AddObjectToObject(root, "config");
        if (config)
        {
            widget_config_t *current = widget->config;
            while (current)
            {
                cJSON_AddStringToObject(config, current->key, current->value);
                current = current->next;
            }
        }
    }

    return root;
}

/* Updates a widget structure using the data from a JSON template */
/* @Parameters: */
/*     - widget: Pointer to a widget_t structure to be updated with data from JSON. */
/*     - widget_json: Pointer to a cJSON object containing the widget's data. */
/* @Return: */
/*     - None. This function directly modifies the widget structure. */
void update_widget_struct_from_template(widget_t *widget, cJSON *widget_json)
{
    // Champs fixes
    cJSON *type = cJSON_GetObjectItem(widget_json, "widget_type");
    if (cJSON_IsNumber(type))
        widget->type = type->valueint;

    cJSON *pos = cJSON_GetObjectItem(widget_json, "position");
    if (cJSON_IsObject(pos))
    {
        cJSON *x = cJSON_GetObjectItem(pos, "x");
        cJSON *y = cJSON_GetObjectItem(pos, "y");
        if (cJSON_IsNumber(x))
            widget->pos_x = x->valueint;
        if (cJSON_IsNumber(y))
            widget->pos_y = y->valueint;
    }

    cJSON *height = cJSON_GetObjectItem(widget_json, "height");
    cJSON *width = cJSON_GetObjectItem(widget_json, "width");
    if (cJSON_IsNumber(height))
        widget->height = height->valueint;
    if (cJSON_IsNumber(width))
        widget->width = width->valueint;

    cJSON *update_interval = cJSON_GetObjectItem(widget_json, "update_interval");
    if (cJSON_IsString(update_interval))
        widget->update_data_interval_ms = widget_template_parse_interval_ms(update_interval->valuestring);

    cJSON *flag = cJSON_GetObjectItem(widget_json, "flag");
    if (cJSON_IsNumber(flag))
        widget->flag = (uint32_t)flag->valuedouble;

    // Champs dynamiques: config
    cJSON *config = cJSON_GetObjectItem(widget_json, "config");
    if (cJSON_IsObject(config))
    {
        cJSON *entry = NULL;
        cJSON_ArrayForEach(entry, config)
        {
            if (cJSON_IsString(entry))
            {
                widget->config = widget_config_list_create_node(widget->config,
                                                          entry->string,
                                                          entry->valuestring);
            }
        }
    }
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
    mount_lfs();
    cJSON *widget_json = create_widget_json(widget);
    if (widget_json != NULL) 
    {
        char *widget_str = cJSON_Print(widget_json);
        char *widget_filename = get_widget_filename_with_json(widget->type);
        if (widget_str != NULL && widget_filename != NULL)
        {
            char instance_path[MAX_PATH_LEN];
            lfs_get_instance_path(widget_filename, instance_path, sizeof(instance_path));
            write_file_lfs(instance_path, widget_str);
            free(widget_str);
            free(widget_filename);
        }
    }
    cJSON_Delete(widget_json);
    unmount_lfs();
}
