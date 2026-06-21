#include "expat.h"
#include "caldav.h"
#include "esp_log.h"
#include "esp_err.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static const char *TAG = "caldav_xml";

// ----------------------------------------------------------------------------
// Helpers internes
// ----------------------------------------------------------------------------

static caldav_capture_tag_t tag_name_to_enum(const char *name)
{
    // Note : avec XML_ParserCreate(NULL) (pas de namespace processing actif),
    // expat nous donne le nom local du tag, sans le préfixe (ex: "calendar-data",
    // pas "c:calendar-data")
    if (strcmp(name, "href") == 0)
    {
        return CALDAV_TAG_HREF;
    }
    if (strcmp(name, "getetag") == 0)
    {
        return CALDAV_TAG_GETETAG;
    }
    if (strcmp(name, "calendar-data") == 0)
    {
        return CALDAV_TAG_CALENDAR_DATA;
    }
    return CALDAV_TAG_NONE;
}

/**
 * @brief Appends data to the accumulator buffer for the currently captured tag.
 *        malloc/realloc pattern, identical to the one used in https_request_raw.
 */
static esp_err_t accumulate(caldav_parse_state_t *state, const char *s, int len)
{
    if (state->current_tag == CALDAV_TAG_NONE || len <= 0)
    {
        return ESP_OK;
    }

    caldav_capture_tag_t tag = state->current_tag;
    size_t old_len = state->capture_len[tag];
    char *new_buf = realloc(state->capture_buf[tag], old_len + len + 1);
    if (!new_buf)
    {
        ESP_LOGE(TAG, "realloc failed while accumulating tag %d (%zu bytes)", tag, old_len + len);
        return ESP_ERR_NO_MEM;
    }

    memcpy(new_buf + old_len, s, len);
    new_buf[old_len + len] = '\0';

    state->capture_buf[tag] = new_buf;
    state->capture_len[tag] = old_len + len;

    return ESP_OK;
}

/**
 * @brief Frees the capture buffers (but not the events already published
 *        in state->events, which now belong to the caller).
 */
static void reset_capture_buffers(caldav_parse_state_t *state)
{
    for (int i = 0; i < CALDAV_TAG_COUNT; i++)
    {
        free(state->capture_buf[i]);
        state->capture_buf[i] = NULL;
        state->capture_len[i] = 0;
    }
}

/**
 * @brief Called on </response> closure: turns the accumulated buffers into
 *        a finalized caldav_raw_event_t, appended to the array.
 */
static void publish_event(caldav_parse_state_t *state)
{
    if (state->event_count >= CALDAV_MAX_RAW_EVENTS)
    {
        ESP_LOGW(TAG, "Max raw events reached (%d), dropping extra response", CALDAV_MAX_RAW_EVENTS);
        reset_capture_buffers(state);
        return;
    }

    // On ne publie un event que s'il contient au moins calendar-data —
    // un <response> sans ça (ex: erreur 404 sur une ressource) n'est pas
    // un événement exploitable.
    if (!state->capture_buf[CALDAV_TAG_CALENDAR_DATA])
    {
        ESP_LOGW(TAG, "Response without calendar-data, skipping");
        reset_capture_buffers(state);
        return;
    }

    caldav_raw_event_t *ev = &state->events[state->event_count];
    ev->href = state->capture_buf[CALDAV_TAG_HREF];               // peut être NULL si absent
    ev->etag = state->capture_buf[CALDAV_TAG_GETETAG];            // peut être NULL si absent
    ev->ical_data = state->capture_buf[CALDAV_TAG_CALENDAR_DATA]; // garanti non-NULL ici

    state->event_count++;

    // Important : on transfère la propriété des buffers à `ev`, donc on ne
    // doit PAS les free() ici — juste réinitialiser les pointeurs locaux
    // sans libérer la mémoire, contrairement à reset_capture_buffers().
    for (int i = 0; i < CALDAV_TAG_COUNT; i++)
    {
        state->capture_buf[i] = NULL;
        state->capture_len[i] = 0;
    }
}

// ----------------------------------------------------------------------------
// Handlers Expat
// ----------------------------------------------------------------------------

