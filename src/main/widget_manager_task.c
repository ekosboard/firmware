#include "core/lv_obj_tree.h"
#include "UI.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/projdefs.h"
#include "main.h"
#include "widget.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

static const char *TAG = "main display_task";


/* Registers a new widget in the widget display list */
/* @Parameters: */
/*     - Pointer to the widget_update_t structure containing the widget information to be registered. */
/* @Return: */
    /* - ESP_OK if the widget was successfully registered*/
    /* - ESP_FAIL in all other cases */
static esp_err_t register_widget(const widget_update_t *widget_update)
{
    ESP_LOGI(TAG, "register widget: %s", get_widget_type_to_string(widget_update->type));
    widget_t *new_widget = NULL;

    if (check_widget_exists_in_any_display_list(widget_update->type) == true)
        return ESP_FAIL;

    if (get_widget_by_type(widget_update->type, &new_widget) != ESP_OK)
        return ESP_FAIL;

    if (update_widget_info(widget_update) != ESP_OK)
        return ESP_FAIL;

    screen_t *screen = &get_main_display()->screen[widget_update->screen_id];
    widget_node_t *new_node = create_widget_display_list_node(screen->widget_display_list, new_widget);
    if (new_node == NULL)
        return ESP_FAIL;

    screen->widget_display_list = new_node;
    update_widget_display_list_json(screen->widget_display_list, screen->id);
    if (lvgl_lock(-1))
    {
        new_node->widget->draw_function(screen->lv_screen);
        lvgl_unlock();
    }

    return ESP_OK;
}

/* Updates an already registered widget with new information */
/* @Parameters: */
/*     - Pointer to the widget_update_t structure containing the updated widget information. */
/* @Return: */
/*     - ESP_OK if the widget was successfully updated and redrawn. */
/*     - ESP_FAIL if the widget node is not found, or if any update or retrieval operation fails. */
static esp_err_t update_registered_widget(const widget_update_t *widget_update)
{
    if (check_widget_exists_in_display_list(widget_update->type, widget_update->screen_id) == false)
        return ESP_FAIL;

    if (update_widget_info(widget_update) != ESP_OK)
        return ESP_FAIL;

    widget_t *widget = NULL;
    if (get_widget_by_type(widget_update->type, &widget) != ESP_OK)
        return ESP_FAIL;

    if (lvgl_lock(-1))
    {
        widget->update_function();
        lvgl_unlock();
    }
    return ESP_OK;
}

/* Unregisters a widget from the widget display list */
/* @Parameters: */
/*     -  type enum representing the ID of the widget to be unregistered. */
/* @Return: */
    /* - ESP_OK if the widget was successfully unregistered */
    /* - ESP_FAIL in all other cases */
static esp_err_t unregister_widget(const widget_type_t widget_type, const uint8_t screen_id)
{
    screen_t *screen = &get_main_display()->screen[screen_id];
    widget_node_t *current = screen->widget_display_list;
    widget_node_t *previous = NULL;

    while (current != NULL)
    {
        if (current->widget->type == widget_type) 
        {
            if (previous == NULL) 
            {
                screen->widget_display_list = current->next;
            }
            else 
            {
                previous->next = current->next;
            }

            if (lvgl_lock(-1))
            {
                current->widget->erase_function();
                lvgl_unlock();
            }
            free(current);
            update_widget_display_list_json(screen->widget_display_list, screen->id);
            return ESP_OK;
        }
        previous = current;
        current = current->next;
    }

    return ESP_FAIL;
}


/* Manages widget registration and updates based on the widget update queue */
/* @Parameters: */
/*     - pvParameters: Pointer to the task handle for the display task, passed in during task creation. */
/* @Behavior: */
/*     - Repeatedly checks the widget update queue for any new updates. */
/*     - Registers or unregisters widgets based on their active state in the widget_update structure. */
/*     - Notifies the display task of updates to trigger UI refreshes. */
/* @Return: */
/*     - None */
void widget_manager_task(void *pvParameters)
{
    widget_update_t widget_update;
    esp_err_t err;

    while (42)
    {
        if (pop_widget_update_queue(&widget_update) == ESP_OK)
        {
            ESP_LOGI(TAG, "widget manager task get update from queue: %s", get_widget_type_to_string(widget_update.type));
            if (widget_update.action == WIDGET_ACTION_DRAW)
            {
                err = register_widget(&widget_update);
                if (err != ESP_OK)
                    continue;
            }
            else if (widget_update.action == WIDGET_ACTION_UPDATE)
            {
                err = update_registered_widget(&widget_update);
                if (err != ESP_OK)
                    continue;
            }
            else if (widget_update.action == WIDGET_ACTION_ERASE)
            {
                err = unregister_widget(widget_update.type, widget_update.screen_id);
                if (err != ESP_OK)
                    continue;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
