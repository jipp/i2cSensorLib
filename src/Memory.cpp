#include "Memory.hpp"

Memory::Memory() = default;

void Memory::begin()
{
#if defined(ESP32)
    isAvailable = true;
#elif defined(ESP8266)
    isAvailable = true;
#else
    isAvailable = false;
#endif
}

bool Memory::isReady()
{
  return true;
}

void Memory::getValues()
{
#if defined(ESP32)
    memory = ESP.getFreeHeap();
#elif defined(ESP8266)
    memory = ESP.getFreeHeap();
#else
    memory = 0;
#endif
}

float Memory::get(Measurement measurement)
{
    switch (measurement)
    {
    case Measurement::MEMORY:
        return static_cast<float>(memory);
    default:
        return 0.0;
    }
}
