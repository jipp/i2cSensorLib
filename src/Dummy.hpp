#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class Dummy : public Sensor
{
public:
  Dummy();
  void begin() override;
  bool isReady() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  float temperature = 0.0;
  float pressure = 0.0;
  float humidity = 0.0;
  float illuminance = 0.0;
};

#endif