#include <VCC.hpp>

VCC::VCC() = default;

void VCC::begin()
{
#if defined(ESP8266)
  isAvailable = true;
#else
  isAvailable = false;
#endif
}

void VCC::getValues()
{
  const float norm = 1024.0;
#if defined(ESP8266)
  voltage = static_cast<float>(ESP.getVcc()) / norm;
#else
  voltage = NAN;
#endif
}

float VCC::get(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::VOLTAGE:
    return voltage;
  default:
    return NAN;
  }
}
