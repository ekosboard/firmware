#ifndef BATTERY_ADC_H
#define BATTERY_ADC_H

#include "data_provider.h"

#define BATTERY_ADC_UNIT        ADC_UNIT_1
#define BATTERY_ADC_CHANNEL     ADC_CHANNEL_0       // GPIO1
#define BATTERY_ADC_ATTEN       ADC_ATTEN_DB_2_5    // Range 0–1.25V

// Voltage divider : 680kΩ / 150kΩ → ratio = 150 / (680 + 150)
#define BATTERY_DIVIDER_RATIO   (150.0f / (680.0f + 150.0f))   // ≈ 0.1807

// LiPo 1S
#define BATTERY_V_MIN           3.0f    // Empty voltage (0%)
#define BATTERY_V_MAX           4.2f    // Full voltage (100%)

// Number of averaged ADC readings to reduce noise
#define BATTERY_ADC_SAMPLES     8

// Cache TTL
#define BATTERY_CACHE_TTL_MS    (30 * 1000)   // 30 seconds

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Return the battery ADC data provider instance.
     *        To be registered via provider_register() in provider_manager_init().
     *        Do not call directly from a widget - use provider_get("battery") instead.
     *
     * Exposed keys:
     *   "battery_pct"     (float)  Charge percentage (0.0 – 100.0)
     *   "battery_voltage" (float)  Measured battery voltage in Volts (e.g. 3.85)
     *
     * Hardware:
     *   GPIO1 / ADC1_CH0
     *   Voltage divider: 680kΩ (series BAT+) / 150kΩ (to GND), ratio ≈ 0.1807
     *   LiPo 1S: 3.0V (empty) → 4.2V (full)
     *
     * @return Pointer to the static data_provider_t for the battery.
     */
    data_provider_t *battery_adc_get_provider(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BATTERY_ADC_H */
