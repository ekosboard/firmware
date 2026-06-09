#!/usr/bin/env python3
import os
import sys
import glob
import json

BASE_DIR      = os.path.dirname(os.path.abspath(__file__))
COMPONENT_DIR = os.path.abspath(os.path.join(BASE_DIR, ".."))
WIDGET_DIR    = os.path.join(COMPONENT_DIR, "widget")
TEMPLATE_DIR  = os.path.abspath(os.path.join(COMPONENT_DIR, "../../littlefs/template"))
HEADER_PATH   = os.path.join(COMPONENT_DIR, "include", "widget_autogen.h")
SOURCE_PATH   = os.path.join(COMPONENT_DIR, "widget_autogen.c")
KCONFIG_PATH  = os.path.join(COMPONENT_DIR, "Kconfig.projbuild")

KCONFIG_ONLY = "--kconfig-only" in sys.argv
CODEGEN_ONLY = "--codegen-only" in sys.argv

# ── Widget discovery ──────────────────────────────────────────────────────────

def load_template_ids():
    template_map = {}
    if not os.path.exists(TEMPLATE_DIR):
        print(f"⚠️  Template dir not found: {TEMPLATE_DIR}")
        return template_map
    for filename in os.listdir(TEMPLATE_DIR):
        if not filename.endswith(".json"):
            continue
        try:
            with open(os.path.join(TEMPLATE_DIR, filename), "r", encoding="utf-8") as f:
                data = json.load(f)
            name = data.get("widget_type")
            wid  = data.get("id")
            if name and wid is not None:
                template_map[name] = wid
        except Exception as e:
            print(f"Error reading template {filename}: {e}")
    return template_map

def sorted_widgets():
    widgets = sorted([
        os.path.splitext(os.path.basename(f))[0]
        for f in glob.glob(os.path.join(WIDGET_DIR, "*.c"))
    ])
    if not widgets:
        raise RuntimeError("No widgets found in widget/")

    template_ids = load_template_ids()
    for w in widgets:
        if w not in template_ids:
            raise ValueError(f"No template ID found for widget '{w}'")

    return sorted(widgets, key=lambda w: template_ids[w])

# ── Kconfig generation ────────────────────────────────────────────────────────

def gen_kconfig(widgets):
    with open(KCONFIG_PATH, "w") as f:
        f.write('menu "EKOS -- Widgets"\n\n')
        for w in widgets:
            f.write(f'    config WIDGET_{w.upper()}\n')
            f.write(f'        bool "Enable {w.replace("_", " ").title()} Widget"\n')
            f.write(f'        default y\n\n')
        f.write("endmenu\n")
    print(f"✅ Generated: {KCONFIG_PATH}")

# ── Header + source generation ────────────────────────────────────────────────

SOURCE_TOP = """\
#include "widget.h"
#include "filesystem_interface.h"

widget_t widget_info_list[WIDGET_COUNT];
uint8_t size_widget_info_list;
"""

INIT_TOP = """\

/* Initializes the widget information list with predefined widgets */
void init_widget_list(void)
{
    uint8_t index = 0;
    mount_lfs();
"""

INIT_BOTTOM = """\

    unmount_lfs();
    for (uint8_t i = index; i < WIDGET_COUNT; i++) {
        widget_info_list[i] = (widget_t){0};
    }
    size_widget_info_list = index;
}
"""

def gen_header(widgets):
    with open(HEADER_PATH, "w") as f:
        f.write("#ifndef WIDGET_AUTOGEN_H\n#define WIDGET_AUTOGEN_H\n\n")

        f.write("// Enabled widget includes\n")
        for w in widgets:
            f.write(f"#ifdef CONFIG_WIDGET_{w.upper()}\n")
            f.write(f'    #include "widget/{w}.h"\n')
            f.write(f"#endif\n")

        f.write("\n// Total enabled widget count\n")
        f.write("#define WIDGET_COUNT_0 0\n")
        for i, w in enumerate(widgets):
            f.write(f"#ifdef CONFIG_WIDGET_{w.upper()}\n")
            f.write(f"    #define WIDGET_COUNT_{i+1} (WIDGET_COUNT_{i} + 1)\n")
            f.write(f"#else\n")
            f.write(f"    #define WIDGET_COUNT_{i+1} WIDGET_COUNT_{i}\n")
            f.write(f"#endif\n")
        f.write(f"#define WIDGET_COUNT WIDGET_COUNT_{len(widgets)}\n\n")

        f.write("// Widget type enum\n")
        f.write("typedef enum {\n")
        for w in widgets:
            f.write(f"#ifdef CONFIG_WIDGET_{w.upper()}\n")
            f.write(f"    WIDGET_TYPE_{w.upper()},\n")
            f.write(f"#endif\n")
        f.write("    WIDGET_TYPE_COUNT\n} widget_type_t;\n\n")

        f.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
        f.write("    void        init_widget_list(void);\n")
        f.write("    const char *get_widget_type_to_string(widget_type_t type);\n\n")
        f.write("#ifdef __cplusplus\n} /* extern \"C\" */\n#endif\n\n")
        f.write("#endif /* WIDGET_AUTOGEN_H */\n")
    print(f"✅ Generated: {HEADER_PATH}")

def gen_source(widgets):
    with open(SOURCE_PATH, "w") as f:
        f.write(SOURCE_TOP)

        f.write("\nconst char *get_widget_type_to_string(widget_type_t type)\n{\n")
        f.write("    switch (type)\n    {\n")
        for w in widgets:
            f.write(f"#ifdef CONFIG_WIDGET_{w.upper()}\n")
            f.write(f'        case WIDGET_TYPE_{w.upper()}: return "{w}";\n')
            f.write(f"#endif\n")
        f.write('        default: return "Unknown Widget";\n')
        f.write("    }\n}\n")

        f.write(INIT_TOP)
        for w in widgets:
            struct_name    = f"widget_{w}"
            filepath_macro = f"{w.upper()}_FILE_PATH"
            f.write(f"\n#ifdef CONFIG_WIDGET_{w.upper()}\n")
            f.write(f"    widget_info_list[index] = (widget_t){{\n")
            f.write(f"        .type                  = WIDGET_TYPE_{w.upper()},\n")
            f.write(f"        .lv_obj                = NULL,\n")
            f.write(f"        .child                 = NULL,\n")
            f.write(f"        .draw_function         = {struct_name}_draw,\n")
            f.write(f"        .erase_function        = {struct_name}_erase,\n")
            f.write(f"        .update_function       = {struct_name}_update,\n")
            f.write(f"        .update_data_function  = {struct_name}_update_data,\n")
            f.write(f"        .update_data_timestamp = 0,\n")
            f.write(f"        .update_schedule_start = 0,\n")
            f.write(f"        .update_schedule_end   = WIDGET_SCHEDULE_DISABLED,\n")
            f.write(f"        .config                = NULL\n")
            f.write(f"    }};\n")
            f.write(f"    init_widget_from_template(&widget_info_list[index++], {filepath_macro});\n")
            f.write(f"#endif\n")
        f.write(INIT_BOTTOM)
    print(f"✅ Generated: {SOURCE_PATH}")

# ── Entry point ───────────────────────────────────────────────────────────────

widgets = sorted_widgets()
print(f"Widgets detected: {', '.join(widgets)}")

if not CODEGEN_ONLY:
    gen_kconfig(widgets)

if not KCONFIG_ONLY:
    gen_header(widgets)
    gen_source(widgets)
