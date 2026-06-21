#include "widget.h"
#include "widget/apple_calendar.h"
#include "widget_autogen.h"
#include "widget_config_list.h"
#include "HTTPS_request.h"
#include "esp_log.h"
#include "mbedtls/base64.h"
#include "font.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SECONDS_PER_DAY 86400
#define IS_EMPTY(s) (!(s) || (s)[0] == '\0')
static const char *TAG = "WIDGET_APPLE_CALENDAR";

// ----------------------------------------------------------------------------
// Helpers internes
// ----------------------------------------------------------------------------

/* Construit le header Authorization: Basic base64(user:asp).
 * out_buf doit faire au moins 256 octets. */
static esp_err_t build_auth_header(const char *username, const char *asp, char *out_buf, size_t out_buf_len)
{
    char credentials[256];
    int written = snprintf(credentials, sizeof(credentials), "%s:%s", username, asp);
    if (written < 0 || written >= (int)sizeof(credentials))
        return ESP_ERR_INVALID_SIZE;

    size_t b64_len = 0;
    // Premier appel pour connaître la taille requise
    mbedtls_base64_encode(NULL, 0, &b64_len,
            (const unsigned char *)credentials, written);

    unsigned char b64_buf[256];
    if (b64_len >= sizeof(b64_buf))
        return ESP_ERR_INVALID_SIZE;

    size_t actual_len = 0;
    if (mbedtls_base64_encode(b64_buf, sizeof(b64_buf), &actual_len,
                (const unsigned char *)credentials, written) != 0)
        return ESP_FAIL;

    b64_buf[actual_len] = '\0';
    written = snprintf(out_buf, out_buf_len, "Basic %s", b64_buf);
    if (written < 0 || written >= (int)out_buf_len)
        return ESP_ERR_INVALID_SIZE;

    return ESP_OK;
}

/* Construit le body XML de la calendar-query sur une fenêtre [now, now+days]. */
static int build_report_body(char *out_buf, size_t out_buf_len, int days_ahead)
{
    time_t now = time(NULL);
    time_t end = now + (time_t)days_ahead * SECONDS_PER_DAY;

    struct tm tm_start, tm_end;
    gmtime_r(&now, &tm_start);
    gmtime_r(&end, &tm_end);

    char start_str[17], end_str[17];
    strftime(start_str, sizeof(start_str), "%Y%m%dT%H%M%SZ", &tm_start);
    strftime(end_str,   sizeof(end_str),   "%Y%m%dT%H%M%SZ", &tm_end);

    return snprintf(out_buf, out_buf_len,
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
            "<c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">"
            "<d:prop><d:getetag/><c:calendar-data/></d:prop>"
            "<c:filter>"
            "<c:comp-filter name=\"VCALENDAR\">"
            "<c:comp-filter name=\"VEVENT\">"
            "<c:time-range start=\"%s\" end=\"%s\"/>"
            "</c:comp-filter>"
            "</c:comp-filter>"
            "</c:filter>"
            "</c:calendar-query>",
            start_str, end_str);
}

/* Formate une date pour l'en-tête de section : "Lundi 18 juin" */
static void format_day_header(time_t t, char *out_buf, size_t out_buf_len)
{
    struct tm *tm_local = localtime(&t);
    strftime(out_buf, out_buf_len, "%A %d %B", tm_local);
    // Capitalise la première lettre (strftime renvoie en minuscules sur Newlib)
    if (out_buf[0] >= 'a' && out_buf[0] <= 'z')
        out_buf[0] -= 32;
}

/* Formate une heure "HH:MM\nHH:MM" (début\nfin) ou "" si all_day. */
static void format_event_hours(const caldav_event_t *ev, char *out_buf, size_t out_buf_len)
{
    if (ev->all_day)
    {
        out_buf[0] = '\0';
        return;
    }
    struct tm *tm_start = localtime(&ev->dtstart);
    char start[6], end_s[6];
    strftime(start, sizeof(start), "%H:%M", tm_start);
    struct tm *tm_end = localtime(&ev->dtend);
    strftime(end_s, sizeof(end_s), "%H:%M", tm_end);
    snprintf(out_buf, out_buf_len, "%s\n%s", start, end_s);
}

/* Compare deux time_t pour vérifier s'ils tombent le même jour calendaire. */
static bool same_day(time_t a, time_t b)
{
    struct tm ta, tb;
    localtime_r(&a, &ta);
    localtime_r(&b, &tb);
    return ta.tm_year == tb.tm_year &&
        ta.tm_mon  == tb.tm_mon  &&
        ta.tm_mday == tb.tm_mday;
}

// ----------------------------------------------------------------------------
// Rendu LVGL
// ----------------------------------------------------------------------------

/* Construit l'arbre LVGL à partir des événements stockés dans child.
 * Appelé par draw() et aussi après update_data() pour rafraîchir l'affichage. */
