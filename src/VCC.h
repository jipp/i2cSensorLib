#ifndef vcc_h
#define vcc_h

#include <Arduino.h>
#include <Sensor.h>

class VCC : public Sensor
{
public:
  VCC();
  void begin() override;
  void getValues() override;
  float get(uint8_t Measurement) override;

private:
  float voltage;
};

#endif
