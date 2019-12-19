#ifndef SHT3X_HPP
#define SHT3X_HPP

// TODO validate with sensor

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class SHT3X_Mode
{
public:
  enum Mode
  {
    H_REPEATABILITY_CLOCK_STRETCHING = 0x2C06, // 15ms
    M_REPEATABILITY_CLOCK_STRETCHING = 0x2C0D, // 6ms
    L_REPEATABILITY_CLOCK_STRETCHING = 0x2C10, // 6ms
    H_REPEATABILITY = 0x2400,                  // 15ms
    M_REPEATABILITY = 0x240B,                  // 6ms
    L_REPEATABILITY = 0x2416                   // 6ms
  };
};

class SHT3X_Register
{
public:
  enum Value
  {
    READ_OUT_OF_STATUS_REGISTER = 0xF32D,
    CLEAR_STATUS = 0x3041,
    BREAK = 0x3093,
    SOFT_RESET = 0x30A2,
    HEATER_ENABLE = 0x306D,
    HEATRER_DISABLED = 0x3066,
  };
};

class SHT3X : public Sensor
{
public:
  SHT3X();
  explicit SHT3X(uint8_t sensorAddress);
  void begin() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  const uint8_t defaultSensorAddress = 0x44;
  uint8_t sensorAddress = defaultSensorAddress;
  const SHT3X_Mode::Mode mode = SHT3X_Mode::H_REPEATABILITY_CLOCK_STRETCHING;
  float temperature = 0.0;
  float humidity = 0.0;
  void reset();
  void wait(SHT3X_Mode::Mode mode);
};

#endif
