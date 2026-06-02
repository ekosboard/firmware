#ifndef WAKE_COORDINATOR_H
#define WAKE_COORDINATOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    WAKE_SOURCE_UPDATE_MANAGER = 0,
    WAKE_SOURCE_SCREEN_SCHEDULER,
    WAKE_SOURCE_COUNT
} wake_source_t;

#ifdef __cplusplus
extern "C" {
#endif

    void wake_coordinator_init(TaskHandle_t *power_manager_handle);
    void wake_coordinator_set(wake_source_t source, uint32_t delay_ms);

#ifdef __cplusplus
}
#endif

#endif /* WAKE_COORDINATOR_H */
