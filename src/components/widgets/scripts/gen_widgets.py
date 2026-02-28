#!/usr/bin/env python3
import os
import sys
import glob
import json

# Base = dossier où se trouve le script lui-même
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# On remonte jusqu’au dossier du composant
COMPONENT_DIR = os.path.abspath(os.path.join(BASE_DIR, ".."))

# Dossier contenant les fichiers de widgets
WIDGET_DIR = os.path.join(COMPONENT_DIR, "widget")

# Dossier contenant les templates (adapté à ton arborescence)
TEMPLATE_DIR = os.path.abspath(os.path.join(COMPONENT_DIR, "../../littlefs/template"))

# Dossier de sortie
OUTPUT_DIR = COMPONENT_DIR

# Fichiers de sortie
HEADER_PATH = os.path.join(OUTPUT_DIR, "include", "widget_autogen.h")
SOURCE_PATH = os.path.join(OUTPUT_DIR, "widget_autogen.c")
KCONFIG_PATH = os.path.join(OUTPUT_DIR, "Kconfig.projbuild")

print("=== DEBUG PATHS ===")
print("Current working directory :", os.getcwd())
print("Script file location      :", os.path.abspath(__file__))
print("BASE_DIR                  :", BASE_DIR)
print("COMPONENT_DIR             :", COMPONENT_DIR)
print("WIDGET_DIR                :", WIDGET_DIR)
print("TEMPLATE_DIR              :", TEMPLATE_DIR)
print("OUTPUT_DIR                :", OUTPUT_DIR)
print("====================\n")

# --------------------------------------------------------------------
#  Chargement des IDs depuis les templates JSON
# --------------------------------------------------------------------
def load_template_ids():
    template_map = {}
    if not os.path.exists(TEMPLATE_DIR):
        print("⚠️ Aucun dossier de templates trouvé :", TEMPLATE_DIR)
        return template_map

    for filename in os.listdir(TEMPLATE_DIR):
        if not filename.endswith(".json"):
            continue
        path = os.path.join(TEMPLATE_DIR, filename)
        try:
            with open(path, "r", encoding="utf-8") as f:
                data = json.load(f)
            name = data.get("widget_type")
            wid = data.get("id")
            if name and wid is not None:
                template_map[name] = wid
        except Exception as e:
            print(f"Erreur lecture template {filename}: {e}")

    return template_map


# --------------------------------------------------------------------
#  Découverte des widgets existants dans le code
# --------------------------------------------------------------------
widgets = sorted([
    os.path.splitext(os.path.basename(f))[0]
    for f in glob.glob(os.path.join(WIDGET_DIR, "*.c"))
])

if not widgets:
    raise RuntimeError("Aucun widget trouvé dans le dossier widget/")

print(f"Widgets détectés : {', '.join(widgets)}")

# --------------------------------------------------------------------
#  Tri des widgets selon les templates JSON (par ID)
# --------------------------------------------------------------------
template_ids = load_template_ids()

widgets_sorted = []
for w in widgets:
    if w not in template_ids:
        raise ValueError(f"❌ Aucun ID trouvé pour le widget '{w}' dans les templates.")
    widgets_sorted.append(w)

# Tri selon l'ID (ordre croissant)
widgets_sorted.sort(key=lambda w: template_ids[w])

print(f"Ordre final des widgets : {', '.join(widgets_sorted)}")

# --------------------------------------------------------------------
#  Génération du header autogen
# --------------------------------------------------------------------
HEADER_TOP = """#ifndef WIDGET_AUTOGEN_H
#define WIDGET_AUTOGEN_H

"""

SOURCE_TOP = """#include "widget.h"
#include "filesystem_interface.h"

widget_t widget_info_list[WIDGET_COUNT];
uint8_t size_widget_info_list;
"""

INIT_TOP = """
/* Initializes the widget information list with predefined widgets */
void init_widget_list(void)
{
    uint8_t index = 0;
    mount_lfs();
"""

