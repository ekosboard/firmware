#include "widget/side_bar.h"
#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style_gen.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "font/lv_symbol_def.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "icons.h"
#include "layouts/flex/lv_flex.h"
#include "misc/lv_area.h"
#include "misc/lv_style.h"
#include "widget.h"
#include "screen_manager.h"

typedef struct {
    uint8_t target_screen;
} sidebar_nav_ctx_t;

static const char *TAG = "WIDGET_SIDE_BAR";
static void widget_side_bar(lv_obj_t *screen, widget_t *widget);


esp_err_t   widget_side_bar_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIDE_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_side_bar(screen, widget);
    return ESP_OK;
}

esp_err_t   widget_side_bar_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIDE_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t   widget_side_bar_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SIDE_BAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}

esp_err_t   widget_side_bar_update_data(void)
{
    return ESP_OK;
}

static void sidebar_nav_event_cb(lv_event_t *e)
{
    sidebar_nav_ctx_t *ctx = lv_event_get_user_data(e);

    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;

    notify_screen_manager(SCREEN_ACTION_SWITCH, ctx->target_screen);
}

static void widget_side_bar(lv_obj_t *screen, widget_t *widget)
{
    static side_bar_t side_bar_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &side_bar_child;

    // side bar
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_pad_all(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        // status icon container
        side_bar_child.container_status = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(side_bar_child.container_status, LV_PCT(100));
        lv_obj_set_height(side_bar_child.container_status, LV_SIZE_CONTENT);

        lv_obj_set_style_bg_opa(side_bar_child.container_status, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(side_bar_child.container_status, 0, 0);
        lv_obj_set_style_pad_all(side_bar_child.container_status, 0, 0);
        lv_obj_set_style_pad_top(side_bar_child.container_status, 4, 0);
        lv_obj_set_style_pad_top(side_bar_child.container_status, 4, 0);

        /* Ligne horizontale */
        lv_obj_set_flex_flow(side_bar_child.container_status, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(side_bar_child.container_status,
                LV_FLEX_ALIGN_SPACE_EVENLY,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER);

        {
            // status icon 0
            side_bar_child.status_icon[0] = lv_label_create(side_bar_child.container_status);
            lv_obj_set_size(side_bar_child.status_icon[0], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(side_bar_child.status_icon[0], ICON_SYSTEM_DOWNLOAD_MD);
            lv_obj_set_style_text_font(side_bar_child.status_icon[0], &symbol_nerdfont_18, LV_PART_MAIN | LV_STATE_DEFAULT);

            // status icon 1
            side_bar_child.status_icon[1] = lv_label_create(side_bar_child.container_status);
            lv_obj_set_size(side_bar_child.status_icon[1], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(side_bar_child.status_icon[1], ICON_BATTERY_BATTERY_FULL);
            lv_obj_set_style_text_font(side_bar_child.status_icon[1], &symbol_nerdfont_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        // widget icon container
        side_bar_child.container_widget = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(side_bar_child.container_widget, LV_PCT(100));
        lv_obj_set_flex_grow(side_bar_child.container_widget, 1);

        lv_obj_set_style_bg_opa(side_bar_child.container_widget, LV_OPA_TRANSP, 0);

        //XXX: Centrage SPACE_EVENLY
        /* lv_obj_set_style_pad_top(side_bar_child.container_widget, 82, 0); */
        /* lv_obj_set_style_pad_bottom(side_bar_child.container_widget, 120, 0); */

        //XXX: Centrage ALIGN_START
        /* lv_obj_set_style_pad_top(side_bar_child.container_widget, 8, 0); */
        lv_obj_set_style_pad_top(side_bar_child.container_widget, 128, 0);
        lv_obj_set_style_pad_row(side_bar_child.container_widget, 64, 0);

        lv_obj_set_style_border_width(side_bar_child.container_widget, 2, 0);
        lv_obj_set_style_border_color(side_bar_child.container_widget, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(side_bar_child.container_widget, LV_BORDER_SIDE_TOP, 0);
        lv_obj_set_style_radius(side_bar_child.container_widget, 0, 0);

        /* Alignement vertical centré */
        lv_obj_set_flex_flow(side_bar_child.container_widget, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(side_bar_child.container_widget,
                LV_FLEX_ALIGN_START,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER);

        /* LV_FLEX_ALIGN_SPACE_EVENLY, */
        lv_obj_set_style_pad_row(side_bar_child.container_widget, 24, 0);
        {
            // widget icon 0
            side_bar_child.widget_icon[0] = lv_label_create(side_bar_child.container_widget);
            {
                static sidebar_nav_ctx_t nav_ctx_0 = {
                    .target_screen = 0,
                };

                lv_obj_add_flag(side_bar_child.widget_icon[0], LV_OBJ_FLAG_CLICKABLE);
                lv_obj_add_event_cb(
                        side_bar_child.widget_icon[0],
                        sidebar_nav_event_cb,
                        LV_EVENT_CLICKED,
                        &nav_ctx_0
                        );

                lv_obj_set_size(side_bar_child.widget_icon[0], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                lv_label_set_text(side_bar_child.widget_icon[0], ICON_SYSTEM_VIEW_QUILT);
                lv_obj_set_style_text_font(side_bar_child.widget_icon[0], &symbol_nerdfont_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            }

            // widget icon 1
            side_bar_child.widget_icon[1] = lv_label_create(side_bar_child.container_widget);
            {

                static sidebar_nav_ctx_t nav_ctx_1 = {
                    .target_screen = 1,
                };

                lv_obj_add_flag(side_bar_child.widget_icon[1], LV_OBJ_FLAG_CLICKABLE);
                lv_obj_add_event_cb(
                        side_bar_child.widget_icon[1],
                        sidebar_nav_event_cb,
                        LV_EVENT_CLICKED,
                        &nav_ctx_1
                        );
                lv_obj_set_size(side_bar_child.widget_icon[1], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                lv_label_set_text(side_bar_child.widget_icon[1], ICON_SYSTEM_CHART_LINE);
                lv_obj_set_style_text_font(side_bar_child.widget_icon[1], &symbol_nerdfont_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            }

            // widget icon 1
            side_bar_child.widget_icon[2] = lv_label_create(side_bar_child.container_widget);
            {
                static sidebar_nav_ctx_t nav_ctx_2 = {
                    .target_screen = 2,
                };

                lv_obj_add_flag(side_bar_child.widget_icon[2], LV_OBJ_FLAG_CLICKABLE);
                lv_obj_add_event_cb(
                        side_bar_child.widget_icon[2],
                        sidebar_nav_event_cb,
                        LV_EVENT_CLICKED,
                        &nav_ctx_2
                        );
                lv_obj_set_size(side_bar_child.widget_icon[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                lv_label_set_text(side_bar_child.widget_icon[2], ICON_SYSTEM_LAYERS_PLUS);
                lv_obj_set_style_text_font(side_bar_child.widget_icon[2], &symbol_nerdfont_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            }

        }
    }
}
