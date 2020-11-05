#ifndef BMP180_HPP
#define BMP180_HPP

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class BME180_Mode
{
public:
  enum OSS
  {
    ULTRA_LOW_POWER = 0,      // 4.5ms
    STANDARD = 1,             // 7.5ms
    HIGH_RESOLUTION = 2,      // 13.5ms
    ULTRA_HIGH_RESOLUTION = 3 // 25.5ms
  };
};

class BMP180_Register
{
public:
  enum Value
  {
    chip_id = 0xD0, // 0x55 fixed
    soft = 0xE0,    // 0xB6 soft reset: 0xB6
    ctrl_meas = 0xF4,
    out_msb = 0xF6,
    out_lsb = 0xF7,
    out_xlsb = 0xF8
  };
};

class BMP180_RegisterValue
{
public:
  enum Measurement
  {
    temperature = 0x2E,
    OSS0 = 0x34,
    OSS1 = 0x74,
    OSS2 = 0xB4,
    OSS3 = 0xF4
  };
};

class BME180_Calibration
{
public:
  enum Coefficient
  {
    REGISTER_AC1 = 0xAA,
    REGISTER_AC2 = 0xAC,
    REGISTER_AC3 = 0xAE,
    REGISTER_AC4 = 0xB0,
    REGISTER_AC5 = 0xB2,
    REGISTER_AC6 = 0xB4,
    REGISTER_B1 = 0xB6,
    REGISTER_B2 = 0xB8,
    REGISTER_MB = 0xBA,
    REGISTER_MC = 0xBC,
    REGISTER_MD = 0xBE
  };
};

class BMP180 : public Sensor
{
public:
  BMP180();
  explicit BMP180(uint8_t address);
  bool begin() override;
  bool checkMeasurementAvailability() override;
  bool readMeasurement() override;
  float getMeasurement(Measurement measurement) override;

private:
  const uint8_t defaultSensorAddress = 0x77;
  uint8_t sensorAddress = defaultSensorAddress;
  const uint8_t id = 0x55;
  const BME180_Mode::OSS mode = BME180_Mode::ULTRA_LOW_POWER;
  float temperature = 0.0;
  float pressure = 0.0;
  struct CalibrationCoefficients
  {
    int16_t ac1 = 0;
    int16_t ac2 = 0;
    int16_t ac3 = 0;
    uint16_t ac4 = 0;
    uint16_t ac5 = 0;
    uint16_t ac6 = 0;
    int16_t b1 = 0;
    int16_t b2 = 0;
    int16_t mb = 0;
    int16_t mc = 0;
    int16_t md = 0;
  } calibrationCoefficients;
  int32_t UT = 0;
  int32_t UP = 0;
  int32_t B5 = 0;
  void conversionTime(BME180_Mode::OSS mode);
  uint16_t controlRegisterValue(BME180_Mode::OSS mode);
  void readCalibrationData();
  void readUncompensatedTemperature();
  void readUncompensatedPressure();
  float calculateTrueTemperature();
  float calculateTruePressure();
};

#endif