INIT_BOTTOM = """
    unmount_lfs();
    for (uint8_t i = index; i < WIDGET_COUNT; i++) {
        widget_info_list[i] = (widget_t){0};
    }

    size_widget_info_list = index;
}
"""

# HEADER
with open(HEADER_PATH, "w") as header:
    header.write(HEADER_TOP)
    header.write("// Includes des widgets activés\n")

    for w in widgets_sorted:
        macro = f"CONFIG_WIDGET_{w.upper()}"
        header.write(f"#ifdef {macro}\n")
        header.write(f'    #include "widget/{w}.h"\n')
        header.write(f"#endif\n")

    header.write("\n// Nombre total de widgets activés\n")
    header.write("#define WIDGET_COUNT ( \\\n")

    for i, w in enumerate(widgets_sorted):
        macro = f"CONFIG_WIDGET_{w.upper()}"
        if i < len(widgets_sorted) - 1:
            header.write(f"    ({macro} ? 1 : 0) + \\\n")
        else:
            header.write(f"    ({macro} ? 1 : 0) \\\n")
    header.write(")\n\n")

    header.write("// Type des widgets\n")
    header.write("typedef enum {\n")
    for w in widgets_sorted:
        macro = f"CONFIG_WIDGET_{w.upper()}"
        header.write(f"#ifdef {macro}\n")
        header.write(f"    WIDGET_TYPE_{w.upper()},\n")
        header.write(f"#endif\n")
    header.write("    WIDGET_TYPE_COUNT\n} widget_type_t;\n\n")

    header.write("// Fonctions exposées\n")
    header.write("#ifdef __cplusplus\n")
    header.write("extern \"C\" {\n")
    header.write("#endif\n\n")

    header.write("    void        init_widget_list(void);\n")
    header.write("    const char *get_widget_type_to_string(widget_type_t type);\n\n")

    header.write("#ifdef __cplusplus\n")
    header.write("} /*extern \"C\"*/\n")
    header.write("#endif\n")
    header.write("#endif")

print(f"✅ Généré : {HEADER_PATH}")

# --------------------------------------------------------------------
#  Génération du fichier source autogen
# --------------------------------------------------------------------
with open(SOURCE_PATH, "w") as source:
    source.write(SOURCE_TOP)

    # get_widget_type_to_string()
    source.write("\nconst char *get_widget_type_to_string(widget_type_t type)\n{\n")
    source.write("    switch (type)\n    {\n")
    for w in widgets_sorted:
        macro = f"CONFIG_WIDGET_{w.upper()}"
        source.write(f"#ifdef {macro}\n")
        source.write(f'        case WIDGET_TYPE_{w.upper()}: return "{w}";\n')
        source.write(f"#endif\n")
    source.write('        default: return "Unknown Widget";\n')
    source.write("    }\n}\n")

    # init_widget_list()
    source.write(INIT_TOP)

    for w in widgets_sorted:
        macro = f"CONFIG_WIDGET_{w.upper()}"
        struct_name = f"widget_{w}"
        filepath_macro = f"{w.upper()}_FILE_PATH"

        source.write(f"\n#ifdef {macro}\n")
        source.write(f"    widget_info_list[index] = (widget_t){{\n")
        source.write(f"        .type = WIDGET_TYPE_{w.upper()},\n")
        source.write(f"        .lv_obj = NULL,\n")
        source.write(f"        .child = NULL,\n")
        source.write(f"        .draw_function = {struct_name}_draw,\n")
        source.write(f"        .erase_function = {struct_name}_erase,\n")
        source.write(f"        .update_function = {struct_name}_update,\n")
        source.write(f"        .update_data_function = {struct_name}_update_data,\n")
        source.write(f"        .update_data_timestamp = 0,\n")
        source.write(f"        .config = NULL\n")
        source.write(f"    }};\n")
        source.write(f"    init_widget_from_template(&widget_info_list[index++], {filepath_macro});\n")
        source.write(f"#endif\n")

    source.write(INIT_BOTTOM)

