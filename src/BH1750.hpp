#ifndef BH1750_HPP
#define BH1750_HPP

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class BH1750 : public Sensor
{
public:
  BH1750();
  explicit BH1750(uint8_t address);
  void begin() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  const uint8_t defaultSensorAddress = 0x23;
  enum Mode
  {
    Power_Down = 0x00,                      // No active state.
    Power_On = 0x01,                        // Waiting for measurement command.
    Reset = 0x07,                           // Reset Data register value. Reset command is not acceptable in Power Down mode.
    Continuously_H_Resolution_Mode = 0x10,  // Start measurement at 1lx resolution. Measurement Time is typically 120ms.
    Continuously_H_Resolution_Mode2 = 0x11, // Start measurement at 0.5lx resolution. Measurement Time is typically 120ms.
    Continuously_L_Resolution_Mode = 0x13,  // Start measurement at 4lx resolution. Measurement Time is typically 16ms.
    One_Time_H_Resolution_Mode = 0x20,      // Start measurement at 1lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    One_Time_H_Resolution_Mode2 = 0x21,     // Start measurement at 0.5lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    One_Time_L_Resolution_Mode = 0x23       // Start measurement at 4lx resolution. Measurement Time is typically 16ms. It is automatically set to Power Down mode after measurement.
  };
  enum Wait
  {
    H_Resolution_Mode = 120,
    H_Resolution_Mode2 = 120,
    L_Resolution_Mode = 16
  };
  const Mode sensorMode = Continuously_H_Resolution_Mode;
  uint8_t sensorAddress = defaultSensorAddress;
  uint16_t illuminance = 0;
  void wait(Mode mode);
};

#endif
