#include "device_info.h"
#include "esp_err.h"
#include "main.h"


/* Initializes the system state, including storage and default configuration. */
/* @Parameters: */
/*    - None */
/* @Behavior: */
/*    - Initializes the default event loop. */
/*    - Initializes the NVS storage interface. */
/*    - Mounts and unmounts the LFS partition, ensuring widget template indexing. */
/*    - Reads the setup state from NVS; if not found, writes default values. */
/* @Return: */
/*    - ESP_OK on success. */
/*    - An error code if initialization fails. */
esp_err_t setup_persistent_state(void)
{
    setup_state_t setup_state;
    esp_err_t ret = ESP_OK;

    ret = esp_event_loop_create_default();
    if (ret != ESP_OK)
        return ret;

    ret = nvs_init_interface();
    if (ret != ESP_OK)
        return ret;

    ret = mount_lfs();
    if (ret != ESP_OK)
        return ret;

    update_file_index_json(WIDGET_TEMPLATE_INDEX);

    ret = unmount_lfs();
    if (ret != ESP_OK)
        return ret;

    ret = nvs_setup_state_read_all(&setup_state);
    if (ret == ESP_ERR_NOT_FOUND || ret == ESP_ERR_NVS_NOT_FOUND)
    {
        setup_state.magic_key = SETUP_MAGIC_KEY;
        setup_state.setup_status = -1;
        setup_state.network_status = -1;
        setup_state.screen_id = 0;
        setup_state.timestamp = 0;
        memcpy(setup_state.timezone, "NA", 3);
        nvs_setup_state_write_all(&setup_state);
        nvs_setup_state_write_magic_key();
    }

    device_info_t device_info;
    device_info_load(&device_info);
    // Si serial encore vide -> générer automatiquement
    if (strcmp(device_info.serial, "UNINITIALIZED") == 0)
    {
        uint8_t mac[6];
        esp_read_mac(mac, ESP_MAC_WIFI_STA);
        snprintf(device_info.serial, sizeof(device_info.serial),
                 "S3-%02X%02X%02X%02X%02X%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

        device_info_save(&device_info);
    }
    return ESP_OK;
}
