#ifndef dummy_h
#define dummy_h

#include <Arduino.h>
#include <Sensor.h>

class Dummy : public Sensor
{
public:
  Dummy();
  void begin();
  void getValues();
  float get(uint8_t Measurement);

private:
  float temperature;
  float pressure;
  float humidity;
  float getHumidity(void);
  float getTemperature(void);
  float getPressure(void);
};

#endif