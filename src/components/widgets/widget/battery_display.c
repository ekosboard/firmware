#include "widget/battery_display.h"
#include "data_provider.h"
#include "provider_manager.h"
#include "font.h"
#include "widget.h"
#include "widget_config_list.h"
#include "core/lv_obj.h"
#include "esp_log.h"

static const char *TAG = "WIDGET_BATTERY_DISPLAY";
static void widget_battery_display_build(lv_obj_t *screen, widget_t *widget);

esp_err_t widget_battery_display_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_BATTERY_DISPLAY, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_battery_display_build(screen, widget);
    return ESP_OK;
}

esp_err_t widget_battery_display_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_BATTERY_DISPLAY, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t widget_battery_display_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_BATTERY_DISPLAY, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    return ESP_OK;
}

esp_err_t widget_battery_display_update_data(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_BATTERY_DISPLAY, &widget) != ESP_OK)
        return ESP_FAIL;

    battery_display_t *child = (battery_display_t *)widget->child;
    if (child == NULL)
        return ESP_FAIL;

    // Récupère le nom du provider depuis la config (avec fallback sur "battery")
    const char *source = widget_config_list_get_value(widget->config, "data_source");
    if (source == NULL)
        source = "battery";

    const provider_data_t *data = NULL;
    esp_err_t err = provider_get(source, &data);

    if (err != ESP_OK || data == NULL)
    {
        ESP_LOGW(TAG, "Provider \"%s\" not found", source);
        lv_label_set_text(child->pct_label, "--%");
        lv_label_set_text(child->voltage_label, "--V");
        return ESP_FAIL;
    }

    // Provider en erreur — affichage dégradé
    if (data->status != PROVIDER_STATUS_OK)
    {
        ESP_LOGW(TAG, "Provider \"%s\" status=%d", source, data->status);
        lv_label_set_text(child->pct_label, "ERR");
        lv_label_set_text(child->voltage_label, "--V");
        return ESP_FAIL;
    }

    // Lecture des valeurs
    float pct = 0.0f;
    float voltage = 0.0f;

    provider_data_get_float(data, "battery_pct",     &pct);
    provider_data_get_float(data, "battery_voltage",  &voltage);

    ESP_LOGI(TAG, "Battery: %.1f%% | %.3fV", pct, voltage);

    char buf[16];

    snprintf(buf, sizeof(buf), "%.0f%%", pct);
    lv_label_set_text(child->pct_label, buf);

    snprintf(buf, sizeof(buf), "%.2fV", voltage);
    lv_label_set_text(child->voltage_label, buf);

    return ESP_OK;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Construction LVGL
// ─────────────────────────────────────────────────────────────────────────────

static void widget_battery_display_build(lv_obj_t *screen, widget_t *widget)
{
    static battery_display_t s_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child  = &s_child;

    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(widget->lv_obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    s_child.pct_label = lv_label_create(widget->lv_obj);
    lv_label_set_text(s_child.pct_label, "--%");
    lv_obj_set_style_text_font(s_child.pct_label, &roboto_bold_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    s_child.voltage_label = lv_label_create(widget->lv_obj);
    lv_label_set_text(s_child.voltage_label, "--V");
    lv_obj_set_style_text_font(s_child.voltage_label, &roboto_reg_18, LV_PART_MAIN | LV_STATE_DEFAULT);
}
