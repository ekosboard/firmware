#include "UI.h"
#include "core/lv_obj.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style.h"
#include "core/lv_obj_tree.h"
#include "display/lv_display.h"
#include "esp_err.h"
#include "font/lv_symbol_def.h"
#include "misc/lv_area.h"
#include "misc/lv_text.h"
#include "misc/lv_types.h"
#include "widget.h"

static lv_obj_t *create_air_quality_label(lv_obj_t *bme680)
{
    static lv_style_t style_air_quality_label;
    lv_style_init(&style_air_quality_label);
    lv_style_set_text_font(&style_air_quality_label, &symbol_nerdfont_48);

    lv_obj_t *air_quality_label = lv_label_create(bme680);
    lv_label_set_text(air_quality_label, SYMBOL_HOME);
    lv_obj_set_size(air_quality_label, lv_pct(100), lv_pct(30));
    lv_obj_set_style_text_align(air_quality_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(air_quality_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_style(air_quality_label, &style_air_quality_label, 0);
    return air_quality_label;
}

static lv_obj_t *create_humidity_label(lv_obj_t *bme680)
{
    static lv_style_t style_humidity_label;
    lv_style_init(&style_humidity_label);
    lv_style_set_text_font(&style_humidity_label, &symbol_nerdfont_48);

    lv_obj_t *humidity_label = lv_label_create(bme680);
    lv_label_set_text(humidity_label, SYMBOL_HUMIDITY);
    lv_obj_set_size(humidity_label, lv_pct(100), lv_pct(30));
    lv_obj_set_style_text_align(humidity_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(humidity_label, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_add_style(humidity_label, &style_humidity_label, 0);
    return humidity_label;
}

static lv_obj_t *create_temperature_label(lv_obj_t *bme680)
{
    static lv_style_t style_temperature_label;
    lv_style_init(&style_temperature_label);
    lv_style_set_text_font(&style_temperature_label, &symbol_nerdfont_48);

    lv_obj_t *temperature_label = lv_label_create(bme680);
    lv_label_set_text(temperature_label, SYMBOL_THERMOMETER_2);
    lv_obj_set_size(temperature_label, lv_pct(100), lv_pct(30));
    lv_obj_set_style_text_align(temperature_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(temperature_label, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_add_style(temperature_label, &style_temperature_label, 0);
    return temperature_label;
}

static void widget_sensor_BME680(lv_obj_t *screen, widget_t *widget)
{
    static sensor_BME680_t sensor_BME680_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &sensor_BME680_child;

    lv_obj_set_size(widget->lv_obj, lv_pct(widget->width), lv_pct(widget->height));
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_style_margin_all(widget->lv_obj, 0, 0);
    lv_obj_set_style_pad_all(widget->lv_obj, 5, 0);

    static lv_style_t style_border;
    lv_style_set_border_width(&style_border, 2);
    lv_style_set_border_color(&style_border, lv_color_black());
    lv_obj_add_style(widget->lv_obj, &style_border, 0);

    sensor_BME680_child.temperature_label = create_temperature_label(widget->lv_obj);
    sensor_BME680_child.humidity_label = create_humidity_label(widget->lv_obj);
    sensor_BME680_child.air_quality_label = create_air_quality_label(widget->lv_obj);
}

esp_err_t widget_sensor_BME680_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SENSOR_BME680, &widget) != ESP_OK)
        return ESP_FAIL;

   widget_sensor_BME680(screen, widget); 
   return ESP_OK;
}

esp_err_t widget_sensor_BME680_erase()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SENSOR_BME680, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t widget_sensor_BME680_update()
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_SENSOR_BME680, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, lv_pct(widget->width), lv_pct(widget->height));
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    return ESP_OK;
}
