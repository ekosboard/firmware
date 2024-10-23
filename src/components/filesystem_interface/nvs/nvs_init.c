#include "filesystem_interface.h"

/* Initializes the Non-Volatile Storage (NVS) interface. */ 
/* It handles any necessary erasing of NVS pages if there are no free pages or if a new version of NVS is found. */
/* @Returns: */
/* - ESP_OK on success, or an error code on failure. */
esp_err_t nvs_init_interface()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    return ret;
}
