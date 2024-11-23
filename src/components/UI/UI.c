#include "UI.h"
#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "widget.h"
#include <stdio.h>

static display_t display;


/* Initializes the display structure with screens and widget containers */
/* @Parameters: None */
/* @Return: None */
/* @Details: Sets up the `display` structure by initializing each screen’s `lv_screen`,
   setting up empty widget display lists, and assigning empty containers for each layout type. */
static void init_display_structure(void)
{
    display.widget_info_list = get_widget_list(NULL);
    int8_t screen_id = nvs_setup_state_read_screen_id();
    if (screen_id != -1)
        display.active_screen = screen_id;

    for (uint8_t i = 0; i < MAX_SCREEN; i++)
    {
        if (lvgl_lock(-1))
        {
            display.screen[i].lv_screen = lv_obj_create(NULL);
            lvgl_unlock();
        }
        display.screen[i].id = i;
        display.screen[i].widget_display_list = NULL;

        char json_path_file[WIDGET_INDEX_PATH_LEN];
        snprintf(json_path_file, sizeof(json_path_file), "%s%d%s", WIDGET_INDEX_PATH_BASE, display.screen[i].id, WIDGET_INDEX_PATH_EXT);
        init_widget_display_list_from_file(&display.screen[i].widget_display_list, json_path_file);

        for (uint8_t j = 0; j < LAYOUT_TYPE; j++)
        {
            display.screen[i].containers[j].widget = NULL;
        }
    }
}

/* Retrieves the main display structure */
/* @Parameters: None */
/* @Return:
   - display_t*: Pointer to the main `display_t` structure used throughout the UI module. */
/* @Details: Provides access to the initialized display structure, allowing other components
   to reference the main display and access its screens, active screen index, and widgets. */
display_t *get_main_display(void)
{
    return &display;
}

/* Retrieves the currently active screen structure */
/* @Parameters: None */
/* @Return:
   - Pointer to the currently active `screen_t` structure based on the active screen index. */
/* @Details: Provides access to the screen structure that is currently active on the main display.
   This function allows other components to interact with the active screen, such as drawing widgets,
   updating UI elements, and handling screen-specific settings. */
screen_t *get_active_screen(void)
{
    display_t *display = get_main_display();
    return &display->screen[display->active_screen];
}

/* Initializes the user interface by setting up the display and widget lists */
/* @Parameters: None */
/* @Return:
   - ESP_OK: User interface initialized successfully.
   - ESP_FAIL: User interface initialization failed. */
/* @Details: Invokes LVGL initialization for the main display structure, initializes the
   widget list, and configures the display structure with screens and containers. */
esp_err_t init_ui(void)
{
    esp_err_t err = init_lvgl(&display);
    if (err != ESP_OK)
        return ESP_FAIL;

    init_widget_list();
    init_display_structure();

    return ESP_OK;
}
