#ifndef BME680_PROVIDER_H
#define BME680_PROVIDER_H

#include "data_provider.h"

// Cache TTL
#define BME680_CACHE_TTL_MS    (30 * 1000)   // 30 seconds

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Return the BME680 data provider instance.
     *        To be registered via provider_register() in provider_manager_init().
     *        Do not call directly from a widget — use provider_get("bme680") instead.
     *
     * Exposed keys:
     *   "temperature"    (float)  Temperature in degrees Celsius
     *   "humidity"       (float)  Relative humidity in percent (0.0 – 100.0)
     *   "pressure"       (float)  Atmospheric pressure in hPa
     *   "gas_resistance" (float)  Gas resistance in Ohms — proxy for air quality
     *                             Valid only when status has BME68X_GASM_VALID_MSK set.
     *
     * Hardware:
     *   I2C address: 0x76 (SDO → GND)
     *   Bus: I2C_NUM_0, SCL=GPIO14, SDA=GPIO21
     *   Bosch BME68x SensorAPI, forced mode, OSR x1, no filter
     *   Heater: CONFIG_PROVIDER_BME680_HEATER_TEMP °C / CONFIG_PROVIDER_BME680_HEATER_DUR ms
     *
     * @return Pointer to the static data_provider_t for the BME680.
     */
    data_provider_t *bme680_get_provider(void);

#ifdef __cplusplus
}
#endif

#endif /* BME680_PROVIDER_H */
