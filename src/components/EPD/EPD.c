#include "EPD.h"
#include "freertos/idf_additions.h"

static EventGroupHandle_t epd_event_group;

/**
 * @brief Initializes the event group used for EPD events.
 * @details
 * - Creates an event group to manage synchronization for EPD-related tasks.
 * - Must be called before using any other functions related to this event group.
 */
void init_epd_event_group()
{
    epd_event_group = xEventGroupCreate();
}

/**
 * @brief Retrieves the event group handle for EPD events.
 * @return The handle to the EPD event group.
 * @note Ensure that `init_epd_event_group` has been called before using this function.
 */
EventGroupHandle_t get_epd_event_group()
{
    return epd_event_group;
}

/**
 * @brief Sets specific bits in the EPD event group.
 * @param bits The event bits to be set.
 * @details
 * - Updates the event group to signal the occurrence of a specific event.
 * - This function can be used to notify waiting tasks that an event has occurred.
 * @note The bits set here may need to be cleared elsewhere depending on usage.
 */
void set_epd_event(uint32_t bits)
{
    xEventGroupSetBits(epd_event_group, bits);
}
