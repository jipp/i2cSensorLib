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
  float get(uint8_t Measurement) override;

private:
  uint32_t memory;
};

#endif
