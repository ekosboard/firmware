/**
 * @file caldav_ical.c
 * @brief Parser iCalendar (RFC 5545) minimal, limité aux champs nécessaires
 *        à l'affichage d'un événement dans le widget calendrier EKOS.
 *
 * ============================================================================
 * AVERTISSEMENT — LIMITATIONS VOLONTAIRES DE CETTE IMPLÉMENTATION (v1)
 * ============================================================================
 *
 * 1. GESTION DES FUSEAUX HORAIRES (TZID) :
 *    Ce parser NE LIT PAS les règles VTIMEZONE fournies par le serveur CalDAV
 *    dans la réponse. Pour une date du type "DTSTART;TZID=Europe/Paris:...",
 *    le paramètre TZID est ENTIÈREMENT IGNORÉ et la valeur est traitée comme
 *    une heure LOCALE DU DEVICE, convertie via mktime() qui s'appuie sur le
 *    fuseau configuré globalement (setenv("TZ", ...) + tzset()) côté EKOS.
 *
 *    Hypothèse posée : EKOS est un device physique à localisation fixe, donc
 *    le fuseau du calendrier de l'utilisateur correspond presque toujours au
 *    fuseau réel du device. Cette hypothèse est FAUSSE si :
 *      - l'utilisateur a un événement dans un calendrier configuré sur un
 *        fuseau différent de celui du device (ex: device à Paris, événement
 *        TZID=America/New_York) → l'heure affichée sera décalée.
 *      - le fuseau TZ du device n'est pas configuré correctement.
 *
 *    Si ce cas devient un problème réel pour les utilisateurs, la correction
 *    propre consisterait à parser le(s) bloc(s) VTIMEZONE associé(s) et à
 *    appliquer le bon décalage selon le TZID réel de l'événement, plutôt que
 *    de supposer qu'il correspond au fuseau du device.
 *
 * 2. RÉCURRENCE (RRULE) :
 *    Aucune expansion de récurrence. Si un événement a un RRULE, seule
 *    l'occurrence de base (DTSTART/DTEND tels que fournis) est retenue.
 *    Confirmé empiriquement : iCloud ne renvoie qu'une seule occurrence par
 *    calendar-query sur un événement récurrent (pas d'instances dupliquées
 *    à filtrer côté client).
 *
 * 3. AUTRES COMPOSANTS IGNORÉS :
 *    VALARM, VTIMEZONE, et tous les champs X-APPLE-* ne sont pas parsés.
 * ============================================================================
 */

#include "esp_log.h"
#include "esp_err.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "caldav.h"

static const char *TAG = "caldav_ical";

// ----------------------------------------------------------------------------
// Étape 1 : dépliage du line-folding (RFC 5545 §3.1)
// Une ligne logique repliée apparaît comme :
//   "DTSTART;TZID=Europe/Paris:202\r\n 60619T090000"
// c'est-à-dire un CRLF suivi d'un espace ou d'une tabulation, qui doit être
// supprimé pour reconstituer la ligne logique complète.
// ----------------------------------------------------------------------------

/**
 * @brief Unfolds iCal line-folding in a mutable copy of the buffer.
 *        Works in place: replaces each "\r\n " or "\n " sequence
 *        (continuation) with nothing, shifting the rest of the string.
 *
 * @param buf  Mutable buffer (NUL-terminated), modified in place.
 *             The buffer shrinks or stays the same size, never grows.
 */
static void ical_unfold_lines(char *buf)
{
    char *read = buf;
    char *write = buf;

    while (*read)
    {
        // Détecte \r\n ou \n suivi d'un espace/tab : continuation à supprimer
        bool is_fold = false;
        size_t newline_len = 0;

        if (read[0] == '\r' && read[1] == '\n' && (read[2] == ' ' || read[2] == '\t'))
        {
            is_fold = true;
            newline_len = 3; // \r\n + le caractère d'espacement
        }
        else if (read[0] == '\n' && (read[1] == ' ' || read[1] == '\t'))
        {
            is_fold = true;
            newline_len = 2; // \n + le caractère d'espacement
        }

        if (is_fold)
        {
            read += newline_len; // on saute le CRLF/LF + l'espace de continuation
            continue;             // sans rien écrire : la ligne suivante se colle à la précédente
        }

        *write++ = *read++;
    }

    *write = '\0';
}

// ----------------------------------------------------------------------------
// Étape 2 : découpage ligne par ligne + extraction des champs utiles
// ----------------------------------------------------------------------------

/**
 * @brief Splits "NAME;PARAM1=X;PARAM2=Y:VALUE" into property name,
 *        parameter block (can be NULL if absent), and value.
 *        Modifies the line in place (inserts '\0's).
 *
 * @return true if the line could be split (presence of a ':')
 */
