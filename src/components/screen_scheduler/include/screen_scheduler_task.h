#ifndef SCREEN_SCHEDULER_TASK_H
#define SCREEN_SCHEDULER_TASK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef __cplusplus
extern "C" {
#endif

    void screen_scheduler_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* SCREEN_SCHEDULER_TASK_H */
