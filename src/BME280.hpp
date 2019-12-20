#ifndef BME280_HPP
#define BME280_HPP

// TODO bulk read for register values

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class BME280_Register
{
public:
  enum Value
  {
    id = 0xD0,        // The "id" register contains the chip identification number chip_id[7:0], which is 0x60. This number can be read as soon as the device finished the power-on-reset.
    reset = 0xE0,     // The "reset" register contains the soft reset word reset[7:0]. If the value 0xB6 is written to the register, the device is reset using the complete power-on-reset procedure. Writing other values than 0xB6 has no effect. The readout value is always 0x00.
    ctrl_hum = 0xF2,  // The "ctrl_hum" register sets the humidity data acquisition options of the device. Changes to this register only become effective after a write operation to "ctrl_meas".
    status = 0xF3,    // The "status" register contains two bits which indicate the status of the device. Bit 3 measuring[0]. Bit 0 im_update[0].
    ctrl_meas = 0xF4, // The "ctrl_meas" register sets the pressure and temperature data acquisition options of the device. The register needs to be written after changing "ctrl_hum" for the changes to become effective.
    config = 0xF5,    // The "config" register sets the rate, filter and interface options of the device. Writes to the "config" register in normal mode may be ignored. In sleep mode writes are not ignored.
    press_msb = 0xF7, // The "press" register contains the raw pressure measurement output data up[19:0].
    press_lsb = 0xF8,
    press_xlsb = 0xF9,
    temp_msb = 0xFA, // The "temp" register contains the raw temperature measurement output data ut[19:0].
    temp_lsb = 0xFB,
    temp_xlsb = 0xFC,
    hum_msb = 0xFD,
    hum_lsb = 0xFE
  };
};

class BME280_Mode
{
public:
  enum Mode
  {
    Sleep_mode = 0b00,
    Forced_mode = 0b01,
    Normal_mode = 0b11
  };
};

class BME280_Oversampling
{
public:
  enum Value
  {
    oversampling_skipped = 0b000,
    oversampling_1 = 0b001,
    oversampling_2 = 0b010,
    oversampling_4 = 0b011,
    oversampling_8 = 0b100,
    oversampling_16 = 0b101
  };
};

class BME280_Filter
{
public:
  enum Filter_Coefficient
  {
    Filter_off = 0b000,
    Filter_2 = 0b001,
    Filter_4 = 0b010,
    Filter_8 = 0b011,
    Filter_16 = 0b100
  };
};

class BME280_Trimming
{
public:
  enum Register
  {
    dig_T1_LSB = 0x88,
    dig_T1_MSB = 0x89,
    dig_T2_LSB = 0x8A,
    dig_T2_MSB = 0x8B,
    dig_T3_LSB = 0x8C,
    dig_T3_MSB = 0x8D,
    dig_P1_LSB = 0x8E,
    dig_P1_MSB = 0x8F,
    dig_P2_LSB = 0x90,
    dig_P2_MSB = 0x91,
    dig_P3_LSB = 0x92,
    dig_P3_MSB = 0x93,
    dig_P4_LSB = 0x94,
    dig_P4_MSB = 0x95,
    dig_P5_LSB = 0x96,
    dig_P5_MSB = 0x97,
    dig_P6_LSB = 0x98,
    dig_P6_MSB = 0x99,
    dig_P7_LSB = 0x9A,
    dig_P7_MSB = 0x9B,
    dig_P8_LSB = 0x9C,
    dig_P8_MSB = 0x9D,
    dig_P9_LSB = 0x9E,
    dig_P9_MSB = 0x9F,
    dig_H1 = 0xA1,
    dig_H2_LSB = 0xE1,
    dig_H2_MSB = 0xE2,
    dig_H3 = 0xE3,
    dig_H4_MSB = 0xE4,
    dig_H4_LSB = 0xE5,
    dig_H5_LSB = 0xE5,
    dig_H5_MSB = 0xE6,
    dig_H6 = 0xE7
  };
};

class BME280_Operation
{
public:
  enum Mode
  {
    Weather_Monitoring,
    Humidity_Sensing,
    Indoor_Navigation,
    Gaming
  };
};

class BME280_t_sb
{
public:
  enum Settings
  {
    t_sb_0_5 = 0b000,
    t_sb_62_5 = 0b001,
    t_sb_125 = 0b010,
    t_sb_250 = 0b011,
    t_sb_500 = 0b100,
    t_sb_1000 = 0b101,
    t_sb_10 = 0b110,
    t_sb_20 = 0b111
  };
};

class BME280_Type
{
public:
  enum Type
  {
    BME280 = 0x60,
    BMP280_samples1 = 0x56,
    BMP280_samples2 = 0x57,
    BMP280 = 0x58
  };
};

class BME280 : public Sensor
{
public:
  BME280();
  explicit BME280(uint8_t address);
  void begin() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  const uint8_t defaultSensorAddress = 0x76;
  uint8_t sensorAddress = defaultSensorAddress;
  float temperature = 0.0;
  float pressure = 0.0;
  float humidity = 0.0;
  int32_t t_fine = 0;
  struct Trimming
  {
    uint16_t t1 = 0;
    int16_t t2 = 0;
    int16_t t3 = 0;
    uint16_t p1 = 0;
    int16_t p2 = 0;
    int16_t p3 = 0;
    int16_t p4 = 0;
    int16_t p5 = 0;
    int16_t p6 = 0;
    int16_t p7 = 0;
    int16_t p8 = 0;
    int16_t p9 = 0;
    uint8_t h1 = 0;
    int16_t h2 = 0;
    uint8_t h3 = 0;
    int16_t h4 = 0;
    int16_t h5 = 0;
    int8_t h6 = 0;
  } trimming;
  const BME280_Operation::Mode sensorMode = BME280_Operation::Weather_Monitoring;
  bool isMeasuring();
  void setParameter();
  void readCompensationData();
  void setStandby(uint8_t t_sb);
  void setFilter(uint8_t filter);
  void setTemperatureOversampling(uint8_t osrs_t);
  void setPressureOversampling(uint8_t osrs_p);
  void setHumidityOversampling(uint8_t osrs_h);
  void setMode(BME280_Mode::Mode mode);
  BME280_Mode::Mode getMode();
  float getHumidity();
  float getTemperature();
  float getPressure();
};

#endif
