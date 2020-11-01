#include <VCC.hpp>

VCC::VCC() = default;

bool VCC::begin()
{
#if defined(ESP8266)
  isSensorAvailable = true;
#else
  isSensorAvailable = false;
#endif

  return isSensorAvailable;
}

bool VCC::checkMeasurementAvailability()
{
  if (isSensorAvailable)
  {
    isMeasurementAvailable = true;
  }
  
  return isMeasurementAvailable;
}

void VCC::readMeasurement()
{
#if defined(ESP8266)
  voltage = static_cast<float>(ESP.getVcc());
#else
  voltage = NAN;
#endif
}

float VCC::getMeasurement(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::VOLTAGE:
    return voltage;
  default:
    return NAN;
  }
}
