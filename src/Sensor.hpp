#ifndef SENSOR_HPP
#define SENSOR_HPP

// (jipp) add set method for mode selection

#include <Arduino.h>
#include <Wire.h>

#include "Measurement.hpp"

class Sensor
{
public:
  bool isAvailable = false;
  virtual void begin() = 0;
  virtual bool isReady() = 0;
  virtual void getValues() = 0;
  virtual float get(Measurement measurement) = 0;
  bool checkSensorAvailability(uint8_t sensorAddress);
  bool checkSensorAvailability(uint8_t sensorAddress, uint8_t sensorIDRegister, uint8_t value);
  void writeRegister8(uint8_t sensorAddress, uint8_t registerAddress);
  void writeRegister8(uint8_t sensorAddress, uint8_t registerAddress, uint8_t registerValue);
  void writeRegister16(uint8_t sensorAddress, uint16_t registerAddress);
  uint8_t readRegister8(uint8_t sensorAddress);
  uint8_t readRegister8(uint8_t sensorAddress, uint8_t registerAddress);
  uint16_t readRegister16(uint8_t sensorAddress);
  uint16_t readRegister16(uint8_t sensorAddress, uint8_t registerAddress);
  uint32_t readRegister24(uint8_t sensorAddress, uint8_t registerAddress);
};

#endif
