#include "widget/stock_chart.h"
#include "HTTPS_request.h"
#include "core/lv_obj.h"
#include "core/lv_obj_event.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style_gen.h"
#include "draw/lv_draw.h"
#include "draw/lv_draw_private.h"
#include "esp_err.h"
#include "esp_log.h"
#include "font/lv_font.h"
#include "UI.h"
#include "font.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "icons.h"
#include "layouts/flex/lv_flex.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_style.h"
#include "misc/lv_types.h"
#include "widget.h"
#include "widgets/chart/lv_chart.h"
#include "widgets/chart/lv_chart_private.h"
#include <stdlib.h>
#include "inttypes.h"

static const char *TAG = "WIDGET_STOCK_CHART";
static void widget_stock_chart(lv_obj_t *screen, widget_t *widget);
static void alphavantage_request(stock_chart_t *child, const char *url);
static void alphavantage_request_spot(stock_chart_t *child, const char *url);
static void stock_chart_set_values(stock_chart_t *child, float *values, uint32_t count);
static void stock_chart_add_value(stock_chart_t *child, float new_value);
static bool parse_alphavantage_history_50(const char *json, float *out_values, uint32_t *out_count);
static bool parse_alphavantage_spot(const char *json, float *out_price);
static esp_err_t build_alphavantage_url(widget_config_t *cfg, char *buffer, size_t buffer_size);


esp_err_t   widget_stock_chart_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STOCK_CHART, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_stock_chart(screen, widget);
    return ESP_OK;
}


esp_err_t   widget_stock_chart_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STOCK_CHART, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}


esp_err_t   widget_stock_chart_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STOCK_CHART, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x,  widget->pos_y);
    return ESP_OK;
}


esp_err_t   widget_stock_chart_update_data(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_STOCK_CHART, &widget) != ESP_OK)
        return ESP_FAIL;


    stock_chart_t *stock = (stock_chart_t *)widget->child;
    const char *cfg_symbol = widget_config_list_get_value(widget->config, "symbol");
    if (!cfg_symbol)
        return ESP_FAIL;

    lv_label_set_text(stock->symbol_label[0], cfg_symbol);

    char url[256];
    build_alphavantage_url(widget->config, url, sizeof(url));
    alphavantage_request(widget->child, url);
    return ESP_OK;
}

static void add_faded_area(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);

    lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t * base_dsc = draw_task->draw_dsc;

    const lv_chart_series_t * ser = lv_chart_get_series_next(obj, NULL);

    /*Draw a triangle below the line witch some opacity gradient*/
    lv_draw_line_dsc_t * draw_line_dsc = draw_task->draw_dsc;
    lv_draw_triangle_dsc_t tri_dsc;

    lv_draw_triangle_dsc_init(&tri_dsc);
    tri_dsc.p[0].x = draw_line_dsc->p1.x;
    tri_dsc.p[0].y = draw_line_dsc->p1.y;
    tri_dsc.p[1].x = draw_line_dsc->p2.x;
    tri_dsc.p[1].y = draw_line_dsc->p2.y;
    tri_dsc.p[2].x = draw_line_dsc->p1.y < draw_line_dsc->p2.y ? draw_line_dsc->p1.x : draw_line_dsc->p2.x;
    tri_dsc.p[2].y = LV_MAX(draw_line_dsc->p1.y, draw_line_dsc->p2.y);
    tri_dsc.bg_color = ser->color;
    tri_dsc.bg_opa   = LV_OPA_30;
    lv_draw_triangle(base_dsc->layer, &tri_dsc);

    /*Draw rectangle below the triangle*/
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_color = ser->color;
    rect_dsc.bg_opa = LV_OPA_30;

    lv_area_t rect_area;
    rect_area.x1 = (int32_t)draw_line_dsc->p1.x;
    rect_area.x2 = (int32_t)draw_line_dsc->p2.x - 1;
    rect_area.y1 = (int32_t)LV_MAX(draw_line_dsc->p1.y, draw_line_dsc->p2.y);
    rect_area.y2 = (int32_t)obj->coords.y2;
    lv_draw_rect(base_dsc->layer, &rect_dsc, &rect_area);

}


