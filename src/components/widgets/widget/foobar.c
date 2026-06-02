#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "esp_log.h"
#include "layouts/flex/lv_flex.h"
#include "misc/lv_area.h"
#include "widget.h"
#include "widget/foobar.h"
#include "font.h"
#include "widget_autogen.h"

static const char *TAG = "WIDGET_FOOBAR";

static void widget_foobar(lv_obj_t *screen, widget_t *widget);
static void control_btn_event_cb(lv_event_t *e);

esp_err_t widget_foobar_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_FOOBAR, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_foobar(screen, widget);
    return ESP_OK;
}

esp_err_t widget_foobar_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_FOOBAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t widget_foobar_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_FOOBAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}

esp_err_t widget_foobar_update_data(void)
{
    // Normally, fetch or compute data here
    return ESP_OK;
}

static void widget_foobar(lv_obj_t *screen, widget_t *widget)
{
    static foobar_t foobar_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &foobar_child;

    // foobar
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(widget->lv_obj, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(widget->lv_obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        // Content container
        foobar_child.container_content = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(foobar_child.container_content, LV_PCT(100));
        lv_obj_set_height(foobar_child.container_content, LV_PCT(100));
        lv_obj_set_style_pad_top(foobar_child.container_content, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(foobar_child.container_content, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_left(foobar_child.container_content, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(foobar_child.container_content, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_margin_all(foobar_child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(foobar_child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(foobar_child.container_content, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(foobar_child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(foobar_child.container_content, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(foobar_child.container_content, LV_OPA_50, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(foobar_child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_layout(foobar_child.container_content, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_flow(foobar_child.container_content, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_flex_align(foobar_child.container_content,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER);
        {
            foobar_child.button = lv_obj_create(foobar_child.container_content);
            lv_obj_add_event_cb(foobar_child.button, control_btn_event_cb, LV_EVENT_PRESSED, &foobar_child);
            lv_obj_set_width(foobar_child.button, LV_PCT(50));
            lv_obj_set_height(foobar_child.button, LV_PCT(25));
            lv_obj_set_style_margin_bottom(foobar_child.button, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(foobar_child.button, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(foobar_child.button, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(foobar_child.button, LV_BORDER_SIDE_FULL, 0);
            lv_obj_set_style_border_color(foobar_child.button, lv_color_black(), 0);
            lv_obj_set_style_border_opa(foobar_child.button, LV_OPA_50, 0);

            foobar_child.button_label = lv_label_create(foobar_child.button);
            lv_label_set_text(foobar_child.button_label, "FOO");
            lv_obj_set_style_text_font(foobar_child.button_label, &roboto_bold_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_center(foobar_child.button_label);
        }
    }
}

static void control_btn_event_cb(lv_event_t *e)
{
    foobar_t *foobar_child = (foobar_t *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    static int i;

    if(code == LV_EVENT_PRESSED)
    {
        ESP_LOGI(TAG, "Button pressed");
        lv_obj_clear_state(foobar_child->button, LV_STATE_PRESSED);

        if (i % 2)
        {
            lv_label_set_text(foobar_child->button_label, "FOO");
            lv_obj_set_style_bg_opa(
                    foobar_child->button,
                    LV_OPA_TRANSP,
                    LV_PART_MAIN | LV_STATE_DEFAULT
                    );

            lv_obj_set_style_text_color(
                    foobar_child->button_label,
                    lv_color_black(),
                    LV_PART_MAIN | LV_STATE_DEFAULT
                    );
        }
        else
        {
            lv_label_set_text(foobar_child->button_label, "BAR");

            lv_obj_set_style_bg_color(
                    foobar_child->button,
                    lv_color_black(),
                    LV_PART_MAIN | LV_STATE_DEFAULT
                    );

            lv_obj_set_style_bg_opa(
                    foobar_child->button,
                    LV_OPA_COVER,
                    LV_PART_MAIN | LV_STATE_DEFAULT
                    );

            lv_obj_set_style_text_color(
                    foobar_child->button_label,
                    lv_color_white(),
                    LV_PART_MAIN | LV_STATE_DEFAULT
                    );
        }
        i++;
    }
}
