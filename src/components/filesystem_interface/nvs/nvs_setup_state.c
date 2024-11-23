#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "nvs.h"

/* Writes the magic key to the NVS setup state */
/* @Parameters: None */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_magic_key()
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i32(nvs_handle, "magic_key", SETUP_MAGIC_KEY);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes the setup status to the NVS setup state */
/* @Parameters:
       - setup_status (int8_t): The setup status to store. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_setup_status(int8_t setup_status)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i8(nvs_handle, "setup_status", setup_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes the network status to the NVS setup state */
/* @Parameters:
       - network_status (int8_t): The network status to store. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_network_status(int8_t network_status)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i8(nvs_handle, "network_status", network_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes the screen ID to the NVS setup state */
/* @Parameters:
       - screen_id (int8_t): The screen ID to store. */
/* @Return: */
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_screen_id(int8_t screen_id)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i8(nvs_handle, "screen_id", screen_id);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes the timestamp to the NVS setup state */
/* @Parameters:
       - timestamp (int64_t): The timestamp to store. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_timestamp(int64_t timestamp)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i64(nvs_handle, "timestamp", timestamp);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes the timezone to the NVS setup state */
/* @Parameters:
       - timezone (char*): The timezone string to store. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_timezone(char *timezone)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_str(nvs_handle, "timezone", timezone);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Writes all setup state values to NVS */
/* @Parameters: 
       - setup_state (setup_state_t*): Pointer to a structure containing the setup state values. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
esp_err_t nvs_setup_state_write_all(setup_state_t *setup_state)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("setup_state", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_set_i8(nvs_handle, "setup_status", setup_state->setup_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_set_i8(nvs_handle, "network_status", setup_state->network_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_set_i8(nvs_handle, "screen_id", setup_state->screen_id);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_set_i64(nvs_handle, "timestamp", setup_state->timestamp);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_set_str(nvs_handle, "timezone", setup_state->timezone);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_commit(nvs_handle);

cleanup:
    nvs_close(nvs_handle);
    return ret;
}

/* Reads the setup status from the NVS setup state */
/* @Parameters: None */
/* @Return: */ 
/*     - The setup status, or -1 if the value could not be read. */
int8_t nvs_setup_state_read_setup_status()
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;
    int8_t setup_status;

    ret = nvs_open("setup_state", NVS_READONLY, &nvs_handle);
    if (ret != ESP_OK)
        return -1;

    ret = nvs_get_i8(nvs_handle, "setup_status", &setup_status);
    if (ret != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return setup_status;
}

/* Reads the network status from the NVS setup state */
/* @Parameters: None */
/* @Return: */ 
/*     - The network status, or -1 if the value could not be read. */
int8_t nvs_setup_state_read_network_status()
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;
    int8_t network_status;

    ret = nvs_open("setup_state", NVS_READONLY, &nvs_handle);
    if (ret != ESP_OK)
        return -1;

    ret = nvs_get_i8(nvs_handle, "network_status", &network_status);
    if (ret != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return network_status;
}


/* Reads the screen ID from the NVS setup state */
/* @Parameters: None */
/* @Return: */ 
/*     - The screen ID, or -1 if the value could not be read. */
int8_t nvs_setup_state_read_screen_id()
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;
    int8_t screen_id;

    ret = nvs_open("setup_state", NVS_READONLY, &nvs_handle);
    if (ret != ESP_OK)
        return -1;

    ret = nvs_get_i8(nvs_handle, "screen_id", &screen_id);
    if (ret != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return screen_id;
}

/* Reads the timestamp from the NVS setup state */
/* @Parameters: None */
/* @Return: */
/*     - The timestamp, or -1 if the value could not be read. */
int64_t nvs_setup_state_read_timestamp()
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;
    int64_t timestamp;

    ret = nvs_open("setup_state", NVS_READONLY, &nvs_handle);
    if (ret != ESP_OK)
        return -1;

    ret = nvs_get_i64(nvs_handle, "timestamp", &timestamp);
    if (ret != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return timestamp;
}

/* Reads all setup state values from NVS */
/* @Parameters:
       - setup_state (setup_state_t*): Pointer to a structure where the values will be stored. */
/* @Return: */ 
/*     - ESP_OK on success, or an error code on failure */
/* @Details: */ 
/*    Opens the NVS namespace `setup_state`, retrieves all fields from corresponding */
/*    keys, and populates the `setup_state` structure. If the magic key is not found or does */
/*    not match `SETUP_MAGIC_KEY`, the function returns ESP_ERR_NOT_FOUND. */
esp_err_t nvs_setup_state_read_all(setup_state_t *setup_state)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;

    ret = nvs_open("setup_state", NVS_READONLY, &nvs_handle);
    if (ret != ESP_OK)
        return ret;

    ret = nvs_get_i32(nvs_handle, "magic_key", &setup_state->magic_key);
    if (ret == ESP_ERR_NVS_NOT_FOUND || setup_state->magic_key != SETUP_MAGIC_KEY)
    {
        ret = ESP_ERR_NOT_FOUND;
        goto cleanup;
    }

    ret = nvs_get_i8(nvs_handle, "setup_status", &setup_state->setup_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_get_i8(nvs_handle, "network_status", &setup_state->network_status);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_get_i8(nvs_handle, "screen_id", &setup_state->screen_id);
    if (ret != ESP_OK)
        goto cleanup;

    ret = nvs_get_i64(nvs_handle, "timestamp", &setup_state->timestamp);
    if (ret != ESP_OK)
        goto cleanup;

    size_t timezone_len = sizeof(setup_state->timezone);
    ret = nvs_get_str(nvs_handle, "timezone", setup_state->timezone, &timezone_len);
    if (ret != ESP_OK)
        goto cleanup;

cleanup:
    nvs_close(nvs_handle);
    return ret;
}
