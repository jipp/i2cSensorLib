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

bool VCC::isReady()
{
  return true;
}

void VCC::getValues()
{
#if defined(ESP8266)
  voltage = static_cast<float>(ESP.getVcc());
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
