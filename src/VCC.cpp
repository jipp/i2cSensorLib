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
  isMeasurementAvailable = false;

  if (isSensorAvailable)
  {
    isMeasurementAvailable = true;
  }

  return isMeasurementAvailable;
}

bool VCC::readMeasurement()
{
  if (checkMeasurementAvailability())
  {
#if defined(ESP8266)
    voltage = static_cast<float>(ESP.getVcc());

    return true;
#else
    voltage = NAN;

    return false;
#endif
  }

  return false;
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