static void draw_baseline(lv_event_t * e)
{
    lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t * base_dsc = draw_task->draw_dsc;
    lv_obj_t * obj = lv_event_get_target(e);

    /* récupérer la zone de dessin du chart */
    lv_area_t plot;
    lv_area_copy(&plot, &obj->coords);

    plot.x1 += lv_obj_get_style_pad_left(obj, LV_PART_MAIN);
    plot.x2 -= lv_obj_get_style_pad_right(obj, LV_PART_MAIN);
    plot.y1 += lv_obj_get_style_pad_top(obj, LV_PART_MAIN);
    plot.y2 -= lv_obj_get_style_pad_bottom(obj, LV_PART_MAIN);

    /* baseline horizontale */
    lv_draw_line_dsc_t dsc;
    lv_draw_line_dsc_init(&dsc);
    dsc.color = lv_color_black();
    dsc.width = 2;
    dsc.opa = LV_OPA_50;

    lv_draw_line(base_dsc->layer, &dsc);
}


static void draw_event_cb(lv_event_t * e)
{
    lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t *base_dsc = draw_task->draw_dsc;

    if(draw_task->type != LV_DRAW_TASK_TYPE_LINE) return;

    if(base_dsc->part == LV_PART_ITEMS) {
        add_faded_area(e);
    }
}


