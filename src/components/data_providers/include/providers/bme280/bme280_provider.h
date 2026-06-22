#ifndef BME280_PROVIDER_H
#define BME280_PROVIDER_H

#include "data_provider.h"

// Cache TTL
#define BME280_CACHE_TTL_MS    (30 * 1000)   // 30 seconds

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Return the BME280 data provider instance.
     *        To be registered via provider_register() in provider_manager_init().
     *        Do not call directly from a widget — use provider_get("bme280") instead.
     *
     * Exposed keys:
     *   "temperature"  (float)  Temperature in degrees Celsius
     *   "humidity"     (float)  Relative humidity in percent (0.0 – 100.0)
     *   "pressure"     (float)  Atmospheric pressure in hPa
     *
     * Hardware:
     *   I2C address: 0x76 (SDO → GND)
     *   Bus: I2C_NUM_0, SCL=GPIO14, SDA=GPIO21
     *   Bosch SensorAPI, forced mode, OSR x1, no filter
     *
     * @return Pointer to the static data_provider_t for the BME280.
     */
    data_provider_t *bme280_get_provider(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BME280_PROVIDER_H */
