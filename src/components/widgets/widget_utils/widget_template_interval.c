#include "widget_template_interval.h"
#include <ctype.h>
#include <inttypes.h>

uint32_t widget_template_parse_interval_ms(const char *str)
{
    if (!str || !*str)
        return 0;

    uint32_t total_ms = 0;
    uint32_t current = 0;

    for (const char *p = str; *p; ++p)
    {
        if (isdigit((unsigned char)*p))
        {
            current = current * 10 + (*p - '0');
        }
        else
        {
            switch (*p)
            {
                case 'd':
                    total_ms += current * 24 * 60 * 60 * 1000;
                    break;
                case 'h':
                    total_ms += current * 60 * 60 * 1000;
                    break;
                case 'm':
                    total_ms += current * 60 * 1000;
                    break;
                case 's':
                    total_ms += current * 1000;
                    break;
                default:
                    return 0;
            }
            current = 0;
        }
    }

    return total_ms;
}

void widget_template_format_interval_ms(uint32_t ms, char *buffer, size_t buffer_size)
{
    if (!buffer || buffer_size == 0)
        return;

    if (ms == 0)
    {
        snprintf(buffer, buffer_size, "1d");
        return;
    }

    uint32_t days = ms / (24 * 60 * 60 * 1000);
    ms %= 24 * 60 * 60 * 1000;
    uint32_t hours = ms / (60 * 60 * 1000);
    ms %= 60 * 60 * 1000;
    uint32_t minutes = ms / (60 * 1000);
    ms %= 60 * 1000;
    uint32_t seconds = ms / 1000;

    size_t offset = 0;

    if (days)
        offset += snprintf(buffer + offset, buffer_size - offset, "%"PRIu32"d", days);
    if (hours && offset < buffer_size)
        offset += snprintf(buffer + offset, buffer_size - offset, "%"PRIu32"h", hours);
    if (minutes && offset < buffer_size)
        offset += snprintf(buffer + offset, buffer_size - offset, "%"PRIu32"m", minutes);
    if ((seconds || offset == 0) && offset < buffer_size)
        snprintf(buffer + offset, buffer_size - offset, "%"PRIu32"s", seconds);
}

