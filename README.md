[![Build Status](https://travis-ci.org/jipp/i2cSensorLib.svg?branch=master)](https://travis-ci.org/jipp/i2cSensorLib)

# i2cSensorLib
The library has the goal to provide the same command syntax for different i2c connected sensors. It can be used by Arduino IDE or PlatformIO.

## supported architectures
 * esp8266
 * esp32
 * avr

## supported sensors (and compatible)
- [X] BH1750 (digital ambient light intensity sensor)
- [X] BME280 (digital barometric pressure, temperature and humidity sensor)
- [X] BMP180 (digital barometric pressure and temperature sensor)
- [X] SHT3X (digital humidity and temperature sensor)
- [X] dummy (simulate values for light intensity, temperature, humidity and presure)
- [X] memory (display free heap of esp8266/esp32)
- [ ] CCS811 (digital gas sensor for monitoring indoor air quality)
- [ ] tof sensor (discance sensor)

## needed libraries
 * Wire.h