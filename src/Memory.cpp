#include "Memory.hpp"

Memory::Memory() = default;

bool Memory::begin()
{
#if defined(ESP32)
    isSensorAvailable = true;
#elif defined(ESP8266)
    isSensorAvailable = true;
#else
    isSensorAvailable = false;
#endif

    return isSensorAvailable;
}

bool Memory::checkMeasurementAvailability()
{
    isMeasurementAvailable = false;

    if (isSensorAvailable)
    {
        isMeasurementAvailable = true;
    }

    return isMeasurementAvailable;
}

bool Memory::readMeasurement()
{
    if (checkMeasurementAvailability())
    {
#if defined(ESP32)
        memory = ESP.getFreeHeap();

        return true;
#elif defined(ESP8266)
        memory = ESP.getFreeHeap();

        return true;
#else
        memory = 0;

        return false;
#endif
    }

    return false;
}

float Memory::getMeasurement(Measurement measurement)
{
    switch (measurement)
    {
    case Measurement::MEMORY:
        return static_cast<float>(memory);
    default:
        return 0.0;
    }
}