static void render_events(lv_obj_t *parent, apple_calendar_t *child)
{
    // Nettoie les enfants existants sans supprimer le container parent
    lv_obj_clean(parent);

    if (child->event_count == 0)
    {
        lv_obj_t *lbl = lv_label_create(parent);
        lv_label_set_text(lbl, "No upcoming events");
        lv_obj_set_style_text_font(lbl, &roboto_reg_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        return;
    }

    time_t current_day = 0; // sentinelle "pas encore de jour en cours"

    for (int i = 0; i < child->event_count; i++)
    {
        const caldav_event_t *ev = &child->events[i];

        /* --- En-tête de jour si on change de journée --- */
        if (!same_day(current_day, ev->dtstart))
        {
            current_day = ev->dtstart;

            char day_str[48];
            format_day_header(current_day, day_str, sizeof(day_str));

            lv_obj_t *day_container = lv_obj_create(parent);
            lv_obj_set_width(day_container, LV_PCT(100));
            lv_obj_set_height(day_container, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_all(day_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(day_container, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_all(day_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(day_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(day_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(day_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(day_container, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(day_container, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_obj_t *day_title = lv_label_create(day_container);
            lv_label_set_text(day_title, day_str);
            lv_obj_set_style_text_font(day_title, &roboto_bold_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(day_title, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

            /* Events container sous ce titre de jour */
            lv_obj_t *events_container = lv_obj_create(day_container);
            lv_obj_set_width(events_container, LV_PCT(100));
            lv_obj_set_height(events_container, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_all(events_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(events_container, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_all(events_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(events_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(events_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(events_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(events_container, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(events_container, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);

            /* On va ajouter les event_rows à events_container.
             * Pour ça on continue la boucle avec `parent` temporairement
             * pointé sur events_container — mais on ne peut pas modifier
             * `parent` en cours de boucle proprement sans un second pointeur.
             * Solution : on utilise une boucle interne sur tous les events
             * du même jour, puis on avance i en conséquence. */
            int j = i;
            while (j < child->event_count && same_day(ev->dtstart, child->events[j].dtstart))
            {
                const caldav_event_t *ev_j = &child->events[j];

                lv_obj_t *event_row = lv_obj_create(events_container);
                lv_obj_set_width(event_row, LV_PCT(100));
                lv_obj_set_height(event_row, LV_SIZE_CONTENT);
                lv_obj_set_style_pad_all(event_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_left(event_row, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_right(event_row, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_top(event_row, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_bottom(event_row, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_margin_all(event_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(event_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_color(event_row, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(event_row, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_side(event_row, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_opa(event_row, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_radius(event_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_layout(event_row, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_flex_flow(event_row, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_flex_align(event_row,
                        LV_FLEX_ALIGN_SPACE_BETWEEN,
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

                /* Heures (colonne gauche) */
                char hours_str[16];
                format_event_hours(ev_j, hours_str, sizeof(hours_str));

                if (hours_str[0] != '\0')
                {
                    lv_obj_t *lbl_hours = lv_label_create(event_row);
                    lv_label_set_text(lbl_hours, hours_str);
                    lv_obj_set_style_text_font(lbl_hours, &roboto_reg_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_width(lbl_hours, 80); // largeur fixe pour aligner les titres
                }

                /* Titre de l'événement (colonne droite) */
                lv_obj_t *lbl_summary = lv_label_create(event_row);
                lv_label_set_text(lbl_summary, ev_j->summary[0] ? ev_j->summary : "(untitled)");
                lv_obj_set_style_text_font(lbl_summary, &roboto_bold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_flex_grow(lbl_summary, 1);
                lv_label_set_long_mode(lbl_summary, LV_LABEL_LONG_DOT);

                j++;
            }

            /* La boucle externe reprend à j (premier event du jour suivant).
             * On décrémente pour compenser le i++ de la boucle for. */
            i = j - 1;
        }
    }
}

// ----------------------------------------------------------------------------
// Fonctions publiques du widget
// ----------------------------------------------------------------------------

esp_err_t widget_apple_calendar_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_APPLE_CALENDAR, &widget) != ESP_OK)
        return ESP_FAIL;

    static apple_calendar_t child;
    memset(&child, 0, sizeof(apple_calendar_t));
    widget->child = &child;

    widget->lv_obj = lv_obj_create(screen);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_style_pad_all(widget->lv_obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(widget->lv_obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(widget->lv_obj, LV_OPA_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(widget->lv_obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(widget->lv_obj, LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(widget->lv_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(widget->lv_obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(widget->lv_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);

    child.container_content = lv_obj_create(widget->lv_obj);
    lv_obj_set_width(child.container_content, LV_PCT(100));
    lv_obj_set_flex_grow(child.container_content, 1);
    lv_obj_set_style_pad_all(child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(child.container_content, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_margin_all(child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(child.container_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(child.container_content, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(child.container_content, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Affichage initial vide (les données arrivent via update_data)
    lv_obj_t *lbl_loading = lv_label_create(child.container_content);
    lv_label_set_text(lbl_loading, "Loading...");
    lv_obj_set_style_text_font(lbl_loading, &roboto_reg_18, LV_PART_MAIN | LV_STATE_DEFAULT);


    return ESP_OK;
}

esp_err_t widget_apple_calendar_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_APPLE_CALENDAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    widget->lv_obj = NULL;
    widget->child = NULL;

    return ESP_OK;
}

esp_err_t widget_apple_calendar_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_APPLE_CALENDAR, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);

    return ESP_OK;
}

esp_err_t widget_apple_calendar_update_data(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_APPLE_CALENDAR, &widget) != ESP_OK)
        return ESP_FAIL;

    apple_calendar_t *child = (apple_calendar_t *)widget->child;
    if (!child)
        return ESP_FAIL;

    /* --- Lecture des config keys --- */
    const char *caldav_url = widget_config_list_get_value(widget->config, CFG_CALDAV_URL);
    const char *username = widget_config_list_get_value(widget->config, CFG_USERNAME);
    const char *asp = widget_config_list_get_value(widget->config, CFG_ASP);

    if (IS_EMPTY(caldav_url) || IS_EMPTY(username) || IS_EMPTY(asp))
    {
        ESP_LOGE(TAG, "Missing required config keys (caldav_url, username, password_or_asp)");
        return ESP_ERR_INVALID_STATE;
    }


    const char *days_str = widget_config_list_get_value(widget->config, CFG_DAYS_AHEAD);
    const char *max_events_str = widget_config_list_get_value(widget->config, CFG_MAX_EVENTS);

    int days_ahead = !IS_EMPTY(days_str) ? atoi(days_str)       : DEFAULT_DAYS_AHEAD;
    int max_events = !IS_EMPTY(max_events_str) ? atoi(max_events_str) : DEFAULT_MAX_EVENTS;
    /* int days_ahead = (days_str && days_str[0] != '\0') ? atoi(days_str) : DEFAULT_DAYS_AHEAD; */
    /* int max_events = (max_events_str && max_events_str[0] != '\0') ? atoi(max_events_str) : DEFAULT_MAX_EVENTS; */
    if (max_events <= 0 || max_events > APPLE_CALENDAR_MAX_EVENTS)
        max_events = APPLE_CALENDAR_MAX_EVENTS;

    /* --- Construction de la requête --- */
    char auth_header_value[256];
    if (build_auth_header(username, asp, auth_header_value, sizeof(auth_header_value)) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to build auth header");
        return ESP_FAIL;
    }

    char report_body[512];
    int body_len = build_report_body(report_body, sizeof(report_body), days_ahead);
    if (body_len <= 0 || body_len >= (int)sizeof(report_body))
    {
        ESP_LOGE(TAG, "Failed to build REPORT body");
        return ESP_FAIL;
    }

    http_header_t headers[] = {
        { "Authorization", auth_header_value },
        { "Content-Type",  "application/xml; charset=utf-8" },
        { "Depth",         "1" },
    };

    /* --- Requête REPORT --- */
    char *response_buf = NULL;
    int   http_status  = -1;
    int   resp_len     = 0;

    esp_err_t ret = https_request_raw(caldav_url,
            HTTP_METHOD_REPORT,
            headers,
            sizeof(headers) / sizeof(headers[0]),
            report_body,
            body_len,
            &response_buf,
            &http_status,
            &resp_len);

    if (ret != ESP_OK || http_status != 207)
    {
        ESP_LOGE(TAG, "REPORT request failed (err=%s, status=%d)", esp_err_to_name(ret), http_status);
        free(response_buf);
        return ESP_FAIL;
    }

    /* --- Parsing XML --- */
    caldav_raw_event_t raw_events[CALDAV_MAX_RAW_EVENTS];
    size_t raw_count = 0;

    ret = caldav_xml_parse_multistatus(response_buf, resp_len, raw_events, &raw_count);
    free(response_buf); // libéré dès que le XML est parsé, avant d'allouer les events
    response_buf = NULL;

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "XML parsing failed");
        return ESP_FAIL;
    }

    /* --- Parsing iCal + remplissage du child --- */
    child->event_count = 0;
    int count = 0;

    for (size_t i = 0; i < raw_count && count < max_events; i++)
    {
        caldav_event_t ev;
        if (caldav_ical_parse_event(raw_events[i].ical_data, &ev) == ESP_OK)
        {
            child->events[count++] = ev;
        }
    }

    caldav_xml_free_raw_events(raw_events, raw_count);
    child->event_count = (uint8_t)count;

    ESP_LOGI(TAG, "Loaded %d event(s)", child->event_count);

    /* --- Tri par dtstart (tri à bulles, N ≤ 16, acceptable) --- */
    for (int i = 0; i < child->event_count - 1; i++)
    {
        for (int j = 0; j < child->event_count - 1 - i; j++)
        {
            if (child->events[j].dtstart > child->events[j + 1].dtstart)
            {
                caldav_event_t tmp    = child->events[j];
                child->events[j]     = child->events[j + 1];
                child->events[j + 1] = tmp;
            }
        }
    }

    /* --- Redraw LVGL --- */
    render_events(child->container_content, child);
    return ESP_OK;
}
