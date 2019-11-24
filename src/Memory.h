#ifndef memory_h
#define memory_h

#include <Arduino.h>
#include <Sensor.h>

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
