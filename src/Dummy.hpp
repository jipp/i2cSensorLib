#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <Arduino.h>
#include <Sensor.hpp>

class Dummy : public Sensor
{
public:
  Dummy();
  void begin() override;
  void getValues() override;
  float get(uint8_t Measurement) override;

private:
  float temperature;
  float pressure;
  float humidity;
  float getHumidity(void);
  float getTemperature(void);
  float getPressure(void);
};

#endif