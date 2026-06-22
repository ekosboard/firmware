#ifndef APPLE_CALENDAR_H
#define APPLE_CALENDAR_H

#include "esp_err.h"
#include "misc/lv_types.h"
#include "caldav.h"
#include <stdint.h>
#include <stdbool.h>

#define APPLE_CALENDAR_FILE_PATH "apple_calendar.json"
#define APPLE_CALENDAR_MAX_EVENTS 16

/* Config keys attendues dans widget->config (template JSON) */
#define CFG_CALDAV_URL      "caldav_url"
#define CFG_USERNAME        "username"
#define CFG_ASP             "password_or_asp"
#define CFG_DAYS_AHEAD      "days_ahead"
#define CFG_MAX_EVENTS      "max_events"

/* Valeurs par défaut si les clés sont absentes du template */
#define DEFAULT_DAYS_AHEAD  7
#define DEFAULT_MAX_EVENTS  APPLE_CALENDAR_MAX_EVENTS

/* Structure interne du widget, stockée dans widget->child.
 * Contient les événements parsés (persistants entre les updates LVGL)
 * et les objets LVGL racines nécessaires à un erase propre. */
typedef struct apple_calendar_s {
    caldav_event_t  events[APPLE_CALENDAR_MAX_EVENTS];
    uint8_t         event_count;

    /* Objets LVGL — uniquement le container racine est nécessaire ici,
     * lv_obj_delete() supprime récursivement tous ses enfants. */
    lv_obj_t       *container_content;
} apple_calendar_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t widget_apple_calendar_draw(lv_obj_t *screen);
    esp_err_t widget_apple_calendar_erase(void);
    esp_err_t widget_apple_calendar_update(void);
    esp_err_t widget_apple_calendar_update_data(void);

#ifdef __cplusplus
}
#endif

#endif
