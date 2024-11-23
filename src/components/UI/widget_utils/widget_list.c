#include "UI.h"
#include "esp_err.h"
#include "filesystem_interface.h"
#include "widget.h"
#include "cJSON.h"
#include <stdlib.h>

static widget_t widget_info_list[WIDGET_COUNT];
static uint8_t size_widget_info_list;


/* Initializes the widget information list with predefined widgets */
/* @Parameters: */
/*     - None */
/* @Return: */
/*     - None */
void init_widget_list(void)
{
    uint8_t index = 0;
    mount_fat_fs();

#ifdef CONFIG_WIDGET_STATUS_BAR
    widget_info_list[index] = (widget_t) {
        WIDGET_TYPE_STATUS_BAR,
            NULL,
            NULL,
            0,
            0,
            20,
            100,
            0,
            widget_status_bar_draw,
            widget_status_bar_erase,
            widget_status_bar_update,
    };
    init_widget_from_file(&widget_info_list[index++], STATUS_BAR_FILE_PATH);
#endif

#ifdef CONFIG_WIDGET_SENSOR_BME680
    widget_info_list[index] = (widget_t) {
        WIDGET_TYPE_SENSOR_BME680,
            NULL,
            NULL,
            0,
            100,
            20,
            100,
            0,
            widget_sensor_BME680_draw,
            widget_sensor_BME680_erase,
            widget_sensor_BME680_update,
    };
    init_widget_from_file(&widget_info_list[index++], SENSOR_BME680_FILE_PATH);
#endif

    unmount_fat_fs();

    for (uint8_t i = index; i < WIDGET_COUNT; i++)
    {
        widget_info_list[i] = (widget_t) {
            0
        };
    }

    size_widget_info_list = index;
}


/* Retrieves the widget information list */
/* @Parameters: */
/*     - size: Pointer to store the number of active widgets in the list. */
/* @Return: */
/*     - Pointer to the widget_info_list array containing widget information. */
const widget_t *get_widget_list(uint8_t *size)
{
    if (size)
        *size = size_widget_info_list;
    return widget_info_list;
}

/* Searches for widget information by ID in the widget list */
/* @Parameters: */
/*     - id: The unique identifier for the widget to search. */
/*     - widget_info: Pointer to store the widget information if found. */
/* @Return: */
/*     - ESP_OK: Widget with the specified ID found and info retrieved. */
/*     - ESP_ERR_NOT_FOUND: Widget ID not found in the list. */
esp_err_t get_widget_by_id(const char *id, const widget_t **widget_info)
{
    for (uint8_t i = 0; i < size_widget_info_list; i++)
    {
        if (check_widget_type_by_id(id, widget_info_list[i].type))
        {
            *widget_info = &widget_info_list[i];
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}

/* Searches for widget information by TYPE in the widget list */
/* @Parameters: */
/*     - type: The unique identifier for the widget to search. */
/*     - widget_info: Pointer to store the widget information if found. */
/* @Return: */
/*     - ESP_OK: Widget with the specified type found and info retrieved. */
/*     - ESP_ERR_NOT_FOUND: Widget type not found in the list. */
esp_err_t get_widget_by_type(const widget_type_t type, widget_t **widget_info)
{
    for (uint8_t i = 0; i < size_widget_info_list; i++)
    {
        if (type == widget_info_list[i].type)
        {
            *widget_info = &widget_info_list[i];
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}

/* Updates widget information in the widget list based on widget ID */
/* @Parameters: */
/*     - update: Pointer to a widget_update_t structure containing the updated widget information. */
/* @Return: */
/*     - ESP_OK: Widget information successfully updated. */
/*     - ESP_ERR_INVALID_ARG: Update structure or ID is NULL. */
/*     - ESP_ERR_NOT_FOUND: Widget ID not found in the list. */
esp_err_t update_widget_info(const widget_update_t *update)
{
    if (update == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    for (uint8_t i = 0; i < size_widget_info_list; i++)
    {
        if (widget_info_list[i].type == update->type)
        {
            widget_info_list[i].pos_x = update->pos_x;
            widget_info_list[i].pos_y = update->pos_y;
            widget_info_list[i].width = update->width;
            widget_info_list[i].height = update->height;
            widget_info_list[i].flag = update->flag;

            update_widget_json_from_struct(&widget_info_list[i]);
            return ESP_OK;
        }
    }

    return ESP_ERR_NOT_FOUND;
}

/* Converts widget type to a string representation */
/* @Parameters: */
/*     - type: Type of the widget (widget_type_t) to convert to string. */
/* @Return: */
/*     - const char*: String representing the widget type. */
const char *get_widget_type_to_string(widget_type_t type)
{
    switch (type)
    {
        case WIDGET_TYPE_STATUS_BAR: return "status_bar";
        case WIDGET_TYPE_SENSOR_BME680: return "sensor_BME680";
        default: return "Unknown Widget";
    }
}

/* Adds a new widget node to the beginning of the widget node list */
/* @Parameters: */
/*     - first_node: Pointer to the first node in the widget node list. */
/*     - widget: Pointer to the widget_t structure to be added in the new node. */
/* @Return: */
/*     - widget_node_t*: Pointer to the new head of the widget node list. */
/*     - NULL: Memory allocation for the new node failed. */
widget_node_t *create_widget_display_list_node(widget_node_t *head, widget_t *widget)
{
    widget_node_t *new_node = malloc(sizeof(widget_node_t));
    if (new_node == NULL)
        return NULL;

    new_node->widget = widget;
    new_node->next = head;
    return new_node;
}

/* Checks if a widget of a specific type exists in the active screen’s widget list */
/* @Parameters: */
/*     - type: Type of the widget (widget_type_t) to check in the list. */
/* @Return: */
/*     - true: A widget of the specified type exists in the active screen list. */
/*     - false: No widget of the specified type exists in the active screen list. */
bool check_widget_exists_in_display_list(const widget_type_t type)

{
    screen_t *screen = get_active_screen();
    widget_node_t *current = screen->widget_display_list;

    while (current != NULL)
    {
        if (current->widget->type == type)
            return true;
        current = current->next;
    }

    return false;
}

/* Compares a widget ID string with a specific widget type */
/* @Parameters: */
/*     - id: Pointer to a constant character string representing the widget ID. */
/*     - type: Type of the widget (widget_type_t) to compare against the ID. */
/* @Return: */
/*     - true: The ID matches the specified widget type. */
/*     - false: The ID does not match the specified widget type. */
bool check_widget_type_by_id(const char *id, widget_type_t type)
{
    return strcmp(id, get_widget_type_to_string(type)) == 0;
}