static void widget_stock_chart(lv_obj_t *screen, widget_t *widget)
{
    static stock_chart_t stock_chart_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &stock_chart_child;

    // stock chart
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_align(widget->lv_obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    {
        // content container
        stock_chart_child.container_content = lv_obj_create(widget->lv_obj);
        lv_obj_set_width(stock_chart_child.container_content, LV_PCT(100));
        lv_obj_set_flex_grow(stock_chart_child.container_content, 1);
        lv_obj_set_style_bg_opa(stock_chart_child.container_content, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(stock_chart_child.container_content, 0, 0);
        lv_obj_set_style_pad_all(stock_chart_child.container_content, 4, 0);
        lv_obj_set_flex_flow(stock_chart_child.container_content, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(stock_chart_child.container_content, LV_FLEX_ALIGN_SPACE_AROUND, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            // row container
            for (int i = 0; i < 1; i++)
            {
                stock_chart_child.container_row[i] = lv_obj_create(stock_chart_child.container_content);

                lv_obj_set_width(stock_chart_child.container_row[i], LV_PCT(100));
                lv_obj_set_flex_grow(stock_chart_child.container_row[i], 1);
                lv_obj_set_style_bg_opa(stock_chart_child.container_row[i], LV_OPA_TRANSP, 0);
                lv_obj_set_style_border_width(stock_chart_child.container_row[i], 0, 0);
                lv_obj_set_style_pad_all(stock_chart_child.container_row[i], 0, 0);
                lv_obj_set_style_pad_left(stock_chart_child.container_row[i], 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_flex_flow(stock_chart_child.container_row[i], LV_FLEX_FLOW_ROW);
                lv_obj_set_flex_align(stock_chart_child.container_row[i],
                        LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER
                        );
                lv_obj_set_style_radius(stock_chart_child.container_row[i], 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_color(stock_chart_child.container_row[i], lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_opa(stock_chart_child.container_row[i], LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(stock_chart_child.container_row[i], 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_side(stock_chart_child.container_row[i], LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
                {
                    // symbol container
                    stock_chart_child.container_symbol[i] = lv_obj_create(stock_chart_child.container_row[i]);
                    lv_obj_set_width(stock_chart_child.container_symbol[i], 150);
                    lv_obj_set_height(stock_chart_child.container_symbol[i], LV_PCT(100));
                    lv_obj_set_style_bg_opa(stock_chart_child.container_symbol[i], LV_OPA_TRANSP, 0);
                    lv_obj_set_style_pad_row(stock_chart_child.container_symbol[i], 6, 0);
                    lv_obj_set_style_pad_all(stock_chart_child.container_symbol[i], 0, 0);
                    lv_obj_set_style_margin_left(stock_chart_child.container_symbol[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(stock_chart_child.container_symbol[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_flex_flow(stock_chart_child.container_symbol[i], LV_FLEX_FLOW_COLUMN);
                    lv_obj_set_flex_align(
                            stock_chart_child.container_symbol[i],
                            LV_FLEX_ALIGN_START,
                            LV_FLEX_ALIGN_SPACE_AROUND,
                            LV_FLEX_ALIGN_START
                            );
                    {
                        // symbol top row container
                        stock_chart_child.container_symbol_top[i] = lv_obj_create(stock_chart_child.container_symbol[i]);
                        lv_obj_set_width(stock_chart_child.container_symbol_top[i], LV_PCT(100));
                        lv_obj_set_height(stock_chart_child.container_symbol_top[i], LV_SIZE_CONTENT);
                        lv_obj_set_style_bg_opa(stock_chart_child.container_symbol_top[i], LV_OPA_TRANSP, 0);
                        lv_obj_set_style_pad_all(stock_chart_child.container_symbol_top[i], 0, 0);
                        lv_obj_set_flex_flow(stock_chart_child.container_symbol_top[i], LV_FLEX_FLOW_ROW);
                        lv_obj_set_flex_align(
                                stock_chart_child.container_symbol_top[i],
                                LV_FLEX_ALIGN_START,
                                LV_FLEX_ALIGN_CENTER,
                                LV_FLEX_ALIGN_CENTER
                                );
                        {
                            // symbol label
                            stock_chart_child.symbol_label[i] = lv_label_create(stock_chart_child.container_symbol_top[i]);
                            lv_label_set_text(stock_chart_child.symbol_label[i], "SYMBL");
                            lv_obj_set_style_text_font(stock_chart_child.symbol_label[i], &roboto_bold_24, 0);

                            // timeframe label
                            stock_chart_child.timeframe_label[i] = lv_label_create(stock_chart_child.container_symbol_top[i]);
                            lv_label_set_text(stock_chart_child.timeframe_label[i], "1D");
                            lv_obj_set_style_text_font(stock_chart_child.timeframe_label[i], &lv_font_montserrat_20, 0);

                            // arrow label
                            stock_chart_child.arrow_label[i] = lv_label_create(stock_chart_child.container_symbol_top[i]);
                            lv_label_set_text(stock_chart_child.arrow_label[i], ICON_SYSTEM_TRIANGLE_UP);
                            lv_obj_set_style_text_font(stock_chart_child.arrow_label[i], &symbol_nerdfont_24, 0);
                        }

                        // price container
                        stock_chart_child.container_price[i] = lv_obj_create(stock_chart_child.container_symbol[i]);
                        lv_obj_set_width(stock_chart_child.container_price[i], LV_PCT(100));
                        lv_obj_set_flex_grow(stock_chart_child.container_price[i], 1);
                        lv_obj_set_style_bg_opa(stock_chart_child.container_price[i], LV_OPA_TRANSP, 0);
                        lv_obj_set_style_pad_all(stock_chart_child.container_price[i], 0, 0);
                        lv_obj_set_style_pad_column(stock_chart_child.container_price[i], 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_flex_flow(stock_chart_child.container_price[i], LV_FLEX_FLOW_COLUMN);
                        lv_obj_set_flex_align(
                                stock_chart_child.container_price[i],
                                LV_FLEX_ALIGN_CENTER,
                                LV_FLEX_ALIGN_START,
                                LV_FLEX_ALIGN_START
                                );
                        {
                            // price label
                            stock_chart_child.price_label[i] = lv_label_create(stock_chart_child.container_price[i]);
                            lv_label_set_text(stock_chart_child.price_label[i], "$42 356");
                            lv_obj_set_style_text_font(stock_chart_child.price_label[i], &roboto_bold_32, 0);
                            lv_obj_set_style_text_align(stock_chart_child.price_label[i], LV_TEXT_ALIGN_LEFT, 0);

                            // diff price label
                            stock_chart_child.diff_label[i] = lv_label_create(stock_chart_child.container_price[i]);
                            lv_label_set_text(stock_chart_child.diff_label[i], "+1 240  (+2.03%)");
                            lv_obj_set_style_text_font(stock_chart_child.diff_label[i], &lv_font_montserrat_18, 0);
                        }
                    }
                }
                {
                // chart container
                    stock_chart_child.container_chart[i] = lv_obj_create(stock_chart_child.container_row[i]);
                    lv_obj_set_flex_grow(stock_chart_child.container_chart[i], 1);   // 👈 prend TOUT le reste
                    lv_obj_set_height(stock_chart_child.container_chart[i], LV_PCT(100));
                    lv_obj_set_style_bg_opa(stock_chart_child.container_chart[i], LV_OPA_TRANSP, 0);
                    lv_obj_set_style_border_width(stock_chart_child.container_chart[i], 0, 0);
                    lv_obj_set_style_pad_all(stock_chart_child.container_chart[i], 0, 0);
                    lv_obj_set_style_margin_all(stock_chart_child.container_chart[i], 0, 0);
                    lv_obj_set_flex_flow(stock_chart_child.container_chart[i], LV_FLEX_FLOW_COLUMN);
                    {
                        // chart data
                        stock_chart_child.chart_data[i] = lv_chart_create(stock_chart_child.container_chart[i]);
                        lv_obj_set_size(stock_chart_child.chart_data[i], LV_PCT(100), LV_PCT(100));
                        lv_obj_set_style_bg_opa(stock_chart_child.chart_data[i], LV_OPA_100, 0);
                        lv_chart_set_type(stock_chart_child.chart_data[i], LV_CHART_TYPE_LINE);
                        lv_chart_set_update_mode(stock_chart_child.chart_data[i], LV_CHART_UPDATE_MODE_SHIFT);
                        lv_chart_set_point_count(stock_chart_child.chart_data[i], 50);
                        lv_obj_set_style_pad_all(stock_chart_child.chart_data[i], 0, 0);
                        lv_obj_set_style_margin_all(stock_chart_child.chart_data[i], 0, 0);
                        // dot on line
                        lv_obj_set_style_size(stock_chart_child.chart_data[i], 1, 1, LV_PART_INDICATOR);
                        lv_obj_set_style_border_width(stock_chart_child.chart_data[i], 0, 0);
                        lv_obj_set_style_bg_opa(stock_chart_child.chart_data[i], LV_OPA_TRANSP, 0);
                        lv_chart_set_div_line_count(stock_chart_child.chart_data[i], 0, 0);

                        lv_obj_add_event_cb(
                                stock_chart_child.chart_data[i],
                                draw_event_cb,
                                LV_EVENT_DRAW_TASK_ADDED,
                                NULL
                                );

                        lv_obj_add_flag(
                                stock_chart_child.chart_data[i],
                                LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS
                                );

                        stock_chart_child.series[i] = lv_chart_add_series(
                                stock_chart_child.chart_data[i],
                                lv_color_black(),
                                LV_CHART_AXIS_PRIMARY_Y
                                );

                        lv_obj_set_style_line_width(stock_chart_child.chart_data[i], 1, LV_PART_ITEMS);
                    }
                    /* { */
                    /*     // scale */
                    /*     lv_obj_t * scale = lv_scale_create(stock_chart_child.container_chart[i]); */
                    /*     lv_obj_set_size(scale, lv_pct(100), 20); */
                    /*     lv_scale_set_mode(scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM); */
                    /*     lv_obj_center(scale); */

                    /*     lv_scale_set_label_show(scale, true); */

                    /*     lv_scale_set_total_tick_count(scale, 31); */
                    /*     lv_scale_set_major_tick_every(scale, 5); */

                    /*     lv_obj_set_style_length(scale, 5, LV_PART_ITEMS); */
                    /*     lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR); */
                    /*     lv_scale_set_range(scale, 10, 40); */
                    /* } */
                }
            }
        }
    }

}




static esp_err_t build_alphavantage_url(widget_config_t *cfg, char *buffer, size_t buffer_size)
{
    const char *function = widget_config_list_get_value(cfg, "function");
    const char *symbol   = widget_config_list_get_value(cfg, "symbol");
    const char *interval = widget_config_list_get_value(cfg, "interval");
    const char *apikey   = widget_config_list_get_value(cfg, "apikey");

    if(!function || !symbol || !interval || !apikey)
        return ESP_FAIL;

    snprintf(buffer, buffer_size,
            "https://www.alphavantage.co/query?"
            "function=%s&symbol=%s&interval=%s&apikey=%s",
            function,
            symbol,
            interval,
            apikey);

    return ESP_OK;
}


static void alphavantage_request(stock_chart_t *child, const char *url)
{
    char *resp = NULL;
    int status, len;

    esp_err_t err = https_get_dyn(
            url,
            &resp,
            &status,
            &len);

    if (err == ESP_OK && resp)
    {
        float values[50];
        uint32_t count = 0;

        if (parse_alphavantage_history_50(resp, values, &count))
        {
            stock_chart_set_values(child, values, count);
        }
        ESP_LOGI(TAG, "HTTP %d, len=%d, count=%"PRIu32"", status, len, count);
        /* ESP_LOGI(TAG, "HTTP %d, len=%d, body=%s", status, len, resp); */
        stock_chart_set_values(child, values, 50);
    }
    if (resp)
        free(resp);
}


static void alphavantage_request_spot(stock_chart_t *child, const char *url)
{
    char *resp = NULL;
    int status, len;

    esp_err_t err = https_get_dyn(
            url,
            &resp,
            &status,
            &len);

    if (err == ESP_OK && resp)
    {
        float new_value;

        if (parse_alphavantage_spot(resp, &new_value))
        {
            stock_chart_add_value(child, new_value);
        }
        ESP_LOGI(TAG, "HTTP %d, len=%d, resp=%s, value=%0.2f", status, len, resp, new_value);
    }
    if (resp)
        free(resp);
}


static void stock_chart_set_values(stock_chart_t *child, float *values, uint32_t count)
{
    if (!child || !values || count < 2)
        return;

    /* --------------------------------------------------
     * Calcul min / max sur les 50 points
     * -------------------------------------------------- */
    float min = values[0];
    float max = values[0];

    for (uint32_t i = 1; i < count; i++)
    {
        if (values[i] < min) min = values[i];
        if (values[i] > max) max = values[i];
    }

    /* int32_t delta = max - min; */
    /* int32_t padding_top = delta / 6; */
    /* int32_t padding_bottom = delta / 10; */

    int32_t delta = max - min;
    int32_t padding = LV_MAX(delta / 8, max / 100);

    lv_chart_set_range(child->chart_data[0],
            LV_CHART_AXIS_PRIMARY_Y,
            min - padding,
            max + padding);
    /* Petite marge visuelle (2%) pour e-paper */
    /* float padding = (max - min) * 0.02f; */
    /* if (padding == 0) padding = 1.0f; */

    /* min -= padding; */
    /* max += padding; */

    /* --------------------------------------------------
     * Appliquer range dynamique
     * -------------------------------------------------- */
    /* lv_chart_set_range(child->chart_data[0], */
    /*                    LV_CHART_AXIS_PRIMARY_Y, */
    /*                    (int32_t)min, */
    /*                    (int32_t)max); */

    /* --------------------------------------------------
     * Reset chart
     * -------------------------------------------------- */
    lv_chart_set_all_value(child->chart_data[0],
                           child->series[0],
                           LV_CHART_POINT_NONE);

    /* --------------------------------------------------
     * Injecter les vraies valeurs
     * -------------------------------------------------- */
    for (uint32_t i = 0; i < count; i++)
    {
        lv_chart_set_next_value(child->chart_data[0],
                                child->series[0],
                                (int32_t)values[i]);
    }

    lv_chart_refresh(child->chart_data[0]);

    /* --------------------------------------------------
     * Update labels
     * -------------------------------------------------- */

    float last = values[count - 1];
    float prev = values[count - 2];
    float diff = last - prev;
    float percent = (prev != 0) ? (diff / prev) * 100.0f : 0.0f;

    char price_buf[32];
    char diff_buf[64];

    /* Prix principal */
    snprintf(price_buf, sizeof(price_buf), "%.2f", last);
    lv_label_set_text(child->price_label[0], price_buf);

    /* Diff */
    snprintf(diff_buf,
             sizeof(diff_buf),
             "%+.2f  (%+.2f%%)",
             diff,
             percent);

    lv_label_set_text(child->diff_label[0], diff_buf);

    /* --------------------------------------------------
     * Arrow dynamique (e-paper friendly)
     * -------------------------------------------------- */
    if (diff > 0.0f)
    {
        lv_label_set_text(child->arrow_label[0], ICON_SYSTEM_TRIANGLE_UP);
    }
    else if (diff < 0.0f)
    {
        lv_label_set_text(child->arrow_label[0], ICON_SYSTEM_TRIANGLE_DOWN);
    }
    else
    {
        lv_label_set_text(child->arrow_label[0], "-");
    }

    child->history_count = count;

    for (uint32_t i = 0; i < count; i++)
        child->history[i] = values[i];

    child->current_min = min;
    child->current_max = max;
}


static void stock_chart_add_value(stock_chart_t *child, float new_value)
{
    if (!child)
        return;

    /* --------------------------------------------------
     * Initialisation si vide
     * -------------------------------------------------- */
    if (child->history_count == 0)
    {
        child->history[0] = new_value;
        child->history_count = 1;
        child->current_min = new_value;
        child->current_max = new_value;
        return;
    }

    float previous_value = child->history[child->history_count - 1];

    /* --------------------------------------------------
     * Shift buffer si plein
     * -------------------------------------------------- */
    if (child->history_count >= 50)
    {
        for (int i = 1; i < 50; i++)
            child->history[i - 1] = child->history[i];

        child->history[49] = new_value;
    }
    else
    {
        child->history[child->history_count++] = new_value;
    }

    /* --------------------------------------------------
     * Vérifier dépassement range
     * -------------------------------------------------- */
    bool need_rescale = false;

    if (new_value < child->current_min || new_value > child->current_max)
    {
        need_rescale = true;
    }

    /* --------------------------------------------------
     * Si rescale nécessaire → recalcul complet
     * -------------------------------------------------- */
    if (need_rescale)
    {
        stock_chart_set_values(child,
                               child->history,
                               child->history_count);
        return;
    }

    /* --------------------------------------------------
     * Update simple (rapide)
     * -------------------------------------------------- */

    lv_chart_set_next_value(child->chart_data[0],
                            child->series[0],
                            (int32_t)new_value);

    lv_chart_refresh(child->chart_data[0]);

    /* --------------------------------------------------
     * Update labels
     * -------------------------------------------------- */
    float diff = new_value - previous_value;
    float percent = (previous_value != 0) ? (diff / previous_value) * 100.0f : 0.0f;

    char price_buf[32];
    char diff_buf[64];

    snprintf(price_buf, sizeof(price_buf), "%.2f", new_value);
    lv_label_set_text(child->price_label[0], price_buf);

    snprintf(diff_buf,
             sizeof(diff_buf),
             "%+.2f  (%+.2f%%)",
             diff,
             percent);

    lv_label_set_text(child->diff_label[0], diff_buf);

    if (diff > 0.0f)
        lv_label_set_text(child->arrow_label[0], ICON_SYSTEM_TRIANGLE_UP);
    else if (diff < 0.0f)
        lv_label_set_text(child->arrow_label[0], ICON_SYSTEM_TRIANGLE_DOWN);
    else
        lv_label_set_text(child->arrow_label[0], "-");
}


static bool parse_alphavantage_history_50(const char *json, float *out_values, uint32_t *out_count)
{
    if (!json || !out_values || !out_count)
        return false;

    cJSON *root = cJSON_Parse(json);
    if (!root)
        return false;

    if (cJSON_GetObjectItem(root, "Note"))
    {
        cJSON_Delete(root);
        return false;
    }

    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (!cJSON_IsArray(data))
    {
        cJSON_Delete(root);
        return false;
    }

    uint32_t total = cJSON_GetArraySize(data);
    if (total == 0)
    {
        cJSON_Delete(root);
        return false;
    }

    uint32_t count = total > STOCK_HISTORY_MAX_POINTS ?
                     STOCK_HISTORY_MAX_POINTS : total;

    /* AlphaVantage retourne du plus récent au plus ancien */
    /* On va lire les 50 premiers puis les inverser */
    for (uint32_t i = 0; i < count; i++)
    {
        cJSON *entry = cJSON_GetArrayItem(data, i);
        if (!cJSON_IsObject(entry))
            continue;

        cJSON *price = cJSON_GetObjectItem(entry, "price");
        if (!cJSON_IsString(price))
            continue;

        out_values[count - 1 - i] = strtof(price->valuestring, NULL);
    }

    *out_count = count;

    cJSON_Delete(root);
    return true;
}


static bool parse_alphavantage_spot(const char *json, float *out_price)
{
    if (!json || !out_price)
        return false;

    cJSON *root = cJSON_Parse(json);
    if (!root)
        return false;

    if (cJSON_GetObjectItem(root, "Note"))
    {
        cJSON_Delete(root);
        return false;
    }

    cJSON *price = cJSON_GetObjectItem(root, "price");
    if (!cJSON_IsString(price))
    {
        cJSON_Delete(root);
        return false;
    }

    *out_price = strtof(price->valuestring, NULL);

    cJSON_Delete(root);
    return true;
}
