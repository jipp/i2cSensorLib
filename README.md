# i2cSensorLib
The library has the goal to provide the same command syntax for different sensors. It can be used by Arduino IDE or PlatformIO.

## supported architectures
 * esp8266

## supported sensors (and compatible)
- [X] BH1750
- [X] BME280
- [X] BMP180
- [ ] CCS811
- [X] SHT3X

## needed libraries
 * Wire.h

## command syntax
 * include library: `#include <i2cSensorLib.h>`
 * prepare ADC mode on ESP8266: `ADC_MODE(ADC_VCC);`
 * instantiate variable: `<type> <variable> = <constructor>([i2c address]);`
 * check for availability and do compensation calculation: `<variable>.begin();`
 * get info about availability: `<variable>.isAvailable;`
 * measure values: `<variable>.getValues();`
 * get measured: `<variable>.get(Sensor::[VOLTAGE_MEASUREMENT|ILLUMINANCE_MEASUREMENT|TEMPERATURE_MEASUREMENT|HUMIDITY_MEASUREMENT|PRESSURE_MEASUREMENT]);`
