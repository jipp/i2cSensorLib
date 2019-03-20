#include <Dummy.h>

Dummy::Dummy()
{
    randomSeed(analogRead(0));
}

void Dummy::begin()
{
    this->isAvailable = true;
}

void Dummy::getValues()
{
    this->temperature = this->getTemperature();
    this->pressure = this->getPressure();
    this->humidity = this->getHumidity();
}

float Dummy::get(uint8_t Measurement)
{
    switch (Measurement)
    {
    case TEMPERATURE_MEASUREMENT:
        return this->temperature;
    case PRESSURE_MEASUREMENT:
        return this->pressure;
    case HUMIDITY_MEASUREMENT:
        return this->humidity;
    default:
        return NAN;
    }
}

float Dummy::getHumidity(void)
{
    return random(0, 99);
}

float Dummy::getTemperature(void)
{
    return random(-2000, 5000) / 100.0;
}

float Dummy::getPressure(void)
{
    return random(850, 1100);
}