static bool ical_split_property_line(char *line, char **out_name, char **out_params, char **out_value)
{
    // Le ':' qui sépare la définition de propriété (nom + params) de la
    // valeur est le premier ':' rencontré qui n'est pas à l'intérieur d'une
    // valeur de paramètre entre guillemets. Pour nos besoins (TZID, VALUE),
    // on n'a jamais de ':' dans les valeurs de paramètres concernées, donc
    // on prend simplement le premier ':' — suffisant pour les propriétés
    // qu'on extrait (DTSTART, DTEND, SUMMARY, LOCATION, UID, RRULE).
    char *colon = strchr(line, ':');
    if (!colon)
    {
        return false;
    }
    *colon = '\0';
    *out_value = colon + 1;

    char *semicolon = strchr(line, ';');
    if (semicolon)
    {
        *semicolon = '\0';
        *out_name = line;
        *out_params = semicolon + 1;
    }
    else
    {
        *out_name = line;
        *out_params = NULL;
    }

    return true;
}

/**
 * @brief Looks for a "KEY=VALUE" parameter in the parameter block
 *        (e.g. "TZID=Europe/Paris" in "TZID=Europe/Paris" alone, or
 *        in "VALUE=URI;X-APPLE-RADIUS=..." for a more complex case).
 *        Parameters are separated by ';'.
 *
 * @param params  Parameter block (can be NULL), modified in place
 * @param key     Name of the parameter to find (e.g. "TZID", "VALUE")
 * @return Pointer to the parameter value in the buffer (NUL-terminated
 *         in place), or NULL if absent.
 */
static char *ical_find_param(char *params, const char *key)
{
    if (!params)
    {
        return NULL;
    }

    char *cursor = params;
    size_t key_len = strlen(key);

    while (cursor && *cursor)
    {
        char *next_semicolon = strchr(cursor, ';');
        if (next_semicolon)
        {
            *next_semicolon = '\0';
        }

        char *eq = strchr(cursor, '=');
        if (eq && (size_t)(eq - cursor) == key_len && strncmp(cursor, key, key_len) == 0)
        {
            return eq + 1;
        }

        if (next_semicolon)
        {
            cursor = next_semicolon + 1;
        }
        else
        {
            cursor = NULL;
        }
    }

    return NULL;
}

// ----------------------------------------------------------------------------
// Étape 3 : parsing des valeurs de date
// ----------------------------------------------------------------------------

/**
 * @brief Converts n ASCII digits to an integer, without strict validation
 *        (we assume a well-formed iCal format at this stage — the request
 *        comes from a trusted CalDAV server, not raw user input).
 */
static int atoi_n(const char *s, int n)
{
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        if (!isdigit((unsigned char)s[i]))
        {
            return 0;
        }
        result = result * 10 + (s[i] - '0');
    }
    return result;
}

/**
 * @brief Parses an iCal date into a time_t, handling the 3 formats (see
 *        the warning at the top of the file for the TZID limitation).
 *
 * Supported formats:
 *   - "20260618T090000Z"        -> explicit UTC
 *   - "20260618T090000"         -> local time (with or without TZID as a
 *                                  parameter, TZID being ignored, see warning)
 *   - "20260619" (with VALUE=DATE as a parameter) -> all-day, local midnight
 *
 * @param value     The raw property value (after the ':')
 * @param is_date_only  true if the VALUE=DATE parameter was present
 * @param out_time  Result
 * @return true if parsing succeeded
 */
static bool ical_parse_datetime(const char *value, bool is_date_only, time_t *out_time)
{
    struct tm tm_val = {0};
    size_t len = strlen(value);

    if (is_date_only)
    {
        // Format "YYYYMMDD", 8 caractères
        if (len < 8)
        {
            return false;
        }
        tm_val.tm_year = atoi_n(value, 4) - 1900;
        tm_val.tm_mon  = atoi_n(value + 4, 2) - 1;
        tm_val.tm_mday = atoi_n(value + 6, 2);
        tm_val.tm_hour = 0;
        tm_val.tm_min  = 0;
        tm_val.tm_sec  = 0;
        tm_val.tm_isdst = -1; // laisse mktime déterminer le DST

        *out_time = mktime(&tm_val);
        return *out_time != (time_t)-1;
    }

    // Format "YYYYMMDDTHHMMSS" ou "YYYYMMDDTHHMMSSZ", au moins 15 caractères
    if (len < 15)
    {
        return false;
    }

    tm_val.tm_year = atoi_n(value, 4) - 1900;
    tm_val.tm_mon  = atoi_n(value + 4, 2) - 1;
    tm_val.tm_mday = atoi_n(value + 6, 2);
    // value[8] doit être 'T'
    tm_val.tm_hour = atoi_n(value + 9, 2);
    tm_val.tm_min  = atoi_n(value + 11, 2);
    tm_val.tm_sec  = atoi_n(value + 13, 2);

    bool is_utc = (len >= 16 && value[15] == 'Z');

    if (is_utc)
    {
        // timegm() convertit un struct tm interprété comme UTC en time_t,
        // sans tenir compte du fuseau local — exactement ce qu'il faut ici.
        /* *out_time = timegm(&tm_val); */
        // Remplace timegm(&tm_val) par :
        char *old_tz = getenv("TZ");
        setenv("TZ", "UTC0", 1);
        tzset();
        time_t result = mktime(&tm_val);
        if (old_tz) setenv("TZ", old_tz, 1);
        else unsetenv("TZ");
        tzset();
        *out_time = result;
    }
    else
    {
        // Heure locale (TZID ignoré, cf. avertissement en tête de fichier) :
        // mktime() interprète tm_val selon le fuseau TZ configuré sur le device.
        tm_val.tm_isdst = -1;
        *out_time = mktime(&tm_val);
    }

    return *out_time != (time_t)-1;
}

