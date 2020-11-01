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
    if (isSensorAvailable)
    {
        isMeasurementAvailable = true;
    }

    return isMeasurementAvailable;
}

void Memory::readMeasurement()
{
#if defined(ESP32)
    memory = ESP.getFreeHeap();
#elif defined(ESP8266)
    memory = ESP.getFreeHeap();
#else
    memory = 0;
#endif
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
