#ifndef CALDAV_H
#define CALDAV_H

#include "esp_err.h"
#include "time.h"
#include <stdbool.h>
#include <stddef.h>


// Max number of events we're willing to store for a response.
#define CALDAV_MAX_RAW_EVENTS       32
#define CALDAV_SUMMARY_MAX_LEN      128
#define CALDAV_LOCATION_MAX_LEN     128
#define CALDAV_UID_MAX_LEN          80

// Tags we capture from the multistatus response. Intentionally closed (no
// generic configurable system): we know exactly what we need right now
// (calendar-data) and in the near future (href, getetag for incremental
// sync or operations targeting a specific event).
typedef enum {
    CALDAV_TAG_NONE = -1,
    CALDAV_TAG_HREF = 0,
    CALDAV_TAG_GETETAG,
    CALDAV_TAG_CALENDAR_DATA,
    CALDAV_TAG_COUNT
} caldav_capture_tag_t;

// A raw event as extracted from the XML, before any iCal parsing.
// ical_data contains the full BEGIN:VCALENDAR...END:VCALENDAR block.
typedef struct caldav_raw_event_s {
    char *href;
    char *etag;
    char *ical_data;
} caldav_raw_event_t;

// Parsing state, passed via XML_SetUserData and retrieved in each handler.
typedef struct caldav_parse_state_s {
    // Accumulators for the <response> currently being read
    caldav_capture_tag_t current_tag;
    char *capture_buf[CALDAV_TAG_COUNT];
    size_t capture_len[CALDAV_TAG_COUNT];

    // Final result
    caldav_raw_event_t events[CALDAV_MAX_RAW_EVENTS];
    size_t event_count;

    // Used to track whether we're actually inside a <response> (and not,
    // say, inside a tag of the same name located elsewhere in the document,
    // even though in practice a CalDAV multistatus shouldn't have any)
    int response_depth;

    bool error;
} caldav_parse_state_t;


typedef struct caldav_event_s {
    time_t dtstart;         // 0 if absent/unparsable
    time_t dtend;           // 0 if absent/unparsable
    bool   all_day;         // true if DTSTART/DTEND were in VALUE=DATE format
    char   summary[CALDAV_SUMMARY_MAX_LEN];
    char   location[CALDAV_LOCATION_MAX_LEN];
    char   uid[CALDAV_UID_MAX_LEN];
    bool   has_rrule;       // informational only — no expansion (see warning)
} caldav_event_t;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Parses a CalDAV multistatus response and extracts the raw events
     *        from it (href / etag / unparsed calendar-data).
     *
     * @param xml_buf     Buffer containing the raw XML response (already fully
     *                    received, e.g. response_buf from https_request_raw)
     * @param xml_len     Buffer size
     * @param out_events  Output array, must point to a buffer of at least
     *                    CALDAV_MAX_RAW_EVENTS elements allocated by the caller
     * @param out_count   Number of events actually extracted
     *
     * @note  The .href/.etag/.ical_data fields of each event are dynamically
     *        allocated (malloc) — the caller is responsible for free()ing them
     *        once iCal parsing is complete.
     */
    esp_err_t caldav_xml_parse_multistatus(const char *xml_buf, int xml_len,
            caldav_raw_event_t *out_events, size_t *out_count);

    /**
     * @brief Frees the buffers allocated in a caldav_raw_event_t array produced
     *        by caldav_xml_parse_multistatus.
     */
    void caldav_xml_free_raw_events(caldav_raw_event_t *events, size_t count);

    /**
     * @brief Parses a raw iCal block (BEGIN:VCALENDAR...END:VCALENDAR, as
     *        produced by caldav_xml_parse_multistatus) and extracts the fields
     *        needed for display into a caldav_event_t.
     *
     * @param ical_data  Raw iCal block, NUL-terminated. MODIFIED IN PLACE by
     *                    line unfolding — do not reuse the buffer after this
     *                    call for anything other than freeing it.
     * @param out_event  Output structure, filled by this function
     *
     * @note  Only the first VEVENT encountered in the block is parsed. This is
     *        sufficient here since caldav_xml_parse_multistatus produces one
     *        block per <response>, and each CalDAV <response> corresponds to
     *        exactly one VEVENT (associated VTIMEZONEs are not events).
     */
    esp_err_t caldav_ical_parse_event(char *ical_data, caldav_event_t *out_event);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CALDAV_H */
