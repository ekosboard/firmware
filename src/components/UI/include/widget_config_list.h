#ifndef WIDGET_CONFIG_LIST_H
#define WIDGET_CONFIG_LIST_H

typedef struct widget_config_s {
    char                    *key;
    char                    *value;
    struct widget_config_s  *next;
} widget_config_t;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Create and insert a new configuration node at the head of the list.
     *
     * @param head  Pointer to the current head of the list.
     * @param key   Configuration key (duplicated in memory).
     * @param value Configuration value (duplicated in memory).
     *
     * @return Pointer to the new node (new head of the list),
     *         or NULL if memory allocation fails.
     */
    widget_config_t     *widget_config_list_create_node(widget_config_t *head, const char *key, const char *value);

    /**
     * @brief Free the entire configuration list and all its contents.
     *
     * @param head Pointer to the head of the list (can be NULL).
     *
     * @note All keys and values duplicated with strdup() are freed.
     *       The list must not be accessed after this function is called.
     */
    void                widget_config_list_free(widget_config_t *head);

    /**
     * @brief Retrieve the value associated with a given configuration key.
     *
     * @param head Pointer to the head of the configuration list.
     * @param key  The key to search for.
     *
     * @return Pointer to the value string if found (do not modify or free),
     *         or NULL if the key is not present.
     */
    const char          *widget_config_list_get_value(widget_config_t *head, const char *key);

    /**
     * @brief Find the configuration node matching a given key.
     *
     * @param head Pointer to the head of the configuration list.
     * @param key  The key to search for.
     *
     * @return Pointer to the matching configuration node,
     *         or NULL if not found.
     */
    widget_config_t     *widget_config_list_find(widget_config_t *head, const char *key);

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif
