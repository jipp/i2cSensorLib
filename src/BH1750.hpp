#ifndef BH1750_HPP
#define BH1750_HPP

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class BH1750_Instruction
{
public:
  enum Opecode
  {
    Power_Down = 0b00000000,                      // No active state.
    Power_On = 0b00000001,                        // Waiting for measurement command.
    Reset = 0b00000111,                           // Reset Data register value. Reset command is not acceptable in Power Down mode.
    Continuously_H_Resolution_Mode = 0b00010000,  // Start measurement at 1lx resolution. Measurement Time is typically 120ms.
    Continuously_H_Resolution_Mode2 = 0b00010001, // Start measurement at 0.5lx resolution. Measurement Time is typically 120ms.
    Continuously_L_Resolution_Mode = 0b00010011,  // Start measurement at 4lx resolution. Measurement Time is typically 16ms.
    One_Time_H_Resolution_Mode = 0b00100000,      // Start measurement at 1lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    One_Time_H_Resolution_Mode2 = 0b00100001,     // Start measurement at 0.5lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    One_Time_L_Resolution_Mode = 0b00100011       // Start measurement at 4lx resolution. Measurement Time is typically 16ms. It is automatically set to Power Down mode after measurement.
  };
};

class BH1750_Measurement_Mode
{
public:
  enum Measurement_Time
  {
    H_Resolution_Mode = 120,
    H_Resolution_Mode2 = 120,
    L_Resolution_Mode = 16
  };
};

class BH1750 : public Sensor
{
public:
  BH1750();
  explicit BH1750(uint8_t address);
  void begin() override;
  bool isReady() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  const uint8_t defaultSensorAddress = 0x23;
  uint8_t sensorAddress = defaultSensorAddress;
  uint16_t illuminance = 0;
  const BH1750_Instruction::Opecode sensorMode = BH1750_Instruction::Continuously_H_Resolution_Mode;
  void wait(BH1750_Instruction::Opecode instruction);
};

#endif