// ----------------------------------------------------------------------------
// API publique
// ----------------------------------------------------------------------------

esp_err_t caldav_ical_parse_event(char *ical_data, caldav_event_t *out_event)
{
    if (!ical_data || !out_event)
    {
        return ESP_ERR_INVALID_ARG;
    }

    memset(out_event, 0, sizeof(caldav_event_t));

    ical_unfold_lines(ical_data);

    bool in_vevent = false;
    bool in_valarm = false;
    char *line = ical_data;

    while (line && *line)
    {
        char *line_end = strpbrk(line, "\r\n");
        char *next_line = NULL;

        if (line_end)
        {
            next_line = line_end + (line_end[0] == '\r' && line_end[1] == '\n' ? 2 : 1);
            *line_end = '\0';
        }

        if (strlen(line) == 0)
        {
            line = next_line;
            continue;
        }

        if (strcmp(line, "BEGIN:VEVENT") == 0)
        {
            in_vevent = true;
            line = next_line;
            continue;
        }

        if (strcmp(line, "END:VEVENT") == 0)
        {
            // On a fini le premier (et a priori unique) VEVENT du bloc.
            break;
        }

        if (strcmp(line, "BEGIN:VALARM") == 0)
        {
            in_valarm = true;
        }

        if (strcmp(line, "END:VALARM") == 0)
        { 
            in_valarm = false;
        }

        if (in_vevent && !in_valarm)
        {
            char *name = NULL;
            char *params = NULL;
            char *value = NULL;

            if (ical_split_property_line(line, &name, &params, &value))
            {
                if (strcmp(name, "SUMMARY") == 0)
                {
                    strncpy(out_event->summary, value, CALDAV_SUMMARY_MAX_LEN - 1);
                }
                else if (strcmp(name, "LOCATION") == 0)
                {
                    strncpy(out_event->location, value, CALDAV_LOCATION_MAX_LEN - 1);
                }
                else if (strcmp(name, "UID") == 0)
                {
                    strncpy(out_event->uid, value, CALDAV_UID_MAX_LEN - 1);
                }
                else if (strcmp(name, "RRULE") == 0)
                {
                    out_event->has_rrule = true;
                }
                else if (strcmp(name, "DTSTART") == 0 || strcmp(name, "DTEND") == 0)
                {
                    char *value_param = ical_find_param(params, "VALUE");
                    bool is_date_only = (value_param != NULL && strcmp(value_param, "DATE") == 0);
                    /* bool is_date_only = ical_find_param(params, "VALUE") != NULL && */
                    /*     strcmp(ical_find_param(params, "VALUE"), "DATE") == 0; */

                    if (is_date_only)
                    {
                        out_event->all_day = true;
                    }

                    time_t parsed;
                    if (ical_parse_datetime(value, is_date_only, &parsed))
                    {
                        if (strcmp(name, "DTSTART") == 0)
                        {
                            out_event->dtstart = parsed;
                        }
                        else
                        {
                            out_event->dtend = parsed;
                        }
                    }
                    else
                    {
                        ESP_LOGW(TAG, "Failed to parse %s value: %s", name, value);
                    }
                }
                // Tous les autres champs (CREATED, DTSTAMP, SEQUENCE,
                // X-APPLE-*, TRANSP, ...) sont ignorés silencieusement.
            }
        }

        line = next_line;
    }

    if (out_event->uid[0] == '\0')
    {
        ESP_LOGW(TAG, "Parsed event without UID — unexpected for a well-formed VEVENT");
    }

    return ESP_OK;
}
