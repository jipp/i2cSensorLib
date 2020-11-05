#ifndef VCC_HPP
#define VCC_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class VCC : public Sensor
{
public:
  VCC();
  bool begin() override;
  bool checkMeasurementAvailability() override;
  bool readMeasurement() override;
  float getMeasurement(Measurement measurement) override;

private:
  float voltage = 0.0;
};

#endif
