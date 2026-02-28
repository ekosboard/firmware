#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// Bit masks for screen actions
#include <stdint.h>
#define SCREEN_ID_MASK          0x000000FF
#define SCREEN_ACTION_MASK      0x0000FF00

// Action value
#define SCREEN_ACTION_NONE                   0x00
#define SCREEN_ACTION_CLEAR                  0x01
#define SCREEN_ACTION_CLEAR_DRIVER           0x02
#define SCREEN_ACTION_DRAW                   0x04
#define SCREEN_ACTION_SWITCH                 0x08
#define SCREEN_ACTION_FORCE_REFRESH          0x10


// Composite actions
#define SCREEN_ACTION_CLEAR_ONLY            (SCREEN_ACTION_CLEAR)
#define SCREEN_ACTION_CLEAR_WITH_DRIVER     (SCREEN_ACTION_CLEAR | SCREEN_ACTION_CLEAR_DRIVER)
#define SCREEN_ACTION_DRAW_ONLY             (SCREEN_ACTION_DRAW)
#define SCREEN_ACTION_DRAW_WITH_DRIVER      (SCREEN_ACTION_DRAW | SCREEN_ACTION_CLEAR_DRIVER)
//#define SCREEN_ACTION_DRAW_FORCE_REFRESH    (SCREEN_ACTION_DRAW | SCREEN_ACTION_FORCE_REFRESH)
#define SCREEN_ACTION_SWITCH_ONLY           (SCREEN_ACTION_SWITCH)
#define SCREEN_ACTION_SWITCH_AND_CLEAR      (SCREEN_ACTION_SWITCH | SCREEN_ACTION_CLEAR)
//#define SCREEN_ACTION_SWITCH_FORCE_REFRESH  (SCREEN_ACTION_SWITCH | SCREEN_ACTION_FORCE_REFRESH)
#define SCREEN_ACTION_REFRESH               (SCREEN_ACTION_FORCE_REFRESH)
#define SCREEN_ACTION_REFRESH_AND_CLEAR     (SCREEN_ACTION_FORCE_REFRESH | SCREEN_ACTION_CLEAR)



#ifdef __cplusplus
extern "C" {
#endif

    void        screen_manager_task(void *pvParameters);
    void        notify_screen_manager(uint8_t action, uint8_t screen_id);

#ifdef __cplusplus
}
#endif
#endif
