#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class Memory : public Sensor
{
public:
  Memory();
  bool begin() override;
  bool checkMeasurementAvailability() override;
  bool readMeasurement() override;
  float getMeasurement(Measurement measurement) override;

private:
  uint32_t memory = 0;
};

#endif
