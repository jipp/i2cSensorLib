#include <Dummy.hpp>

Dummy::Dummy()
{
    randomSeed(analogRead(0));
}

bool Dummy::begin()
{
    isSensorAvailable = true;

    return isSensorAvailable;
}

bool Dummy::checkMeasurementAvailability()
{
    isMeasurementAvailable = true;

    return isMeasurementAvailable;
}

void Dummy::readMeasurement()
{
    const int32_t temperatureLow = -2000;
    const int32_t temperatureHigh = 5000;
    const float temperatureScale = 100.0;
    const int32_t pressureLow = 850;
    const int32_t pressureHigh = 1100;
    const int32_t humidityLow = 0;
    const int32_t humidityHigh = 99;
    const int32_t illuminanceLow = 0;
    const int32_t illuminanceHigh = 1000;
    const int32_t co2Low = 0;
    const int32_t co2High = 3200;

    temperature = static_cast<float>(random(temperatureLow, temperatureHigh)) / temperatureScale;
    pressure = static_cast<float>(random(pressureLow, pressureHigh));
    humidity = static_cast<float>(random(humidityLow, humidityHigh));
    illuminance = static_cast<float>(random(illuminanceLow, illuminanceHigh));
    co2 = static_cast<float>(random(co2Low, co2High));
}

float Dummy::getMeasurement(Measurement measurement)
{
    switch (measurement)
    {
    case Measurement::TEMPERATURE:
        return temperature;
    case Measurement::PRESSURE:
        return pressure;
    case Measurement::HUMIDITY:
        return humidity;
    case Measurement::ILLUMINANCE:
        return illuminance;
    case Measurement::CO2:
        return co2;
    default:
        return NAN;
    }
}