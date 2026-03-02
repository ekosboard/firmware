file(GLOB WIDGET_SOURCES "widget/*.c")
file(GLOB WIDGET_HEADERS "include/widget/*.h")

idf_component_register(
    SRCS
        ${WIDGET_SOURCES}
        "widget_autogen.c"
        "widget_utils/widget_json.c"
        "widget_utils/widget_list.c"
        "widget_utils/widget_list_json.c"
        "widget_utils/widget_template_loader.c"
        "widget_utils/widget_config_list.c"
        "widget_utils/widget_template_interval.c"

    INCLUDE_DIRS
        "include"

    REQUIRES
        UI
        lvgl
        filesystem_interface
        json
        screen_manager
)

# --------------------------------------------------------------------
# Génération automatique des fichiers widget_autogen.* et Kconfig.widgets
# --------------------------------------------------------------------
set(GEN_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/scripts/gen_widgets.py)
set(GEN_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/widget_autogen.h)
set(GEN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/widget_autogen.c)
set(KCONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Kconfig.widgets)


# Commande de génération
add_custom_command(
    OUTPUT ${GEN_SOURCE} ${GEN_HEADER} ${KCONFIG_FILE}
    COMMAND ${PYTHON_EXECUTABLE} ${GEN_SCRIPT}
    DEPENDS ${WIDGET_SOURCES} ${WIDGET_HEADERS} ${GEN_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Génération automatique des fichiers widgets"
)

# Cible phony pour forcer la vérification à chaque build
# (Le script vérifiera lui-même s'il doit régénérer)
add_custom_target(force-gen-widgets ALL
    DEPENDS ${GEN_SOURCE} ${GEN_HEADER} ${KCONFIG_FILE}
)

# Dépendance du composant sur cette cible
add_dependencies(${COMPONENT_LIB} force-gen-widgets)
