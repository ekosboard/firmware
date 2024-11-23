#include "UI.h"
#include "main.h"
#include <stdint.h>

/* Task to manage screen updates and actions on the main display */
/* The screen_manager_task listens for notifications containing a screen ID and an */
/* action flag, then performs actions like clearing, drawing, or switching screens */
/* based on the specified action. This task allows external components to trigger */
/* screen changes via notifications, enabling flexibility for API calls, GPIO inputs, */
/* or other triggers. */
/* @Notifications: */
/*     - The notification value passed to the task should contain two pieces of information: */
/*       - Screen ID: lower 8 bits (`0x000000FF`), representing the ID of the screen to be updated. */
/*       - Action flag: next 8 bits (`0x0000FF00`), defining the action to perform, such as clear, */
/*         draw, or switch actions. */
/* @Actions: */
/*     - SCREEN_ACTION_CLEAR_ONLY: Clear the current screen without affecting the driver buffer. */
/*     - SCREEN_ACTION_CLEAR_WITH_DRIVER: Clear both the screen and the driver buffer. */
/*     - SCREEN_ACTION_DRAW_ONLY: Draw the screen without clearing the driver buffer. */
/*     - SCREEN_ACTION_DRAW_WITH_DRIVER: Draw the screen and clear the driver buffer. */
/*     - SCREEN_ACTION_SWITCH_ONLY: Switch to a different screen without clearing. */
/*     - SCREEN_ACTION_SWITCH_AND_CLEAR: Switch to a different screen and clear the driver buffer. */
void screen_manager_task(void *pvParameters)
{
    uint32_t notif_value;
    uint8_t screen_id, action;
    screen_t *screen;
    display_t *display = get_main_display();

    while (42)
    {
        if (xTaskNotifyWait(0x00, 0xffffffff, &notif_value, portMAX_DELAY) == pdTRUE)
        {
            screen_id = (uint8_t)(notif_value & SCREEN_ID_MASK);
            action = (uint8_t)((notif_value & SCREEN_ACTION_MASK) >> 8);

            display->active_screen = screen_id;
            screen = get_active_screen();

            switch (action)
            {
                case SCREEN_ACTION_CLEAR_ONLY:
                    lvgl_clear_screen(screen, NULL);
                    break;

                case SCREEN_ACTION_CLEAR_WITH_DRIVER:
                    lvgl_clear_screen(screen, display->display_driver->clear);
                    break;

                case SCREEN_ACTION_DRAW_ONLY:
                    lvgl_draw_screen(screen, NULL);
                    break;

                case SCREEN_ACTION_DRAW_WITH_DRIVER:
                    lvgl_draw_screen(screen, display->display_driver->clear);
                    break;

                case SCREEN_ACTION_SWITCH_ONLY:
                    lvgl_switch_screen(screen, NULL);
                    break;

                case SCREEN_ACTION_SWITCH_AND_CLEAR:
                    lvgl_switch_screen(screen, display->display_driver->clear);
                    break;

                default:
                    // SCREEN_ACTION_NONE
                    break;
            }
        }
    }
}


/* Sends a notification to the screen manager task to perform a specific action on a screen */
/* @Parameters: */
/*     - action: The action to perform, encoded as a uint8_t. */
/*     - screen_id: The ID of the screen to act on, encoded as a uint8_t. */
/* @Behavior: */
/*     - Combines the action and screen_id into a 32-bit notification value. */
/* @Return: */
/*     - None */
void notify_screen_manager(uint8_t action, uint8_t screen_id)
{
    uint32_t notification_value = screen_id | (action << 8);
    TaskHandle_t screen_manager_task_handle = xTaskGetHandle("screen_manager_task");
    if (screen_manager_task_handle != NULL)
    {
        xTaskNotify(screen_manager_task_handle, notification_value, eSetValueWithOverwrite);
    }
}
