[![Build Status](https://travis-ci.org/jipp/i2cSensorLib.svg?branch=master)](https://travis-ci.org/jipp/i2cSensorLib)

# i2cSensorLib
The library has the goal to provide the same command syntax for different i2c connected sensors. It can be used by Arduino IDE or PlatformIO.

## supported architectures
 * esp8266
 * esp32
 * avr

## supported sensors (and compatible)
- [X] BH1750
- [X] BME280
- [X] BMP180
- [ ] CCS811
- [X] SHT3X
- [X] dummy (simulate values for temperature, humidity and pressure)

## needed libraries
 * Wire.h
