#include "widget/seedbox_monitoring.h"
#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style_gen.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "layouts/flex/lv_flex.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_math.h"
#include "widget.h"
#include "widgets/label/lv_label.h"
#include <stdint.h>
#include <stdlib.h>

static const char *TAG = "WIDGET_SEEDBOX_MONITORING";
static void widget_seedbox_monitoring(lv_obj_t *screen, widget_t *widget);

esp_err_t   widget_seedbox_monitoring_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SEEDBOX_MONITORING, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_seedbox_monitoring(screen, widget);
    return ESP_OK;
}

esp_err_t   widget_seedbox_monitoring_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SEEDBOX_MONITORING, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t   widget_seedbox_monitoring_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SEEDBOX_MONITORING, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}

esp_err_t   widget_seedbox_monitoring_update_data(void)
{
    return ESP_OK;
}

static void widget_seedbox_monitoring(lv_obj_t *screen, widget_t *widget)
{
    static seedbox_monitoring_t seedbox_monitoring_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &seedbox_monitoring_child;

    // seedbox_monitoring
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);

    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    /* lv_obj_set_style_margin_all(widget->lv_obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT); */
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(widget->lv_obj, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(widget->lv_obj, LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(widget->lv_obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);

    {
        // header container
        seedbox_monitoring_child.container_header = lv_obj_create(widget->lv_obj);
        lv_obj_set_size(seedbox_monitoring_child.container_header, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

        lv_obj_set_style_pad_all(seedbox_monitoring_child.container_header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_margin_all(seedbox_monitoring_child.container_header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_set_style_bg_opa(seedbox_monitoring_child.container_header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(seedbox_monitoring_child.container_header, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(seedbox_monitoring_child.container_header, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(seedbox_monitoring_child.container_header, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(seedbox_monitoring_child.container_header, LV_OPA_50, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(seedbox_monitoring_child.container_header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_set_style_layout(seedbox_monitoring_child.container_header, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_flow(seedbox_monitoring_child.container_header, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_flex_align(seedbox_monitoring_child.container_header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        {
            // title label
            seedbox_monitoring_child.title_label = lv_label_create(seedbox_monitoring_child.container_header);
            lv_obj_set_size(seedbox_monitoring_child.title_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(seedbox_monitoring_child.title_label, "Seedbox");
            lv_obj_set_style_text_font(seedbox_monitoring_child.title_label, &roboto_bold_24, LV_PART_MAIN | LV_STATE_DEFAULT);

            // header label
            /* seedbox_monitoring_child.header_label = lv_label_create(seedbox_monitoring_child.container_header); */
            /* lv_obj_set_size(seedbox_monitoring_child.header_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT); */
            /* lv_label_set_text(seedbox_monitoring_child.header_label, "seedbox.local "); */
            /* lv_obj_set_style_text_font(seedbox_monitoring_child.header_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT); */
        }

        // content container
        seedbox_monitoring_child.container_content = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(seedbox_monitoring_child.container_content, LV_PCT(100));
        lv_obj_set_flex_grow(seedbox_monitoring_child.container_content, 1);
        lv_obj_set_style_pad_all(seedbox_monitoring_child.container_content, 0, 0);
        lv_obj_set_style_margin_all(seedbox_monitoring_child.container_content, 12, 0);
        lv_obj_set_style_bg_opa(seedbox_monitoring_child.container_content, 0, 0);
        lv_obj_set_style_border_width(seedbox_monitoring_child.container_content, 0, 0);
        lv_obj_set_layout(seedbox_monitoring_child.container_content, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(seedbox_monitoring_child.container_content, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(
                seedbox_monitoring_child.container_content,
                LV_FLEX_ALIGN_SPACE_EVENLY,   // très important ici
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER
                );
        {
            // disk container
            seedbox_monitoring_child.container_disk = lv_obj_create(seedbox_monitoring_child.container_content);
            lv_obj_set_size(seedbox_monitoring_child.container_disk, LV_PCT(40), LV_PCT(100));
            lv_obj_set_style_bg_opa(seedbox_monitoring_child.container_disk, 0, 0);
            lv_obj_set_style_border_width(seedbox_monitoring_child.container_disk, 0, 0);
            lv_obj_set_layout(seedbox_monitoring_child.container_disk, LV_LAYOUT_FLEX);
            lv_obj_set_flex_flow(seedbox_monitoring_child.container_disk, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(
                    seedbox_monitoring_child.container_disk,
                    LV_FLEX_ALIGN_CENTER,
                    LV_FLEX_ALIGN_CENTER,
                    LV_FLEX_ALIGN_CENTER
                    );
            {
                // XXX: ARC
                int32_t value = 42;
                lv_obj_update_layout(screen);
                seedbox_monitoring_child.disk_arc = lv_arc_create(seedbox_monitoring_child.container_disk);
                int32_t container_disk_height = lv_obj_get_height(seedbox_monitoring_child.container_disk);
                int32_t container_disk_width = lv_obj_get_width(seedbox_monitoring_child.container_disk);
                int32_t disk_arc_size = LV_MIN(container_disk_height, container_disk_width) * 0.8;
                lv_obj_set_size(seedbox_monitoring_child.disk_arc, disk_arc_size, disk_arc_size);
                lv_obj_set_style_border_width(seedbox_monitoring_child.disk_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                /* Plage */
                lv_arc_set_range(seedbox_monitoring_child.disk_arc, 0, 100);
                lv_arc_set_value(seedbox_monitoring_child.disk_arc, value);

                /* Arc complet */
                lv_arc_set_bg_angles(seedbox_monitoring_child.disk_arc, 135, 405);
                lv_arc_set_angles(seedbox_monitoring_child.disk_arc, 135, 135 + (270 * value) / 100);

                /* Désactivation interaction */
                lv_obj_clear_flag(seedbox_monitoring_child.disk_arc, LV_OBJ_FLAG_CLICKABLE);
                lv_obj_clear_flag(seedbox_monitoring_child.disk_arc, LV_OBJ_FLAG_SCROLLABLE);
                /* lv_obj_add_flag(seedbox_monitoring_child.disk_arc, LV_OBJ_FLAG_IGNORE_LAYOUT); */

                /* Fond de l’arc */
                lv_obj_set_style_arc_width(seedbox_monitoring_child.disk_arc, 2, LV_PART_MAIN);
                lv_obj_set_style_arc_color(seedbox_monitoring_child.disk_arc, lv_color_black(), LV_PART_MAIN);
                lv_obj_set_style_arc_opa(seedbox_monitoring_child.disk_arc, LV_OPA_30, LV_PART_MAIN);

                /* Valeur */
                lv_obj_set_style_arc_width(seedbox_monitoring_child.disk_arc, 8, LV_PART_INDICATOR);
                lv_obj_set_style_arc_color(seedbox_monitoring_child.disk_arc, lv_color_black(), LV_PART_INDICATOR);
                lv_obj_set_style_arc_opa(seedbox_monitoring_child.disk_arc, LV_OPA_100, LV_PART_INDICATOR);

                /* Knob OFF */
                lv_obj_set_style_bg_opa(seedbox_monitoring_child.disk_arc, LV_OPA_TRANSP, LV_PART_KNOB);

                /* Suppression radius ligne */
                lv_obj_set_style_arc_rounded(seedbox_monitoring_child.disk_arc, false, LV_PART_INDICATOR);
                lv_obj_set_style_arc_rounded(seedbox_monitoring_child.disk_arc, false, LV_PART_MAIN);

                // XXX: LABEL
                lv_obj_t * value_label = lv_label_create(seedbox_monitoring_child.disk_arc);
                lv_label_set_text_fmt(value_label, "%"PRIu32"%%", value);
                lv_obj_set_style_text_font(value_label, &roboto_bold_32, 0);

                /* Centrage absolu */
                lv_obj_add_flag(value_label, LV_OBJ_FLAG_IGNORE_LAYOUT);
                lv_obj_center(value_label);

                // XXX: LABEL / TITRE
                lv_obj_t * title_label = lv_label_create(seedbox_monitoring_child.container_disk);
                lv_label_set_text(title_label, "Disk");
                lv_obj_set_style_text_font(title_label, &roboto_bold_22, 0);
                lv_obj_set_style_text_opa(title_label, LV_OPA_100, 0);
                lv_obj_set_style_pad_all(title_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_margin_all(title_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_margin_top(title_label, -16, LV_PART_MAIN | LV_STATE_DEFAULT);
            }

            // traffic container
            seedbox_monitoring_child.container_traffic = lv_obj_create(seedbox_monitoring_child.container_content);
            lv_obj_set_size(seedbox_monitoring_child.container_traffic, LV_PCT(40), LV_PCT(100));
            lv_obj_set_style_bg_opa(seedbox_monitoring_child.container_traffic, 0, 0);
            lv_obj_set_style_border_width(seedbox_monitoring_child.container_traffic, 0, 0);
            lv_obj_set_layout(seedbox_monitoring_child.container_traffic, LV_LAYOUT_FLEX);
            lv_obj_set_flex_flow(seedbox_monitoring_child.container_traffic, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(
                    seedbox_monitoring_child.container_traffic,
                    LV_FLEX_ALIGN_CENTER,
                    LV_FLEX_ALIGN_CENTER,
                    LV_FLEX_ALIGN_CENTER
                    );
            {
                // XXX: ARC
                lv_obj_update_layout(screen);
                int32_t value = 94;
                seedbox_monitoring_child.traffic_arc = lv_arc_create(seedbox_monitoring_child.container_traffic);
                int32_t container_traffic_height = lv_obj_get_height(seedbox_monitoring_child.container_traffic);
                int32_t container_traffic_width = lv_obj_get_width(seedbox_monitoring_child.container_traffic);
                int32_t traffic_arc_size = LV_MIN(container_traffic_height, container_traffic_width) * 0.8;
                lv_obj_set_size(seedbox_monitoring_child.traffic_arc, traffic_arc_size, traffic_arc_size);

                /* Plage */
                lv_arc_set_range(seedbox_monitoring_child.traffic_arc, 0, 100);
                lv_arc_set_value(seedbox_monitoring_child.traffic_arc, value);

                /* Arc complet */
                lv_arc_set_bg_angles(seedbox_monitoring_child.traffic_arc, 135, 405);
                lv_arc_set_angles(seedbox_monitoring_child.traffic_arc, 135, 135 + (270 * value) / 100);

                /* Désactivation interaction */
                lv_obj_clear_flag(seedbox_monitoring_child.traffic_arc, LV_OBJ_FLAG_CLICKABLE);
                lv_obj_clear_flag(seedbox_monitoring_child.traffic_arc, LV_OBJ_FLAG_SCROLLABLE);

                /* Fond de l’arc */
                lv_obj_set_style_arc_width(seedbox_monitoring_child.traffic_arc, 2, LV_PART_MAIN);
                lv_obj_set_style_arc_color(seedbox_monitoring_child.traffic_arc, lv_color_black(), LV_PART_MAIN);
                lv_obj_set_style_arc_opa(seedbox_monitoring_child.traffic_arc, LV_OPA_30, LV_PART_MAIN);

                /* Valeur */
                lv_obj_set_style_arc_width(seedbox_monitoring_child.traffic_arc, 8, LV_PART_INDICATOR);
                lv_obj_set_style_arc_color(seedbox_monitoring_child.traffic_arc, lv_color_black(), LV_PART_INDICATOR);
                lv_obj_set_style_arc_opa(seedbox_monitoring_child.traffic_arc, LV_OPA_100, LV_PART_INDICATOR);

                /* Knob OFF */
                lv_obj_set_style_bg_opa(seedbox_monitoring_child.traffic_arc, LV_OPA_TRANSP, LV_PART_KNOB);

                /* Suppression radius ligne */
                lv_obj_set_style_arc_rounded(seedbox_monitoring_child.traffic_arc, false, LV_PART_INDICATOR);
                lv_obj_set_style_arc_rounded(seedbox_monitoring_child.traffic_arc, false, LV_PART_MAIN);

                // XXX: LABEL
                lv_obj_t *value_label = lv_label_create(seedbox_monitoring_child.traffic_arc);
                lv_label_set_text_fmt(value_label, "%"PRIu32"%%", value);
                lv_obj_set_style_text_font(value_label, &roboto_bold_32, 0);

                /* Centrage absolu */
                lv_obj_add_flag(value_label, LV_OBJ_FLAG_IGNORE_LAYOUT);
                lv_obj_center(value_label);

                // XXX: LABEL / TITRE
                lv_obj_t * title_label = lv_label_create(seedbox_monitoring_child.container_traffic);
                lv_label_set_text(title_label, "Traffic");
                lv_obj_set_style_text_font(title_label, &roboto_bold_22, 0);
                lv_obj_set_style_text_opa(title_label, LV_OPA_100, 0);
                lv_obj_set_style_margin_all(title_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_margin_top(title_label, -16, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        // footer container
        seedbox_monitoring_child.container_footer = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(seedbox_monitoring_child.container_footer, LV_PCT(100));
        lv_obj_set_height(seedbox_monitoring_child.container_footer, LV_SIZE_CONTENT);
        lv_obj_set_style_pad_top(seedbox_monitoring_child.container_footer, 4, 0);
        lv_obj_set_style_pad_left(seedbox_monitoring_child.container_footer, 4, 0);
        lv_obj_set_style_pad_right(seedbox_monitoring_child.container_footer, 4, 0);
        lv_obj_set_style_bg_opa(seedbox_monitoring_child.container_footer, 0, 0);
        lv_obj_set_layout(seedbox_monitoring_child.container_footer, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(seedbox_monitoring_child.container_footer, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(
                seedbox_monitoring_child.container_footer,
                LV_FLEX_ALIGN_END,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER
                );
        {
            // footer label
            seedbox_monitoring_child.footer_label = lv_label_create(seedbox_monitoring_child.container_footer);
            lv_obj_set_size(seedbox_monitoring_child.footer_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(seedbox_monitoring_child.footer_label, "uptime: 12d 8h 23m");
            lv_obj_set_style_text_font(seedbox_monitoring_child.footer_label, &roboto_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

