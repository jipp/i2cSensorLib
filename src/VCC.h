#ifndef vcc_h
#define vcc_h

#include <Arduino.h>
#include <Sensor.h>

class VCC : public Sensor {
public:
  VCC();
  void begin();
  void getValues();
  float get(uint8_t Measurement);

private:
  float voltage;
};

#endif
