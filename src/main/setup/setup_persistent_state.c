#include "device_info.h"
#include "esp_app_desc.h"
#include "esp_err.h"
#include "lwip/err.h"
#include "main.h"

static const char *TAG = "SETUP_PERSISTANT_STATE";
static esp_err_t sync_firmware_version(void);

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

    ret = sync_firmware_version();
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

        snprintf(device_info.device_name, sizeof(device_info.device_name),
                "EKOS-%02X%02X%02X%02X%02X%02X",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

        device_info_save(&device_info);
    }
    return ESP_OK;
}

static esp_err_t sync_firmware_version(void)
{
    const esp_app_desc_t *app_desc = esp_app_get_description();
    if (app_desc == NULL)
    {
        ESP_LOGE(TAG, "Failed to read app description");
        return ESP_FAIL;
    }

    device_info_t device_info;
    device_info_load(&device_info);

    /* Always overwrite — ensures version is correct after OTA */
    strncpy(device_info.firmware_version,app_desc->version,sizeof(device_info.firmware_version) - 1);
    device_info.firmware_version[sizeof(device_info.firmware_version) - 1] = '\0';

    esp_err_t ret = device_info_save(&device_info);
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "Failed to save firmware version to NVS: %s", esp_err_to_name(ret));
    else
        ESP_LOGI(TAG, "Firmware version synced: %s", device_info.firmware_version);

    return ret;
}

