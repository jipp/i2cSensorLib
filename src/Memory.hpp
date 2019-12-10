#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class Memory : public Sensor
{
public:
  Memory();
  void begin() override;
  void getValues() override;
  float get(Measurement measurement) override;

private:
  uint32_t memory = 0;
};

#endif
