#ifndef memory_h
#define memory_h

#include <Arduino.h>
#include <Sensor.h>

class Memory : public Sensor
{
public:
  Memory();
  void begin();
  void getValues();
  float get(uint8_t Measurement);

private:
  uint32_t memory;
};

#endif
