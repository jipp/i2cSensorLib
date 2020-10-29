#ifndef VCC_HPP
#define VCC_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class VCC : public Sensor
{
public:
  VCC();
  void begin() override;
  bool isReady() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  float voltage = 0.0;
};

#endif
