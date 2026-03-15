# LVGL UI Simulator

A small Linux simulator to quickly develop and test LVGL widgets without rebuilding the ESP32 firmware.  
The project uses LVGL with the Linux port provided by LVGL.  

---
## Setup

1. Clone the submodule

```shel
git submodule update --init --recursive
```

This fetches the LVGL Linux port (`lv_port_linux`).

2. Add the LVGL configuration

Move the LVGL configuration file into the `lv_port_linux` directory:
```shell
mv lv_conf.defaults lv_port_linux/
```

3. Modify `lv_port_linux/CMakeLists.txt`

Add the simulator includes and sources.
```cmake
target_include_directories(lvglsim PRIVATE
    ../src/include
    ../src/include/widgets
)

# Load fonts
file(GLOB FONT_SOURCES "../src/font_C/*.c")

# Load icon fonts
file(GLOB FONT_ICONS "../src/font_icons/*.c")

# Load widget mocks
file(GLOB WIDGET_SOURCES "../src/widgets/*.c")

target_sources(lvglsim PRIVATE
    ${FONT_SOURCES}
    ${FONT_ICONS}
    ${WIDGET_SOURCES}
)

```

4. Build

```shell
sh build.sh
```

5. Add your mock widgets

Edit the file:
> `lv_port_linux/src/main.c`

and call your widget mock functions (for example simple_date_draw()).
```c
    /*Create a Demo*/
    widget_t *widget = malloc(sizeof(widget_t));
    if (!widget)
        return 1;

    widget->pos_x = 10;
    widget->pos_y = 10;
    widget->width = 200;
    widget->height = 200;

    simple_date_draw(lv_screen_active(), widget);
```

6. Rebuild and run the simulator

```shell
sh run.sh
```

---
## Project Structure
```
ui_simulator
├── build
├── lv_port_linux     # LVGL linux port (submodule)
└── src
    ├── font_C
    ├── font_icons
    ├── include
    └── widgets
```

---
## Goal

This simulator allows you to:
- develop LVGL widgets quickly
- test layouts and fonts
- iterate without rebuilding ESP32 firmware
- copy the final widget into the embedded firmware later.


