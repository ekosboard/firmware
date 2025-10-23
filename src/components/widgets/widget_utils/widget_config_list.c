#include "widget_config_list.h"
#include <stdlib.h>
#include <string.h>

widget_config_t *widget_config_list_create_node(widget_config_t *head, const char *key, const char *value)
{
    widget_config_t *new_node = malloc(sizeof(widget_config_t));
    if (new_node == NULL)
        return NULL;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = head;
    return new_node;
}

void widget_config_list_free(widget_config_t *head)
{
    widget_config_t *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

const char *widget_config_list_get_value(widget_config_t *head, const char *key)
{
    while (head != NULL)
    {
        if (strcmp(head->key, key) == 0)
            return head->value;
        head = head->next;
    }
    return NULL;
}

widget_config_t *widget_config_list_find(widget_config_t *head, const char *key)
{
    while (head)
    {
        if (strcmp(head->key, key) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