print(f"✅ Généré : {SOURCE_PATH}")

# --------------------------------------------------------------------
#  Génération du Kconfig
# --------------------------------------------------------------------
with open(KCONFIG_PATH, "w") as kconfig:
    kconfig.write('menu "Smart Paper -- Widgets"\n\n')

    for w in widgets_sorted:
        kconfig.write(f"    config WIDGET_{w.upper()}\n")
        kconfig.write(f'        bool "Enable {w.replace("_", " ").title()} Widget"\n')
        kconfig.write(f"        default y\n\n")

    kconfig.write("endmenu\n")

print(f"✅ Généré : {KCONFIG_PATH}")

##!/usr/bin/env python3
#import os
#import sys
#import glob

## Base = dossier où se trouve le script lui-même
#BASE_DIR = os.path.dirname(os.path.abspath(__file__))

## On remonte jusqu’au dossier du composant
#COMPONENT_DIR = os.path.abspath(os.path.join(BASE_DIR, ".."))

## Dossier contenant les fichiers de widgets
#WIDGET_DIR = os.path.join(COMPONENT_DIR, "widget")

## Dossier contenant les templates (adapté à ton arborescence)
#TEMPLATE_DIR = os.path.abspath(os.path.join(COMPONENT_DIR, "../../littlefs/template"))

## Dossier de sortie
#OUTPUT_DIR = COMPONENT_DIR

## Fichiers de sortie
#HEADER_PATH = os.path.join(OUTPUT_DIR, "include", "widget_autogen.h")
#SOURCE_PATH = os.path.join(OUTPUT_DIR, "widget_autogen.c")
#KCONFIG_PATH = os.path.join(OUTPUT_DIR, "Kconfig.widgets")


#print("=== DEBUG PATHS ===")
#print("Current working directory :", os.getcwd())
#print("Script file location      :", os.path.abspath(__file__))
#print("BASE_DIR                  :", BASE_DIR)
#print("COMPONENT_DIR             :", COMPONENT_DIR)
#print("WIDGET_DIR                :", WIDGET_DIR)
#print("OUTPUT_DIR                :", OUTPUT_DIR)
#print("====================\n")

## En-têtes communs
#HEADER_TOP = """#ifndef WIDGET_AUTOGEN_H
##define WIDGET_AUTOGEN_H

#"""

#SOURCE_TOP = """#include "widget.h"
##include "filesystem_interface.h"

#widget_t widget_info_list[WIDGET_COUNT];
#uint8_t size_widget_info_list;
#"""

#INIT_TOP = """
#/* Initializes the widget information list with predefined widgets */
#void init_widget_list(void)
#{
#    uint8_t index = 0;
#    mount_lfs();
#"""

#INIT_BOTTOM = """
#    unmount_lfs();
#    for (uint8_t i = index; i < WIDGET_COUNT; i++) {
#        widget_info_list[i] = (widget_t){0};
#    }

#    size_widget_info_list = index;
#}
#"""

## Découvre tous les widgets disponibles
#widgets = sorted([
#    os.path.splitext(os.path.basename(f))[0]
#    for f in glob.glob(os.path.join(WIDGET_DIR, "*.c"))
#])

#if not widgets:
#    raise RuntimeError("Aucun widget trouvé dans le dossier widget/")

#print(f"Widgets détectés : {', '.join(widgets)}")

## HEADER
#with open(HEADER_PATH, "w") as header:
#    header.write(HEADER_TOP)
#    header.write("// Includes des widgets activés\n")

#    for w in widgets:
#        macro = f"CONFIG_WIDGET_{w.upper()}"
#        header.write(f"#ifdef {macro}\n")
#        header.write(f'    #include "widget/{w}.h"\n')
#        header.write(f"#endif\n")

#    header.write("\n// Nombre total de widgets activés\n")
#    header.write("#define WIDGET_COUNT ( \\\n")

#    for i, w in enumerate(widgets):
#        macro = f"CONFIG_WIDGET_{w.upper()}"
#        if i < len(widgets) - 1:
#            # ligne intermédiaire : ajouter " + \\" à la fin
#            header.write(f"    ({macro} ? 1 : 0) + \\\n")
#        else:
#            # dernière ligne : aucun '+' avant le backslash
#            header.write(f"    ({macro} ? 1 : 0) \\\n")
#    header.write(")\n\n")

#    header.write("// Type des widgets\n")
#    header.write("typedef enum {\n")
#    for w in widgets:
#        macro = f"CONFIG_WIDGET_{w.upper()}"
#        header.write(f"#ifdef {macro}\n")
#        header.write(f"    WIDGET_TYPE_{w.upper()},\n")
#        header.write(f"#endif\n")
#    header.write("    WIDGET_TYPE_COUNT\n} widget_type_t;\n\n")

#    header.write("// Fonctions exposées\n")
#    header.write("#ifdef __cplusplus\n")
#    header.write("extern \"C\" {\n")
#    header.write("#endif\n\n")

#    header.write("    void        init_widget_list(void);\n")
#    header.write("    const char *get_widget_type_to_string(widget_type_t type);\n\n")

#    header.write("#ifdef __cplusplus\n")
#    header.write("} /*extern \"C\"*/\n")
#    header.write("#endif\n")
#    header.write("#endif")

#print(f"✅ Généré : {HEADER_PATH}")

## SOURCE
#with open(SOURCE_PATH, "w") as source:
#    source.write(SOURCE_TOP)

#    # get_widget_type_to_string()
#    source.write("\nconst char *get_widget_type_to_string(widget_type_t type)\n{\n")
#    source.write("    switch (type)\n    {\n")
#    for w in widgets:
#        macro = f"CONFIG_WIDGET_{w.upper()}"
#        source.write(f"#ifdef {macro}\n")
#        source.write(f'        case WIDGET_TYPE_{w.upper()}: return "{w}";\n')
#        source.write(f"#endif\n")
#    source.write('        default: return "Unknown Widget";\n')
#    source.write("    }\n}\n")

#    # init_widget_list()
#    source.write(INIT_TOP)

#    for w in widgets:
#        macro = f"CONFIG_WIDGET_{w.upper()}"
#        struct_name = f"widget_{w}"
#        filepath_macro = f"{w.upper()}_FILE_PATH"

#        source.write(f"\n#ifdef {macro}\n")
#        source.write(f"    widget_info_list[index] = (widget_t){{\n")
#        source.write(f"        .type = WIDGET_TYPE_{w.upper()},\n")
#        source.write(f"        .lv_obj = NULL,\n")
#        source.write(f"        .child = NULL,\n")
#        source.write(f"        .draw_function = {struct_name}_draw,\n")
#        source.write(f"        .erase_function = {struct_name}_erase,\n")
#        source.write(f"        .update_function = {struct_name}_update,\n")
#        source.write(f"        .update_data_function = {struct_name}_update_data,\n")
#        source.write(f"        .update_data_timestamp = 0,\n")
#        source.write(f"        .config = NULL\n")
#        source.write(f"    }};\n")
#        source.write(f"    init_widget_from_template(&widget_info_list[index++], {filepath_macro});\n")
#        source.write(f"#endif\n")

#    source.write(INIT_BOTTOM)

#print(f"✅ Généré : {SOURCE_PATH}")


## KCONFIG
#with open(KCONFIG_PATH, "w") as kconfig:
#    kconfig.write('menu "Smart Paper -- Widgets"\n\n')

#    for w in widgets:
#        kconfig.write(f"    config WIDGET_{w.upper()}\n")
#        kconfig.write(f'        bool "Enable {w.replace("_", " ").title()} Widget"\n')
#        kconfig.write(f"        default y\n\n")

#    kconfig.write("endmenu\n")

#print(f"✅ Généré : {KCONFIG_PATH}")
