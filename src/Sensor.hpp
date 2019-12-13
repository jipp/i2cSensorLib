#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>

#include "Measurement.hpp"

class Sensor
{
public:
  uint8_t sensorAddress = 0x00;
  uint8_t sensorIDRegister = 0x00;
  uint8_t sensorID = 0x00;
  bool isAvailable = false;
  const uint8_t MSB4 = 4;
  const uint8_t MSB8 = 8;
  const uint8_t Bit1 = 0b00000001;
  const uint8_t Bit2 = 0b00000010;
  const uint8_t Bit3 = 0b00000100;
  const uint8_t Bit4 = 0b00001000;
  const uint8_t Mask3 = 0b00000111;
  const uint8_t Mask15 = 0b00001111;
  virtual void begin() = 0;
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
