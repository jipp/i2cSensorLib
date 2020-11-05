#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class Dummy : public Sensor
{
public:
  Dummy();
  bool begin() override;
  bool checkMeasurementAvailability() override;
  bool readMeasurement() override;
  float getMeasurement(Measurement measurement) override;

private:
  float temperature = 0.0;
  float pressure = 0.0;
  float humidity = 0.0;
  float illuminance = 0.0;
  float co2 = 0.0;
};

#endif