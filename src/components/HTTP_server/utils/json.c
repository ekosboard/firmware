#include "HTTP_server.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"
#include <stdbool.h>


/* Retrieves a JSON object item by key from the JSON structure */
/* @Parameters: */
/*     - json: Pointer to the JSON structure to search. */
/*     - key: The key for the JSON object item. */
/*     - item: Pointer to store the JSON object item retrieved. */
/* @Return: */
/*     - ESP_OK: Object item found and is a valid JSON object. */
/*     - ESP_FAIL: Item not found or is not an object. */
esp_err_t get_json_object_item(cJSON *json, const char *key, cJSON **item) 
{
    *item = cJSON_GetObjectItem(json, key);
    if (*item && cJSON_IsObject(*item)) 
    {
        return ESP_OK;
    }
    return ESP_FAIL;
}

/* Retrieves a JSON string item by key from the JSON structure */
/* @Parameters: */
/*     - json: Pointer to the JSON structure to search. */
/*     - key: The key for the JSON string item. */
/*     - item: Pointer to store the JSON item structure retrieved. */
/*     - string_value: Pointer to store the string value of the item if found. */
/* @Return: */
/*     - ESP_OK: String item found and value retrieved. */
/*     - ESP_FAIL: Item not found or is not a string. */
esp_err_t get_json_string_item(cJSON *json, const char *key, cJSON **item, const char **string_value)
{
    *item = cJSON_GetObjectItem(json, key);
    if (*item)
    {
        if (cJSON_IsString(*item) && (*item)->valuestring)
        {
            *string_value = (*item)->valuestring;
            return ESP_OK;
        }
    }
    return ESP_FAIL;
}

/* Retrieves a JSON number item by key from the JSON structure */
/* @Parameters: */
/*     - json: Pointer to the JSON structure to search. */
/*     - key: The key for the JSON number item. */
/*     - item: Pointer to store the JSON item structure retrieved. */
/*     - number_value: Pointer to store the integer value of the item if found. */
/* @Return: */
/*     - ESP_OK: Number item found and value retrieved. */
/*     - ESP_FAIL: Item not found or is not a number. */
esp_err_t get_json_number_item(cJSON *json, const char *key, cJSON **item, int *number_value)
{
    *item = cJSON_GetObjectItem(json, key);
    if (*item)
    {
        if (cJSON_IsNumber(*item))
        {
            *number_value = (*item)->valueint;
            return ESP_OK;
        }
    }
    return ESP_FAIL;
}
