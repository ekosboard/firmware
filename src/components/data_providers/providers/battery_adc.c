#include "providers/battery_adc.h"
#include "data_provider.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "PROVIDER_BATTERY";
// ─────────────────────────────────────────────────────────────────────────────
//  Buffer de données en PSRAM (BSS — zero-init, pas d'initialiseurs)
// ─────────────────────────────────────────────────────────────────────────────

static EXT_RAM_BSS_ATTR provider_data_t s_battery_data;

// ─────────────────────────────────────────────────────────────────────────────
//  État interne du provider
// ─────────────────────────────────────────────────────────────────────────────

static adc_oneshot_unit_handle_t s_adc_handle = NULL;

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers internes
// ─────────────────────────────────────────────────────────────────────────────

static float voltage_to_percent(float voltage)
{
    if (voltage <= BATTERY_V_MIN) return 0.0f;
    if (voltage >= BATTERY_V_MAX) return 100.0f;
    return ((voltage - BATTERY_V_MIN) / (BATTERY_V_MAX - BATTERY_V_MIN)) * 100.0f;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Fonctions du provider
// ─────────────────────────────────────────────────────────────────────────────

static esp_err_t battery_init(void)
{
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = BATTERY_ADC_UNIT,
    };
    esp_err_t err = adc_oneshot_new_unit(&unit_cfg, &s_adc_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "adc_oneshot_new_unit failed: 0x%x", err);
        return err;
    }

    adc_oneshot_chan_cfg_t chan_cfg = {
        .atten    = BATTERY_ADC_ATTEN,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    err = adc_oneshot_config_channel(s_adc_handle, BATTERY_ADC_CHANNEL, &chan_cfg);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "adc_oneshot_config_channel failed: 0x%x", err);
        adc_oneshot_del_unit(s_adc_handle);
        s_adc_handle = NULL;
        return err;
    }

    ESP_LOGI(TAG, "ADC init OK (unit=%d, ch=%d, atten=%d)",
            BATTERY_ADC_UNIT, BATTERY_ADC_CHANNEL, BATTERY_ADC_ATTEN);
    return ESP_OK;
}

static esp_err_t battery_read(provider_data_t *out)
{
    if (s_adc_handle == NULL)
    {
        out->status = PROVIDER_STATUS_ERROR_INIT;
        out->count  = 0;
        return ESP_FAIL;
    }

    int32_t raw_sum = 0;
    int     raw_val = 0;
    for (int i = 0; i < BATTERY_ADC_SAMPLES; i++)
    {
        esp_err_t err = adc_oneshot_read(s_adc_handle, BATTERY_ADC_CHANNEL, &raw_val);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "adc_oneshot_read failed: 0x%x", err);
            out->status = PROVIDER_STATUS_ERROR_READ;
            out->count  = 0;
            return err;
        }
        raw_sum += raw_val;
    }

    int32_t raw_avg = raw_sum / BATTERY_ADC_SAMPLES;

    // Conversion raw → tension ADC (plage DB_0 : 0–0.95V, 12 bits)
    float v_adc = (raw_avg / 4095.0f) * 0.95f;

    // Tension réelle batterie (inverser le pont diviseur)
    float v_bat = v_adc / BATTERY_DIVIDER_RATIO;

    float pct = voltage_to_percent(v_bat);

    ESP_LOGD(TAG, "raw=%ld | v_adc=%.4fV | v_bat=%.3fV | pct=%.1f%%",
            raw_avg, v_adc, v_bat, pct);

    out->count  = 2;
    out->status = PROVIDER_STATUS_OK;

    strncpy(out->values[0].key, "battery_pct", PROVIDER_NAME_MAX_LEN - 1);
    out->values[0].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[0].type  = PROVIDER_VAL_FLOAT;
    out->values[0].val.f = pct;

    strncpy(out->values[1].key, "battery_voltage", PROVIDER_NAME_MAX_LEN - 1);
    out->values[1].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[1].type  = PROVIDER_VAL_FLOAT;
    out->values[1].val.f = v_bat;

    return ESP_OK;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Struct de définition du provider — en DRAM interne (pas EXT_RAM_BSS_ATTR)
//
//  EXT_RAM_BSS_ATTR zero-initialise la section au boot, ce qui écraserait
//  tous les initialiseurs statiques (.name, .init, .read...) et laisserait
//  les pointeurs à NULL → crash dans strlen() au premier log.
//
//  Règle : EXT_RAM_BSS_ATTR uniquement pour les buffers sans initialiseurs
//  (ex: s_battery_data ci-dessus). Les structs avec pointeurs/valeurs
//  restent en DRAM interne (section .data).
// ─────────────────────────────────────────────────────────────────────────────

static data_provider_t s_battery_provider = {
    .name           = "battery",
    .state          = PROVIDER_STATUS_UNAVAILABLE,
    .cache_ttl_ms   = BATTERY_CACHE_TTL_MS,
    .last_read_ms   = 0,
    .cached_data    = &s_battery_data,
    .init           = battery_init,
    .read           = battery_read,
    .on_data        = NULL,
};

// ─────────────────────────────────────────────────────────────────────────────
//  Point d'entrée public
// ─────────────────────────────────────────────────────────────────────────────

data_provider_t *battery_adc_get_provider(void)
{
    return &s_battery_provider;
}
