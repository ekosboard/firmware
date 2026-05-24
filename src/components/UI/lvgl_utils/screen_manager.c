#include "EPD.h"
#include "UI.h"
#include "display/lv_display.h"
#include <time.h>

/* Clears all elements from the specified LVGL screen object. */
/* @Parameters: */
/*     - Pointer to the LVGL screen object to be cleared. */
/*     - An optional pointer to a function that clears the display buffer. */
void lvgl_clear_screen(screen_t *screen, void (*clear)(void))
{
    widget_node_t *head = screen->widget_display_list;

    if (lvgl_lock(-1))
    {
        while (head != NULL)
        {
            if (head->widget->lv_obj != NULL)
            {
                head->widget->erase_function();
            }
            head = head->next;
        }
        lv_obj_clean(screen->lv_screen);
        if (clear != NULL)
        {
            clear();
        }
        lvgl_unlock();
    }
}

/* Draws all widgets in the widget_display_list on the specified screen. */
/* @Parameters: */
/*     - Pointer to the LVGL screen object to be drawed. */
/*     - An optional pointer to a function that clears the display buffer. */
void lvgl_draw_screen(screen_t *screen, void (*clear)(void))
{
    widget_node_t *head = screen->widget_display_list;

    if (lvgl_lock(-1))
    {
        if (clear != NULL)
        {
            clear();
        }

        while (head != NULL)
        {
            if (head->widget->lv_obj == NULL)
            {
                head->widget->draw_function(screen->lv_screen);
            }
            head = head->next;
        }

        /* if (clear != NULL) */
        /* { */
        /*     clear(); */
        /* } */
        lv_screen_load(screen->lv_screen);
        lvgl_unlock();
    }
}

void lvgl_force_refresh_screen(screen_t *screen, void (*clear)(void))
{
    epd_reset_refresh_counter();

    if (lvgl_lock(-1))
    {
        if (clear != NULL)
        {
            clear();
        }

        if (screen != NULL)
        {
            lv_obj_invalidate(screen->lv_screen);
            lv_refr_now(NULL);
        }

        lvgl_unlock();
    }
}

/* Switches the active screen in LVGL to the specified screen and optionally clears the display buffer. */
/* @Parameters: */
/*     - A pointer to the screen_t structure representing the screen to switch to. */
/*     - An optional pointer to a function that clears the display buffer. */
void lvgl_switch_screen(screen_t *screen, void (*clear)(void))
{
    if (lvgl_lock(-1))
    {
        if (clear != NULL)
        {
            clear();
        }
        lv_screen_load(screen->lv_screen);
        lvgl_unlock();
    }
}
