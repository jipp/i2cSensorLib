#include <SCD30.hpp>

SCD30::SCD30() = default;

SCD30::SCD30(uint8_t address)
{
    sensorAddress = address;
}

bool SCD30::begin()
{
#ifdef ARDUINO_ARCH_ESP8266
    Wire.setClockStretchLimit(200000);
#endif

    isSensorAvailable = checkSensorAvailability(sensorAddress);

    if (isSensorAvailable)
    {
        
    }

    return isSensorAvailable;
}

bool SCD30::checkMeasurementAvailability()
{
    isMeasurementAvailable = true;

    return isMeasurementAvailable;
}

void SCD30::readMeasurement()
{
    co2 = 0.0;
}

float SCD30::getMeasurement(Measurement measurement)
{
    switch (measurement)
    {
    case Measurement::CO2:
        return co2;
    default:
        return NAN;
    }
}