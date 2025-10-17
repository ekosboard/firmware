#ifndef WIDGET_TEMPLATE_INTERVAL_H
#define WIDGET_TEMPLATE_INTERVAL_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Parse a string interval into milliseconds.
     *
     * Converts a string like "1d12h30m" into its equivalent duration in milliseconds.
     * Supported suffixes:
     *   - 'd' = days
     *   - 'h' = hours
     *   - 'm' = minutes
     *   - 's' = seconds
     *
     * @param[in] str Interval string (e.g., "1h30m").
     *
     * @return Duration in milliseconds, or 0 if the string is invalid/empty.
     */
    uint32_t    widget_template_parse_interval_ms(const char *str);


    /**
     * @brief Format a millisecond interval into a human-readable string.
     *
     * Converts a duration in milliseconds into a compact string representation,
     * like "1d2h30m15s". The resulting string is written into the provided buffer.
     *
     * @param[in]  ms           Duration in milliseconds.
     * @param[out] buffer       Destination buffer for the formatted string.
     * @param[in]  buffer_size  Size of the buffer.
     */
    void        widget_template_format_interval_ms(uint32_t ms, char *buffer, size_t buffer_size);

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif
