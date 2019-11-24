#include <Memory.hpp>

Memory::Memory()
{
}

void Memory::begin()
{
#if defined(ESP32)
    this->isAvailable = true;
#elif defined(ESP8266)
    this->isAvailable = true;
#else
    this->isAvailable = false;
#endif
}

void Memory::getValues()
{
#if defined(ESP32)
    this->memory = ESP.getFreeHeap();
#elif defined(ESP8266)
    this->memory = ESP.getFreeHeap();
#else
    this->memory = NAN;
#endif
}

float Memory::get(uint8_t Measurement)
{
    switch (Measurement)
    {
    case MEMORY_MEASUREMENT:
        return this->memory;
    default:
        return NAN;
    }
}