static void XMLCALL start_element_handler(void *user_data, const char *name, const char **atts)
{
    caldav_parse_state_t *state = (caldav_parse_state_t *)user_data;

    if (strcmp(name, "response") == 0)
    {
        state->response_depth++;
        return;
    }

    caldav_capture_tag_t tag = tag_name_to_enum(name);
    if (tag != CALDAV_TAG_NONE)
    {
        // On entre dans un tag à capturer. S'il était déjà non-vide (ne
        // devrait pas arriver en pratique sur une réponse CalDAV valide,
        // mais on reste défensif), on accumule simplement à la suite.
        state->current_tag = tag;
    }
}

static void XMLCALL end_element_handler(void *user_data, const char *name)
{
    caldav_parse_state_t *state = (caldav_parse_state_t *)user_data;

    if (strcmp(name, "response") == 0)
    {
        if (state->response_depth > 0)
        {
            state->response_depth--;
        }
        publish_event(state);
        return;
    }

    caldav_capture_tag_t tag = tag_name_to_enum(name);
    if (tag != CALDAV_TAG_NONE && state->current_tag == tag)
    {
        state->current_tag = CALDAV_TAG_NONE;
    }
}

static void XMLCALL char_data_handler(void *user_data, const char *s, int len)
{
    caldav_parse_state_t *state = (caldav_parse_state_t *)user_data;

    if (accumulate(state, s, len) != ESP_OK)
    {
        state->error = true;
    }
}

// ----------------------------------------------------------------------------
// API publique de cette couche
// ----------------------------------------------------------------------------

esp_err_t caldav_xml_parse_multistatus(const char *xml_buf, int xml_len,
        caldav_raw_event_t *out_events, size_t *out_count)
{
    if (!xml_buf || xml_len <= 0 || !out_events || !out_count)
    {
        return ESP_ERR_INVALID_ARG;
    }

    caldav_parse_state_t state = {0};
    state.current_tag = CALDAV_TAG_NONE;

    XML_Parser parser = XML_ParserCreate(NULL);
    if (!parser)
    {
        ESP_LOGE(TAG, "Failed to create XML parser");
        return ESP_FAIL;
    }

    XML_SetUserData(parser, &state);
    XML_SetElementHandler(parser, start_element_handler, end_element_handler);
    XML_SetCharacterDataHandler(parser, char_data_handler);

    enum XML_Status status = XML_Parse(parser, xml_buf, xml_len, 1);

    esp_err_t ret = ESP_OK;

    if (status == XML_STATUS_ERROR)
    {
        ESP_LOGE(TAG, "XML parse error: %s at line %lu",
                XML_ErrorString(XML_GetErrorCode(parser)),
                XML_GetCurrentLineNumber(parser));
        ret = ESP_FAIL;
    }
    else if (state.error)
    {
        ESP_LOGE(TAG, "Accumulation error during parsing (likely OOM)");
        ret = ESP_ERR_NO_MEM;
    }

    XML_ParserFree(parser);

    if (ret != ESP_OK)
    {
        // Nettoyage de tout ce qui aurait pu être publié avant l'erreur,
        // pour ne rien laisser fuiter côté appelant.
        for (size_t i = 0; i < state.event_count; i++)
        {
            free(state.events[i].href);
            free(state.events[i].etag);
            free(state.events[i].ical_data);
        }
        // Et les buffers en cours d'accumulation au moment de l'erreur
        reset_capture_buffers(&state);
        *out_count = 0;
        return ret;
    }

    memcpy(out_events, state.events, state.event_count * sizeof(caldav_raw_event_t));
    *out_count = state.event_count;

    ESP_LOGI(TAG, "Extracted %zu event(s) from multistatus response", state.event_count);

    return ESP_OK;
}

void caldav_xml_free_raw_events(caldav_raw_event_t *events, size_t count)
{
    if (!events)
    {
        return;
    }
    for (size_t i = 0; i < count; i++)
    {
        free(events[i].href);
        free(events[i].etag);
        free(events[i].ical_data);
        events[i].href = NULL;
        events[i].etag = NULL;
        events[i].ical_data = NULL;
    }
}
