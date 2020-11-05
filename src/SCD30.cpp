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
        writeRegister16crc(sensorAddress, SCD30_Command::Trigger_Continouos_Measurement, 0);
        writeRegister16crc(sensorAddress, SCD30_Command::Set_Measurement_Interval, 2);
        writeRegister16crc(sensorAddress, SCD30_Command::Automatic_Self_Calibration, 1);
    }

    return isSensorAvailable;
}

bool SCD30::checkMeasurementAvailability()
{
    isMeasurementAvailable = false;

    if (isSensorAvailable)
    {
        if (readRegister16(sensorAddress, static_cast<uint16_t>(SCD30_Command::Get_Data_Ready_Status)) == 1)
        {
            isMeasurementAvailable = true;
        }
    }

    return isMeasurementAvailable;
}

bool SCD30::readMeasurement()
{
    byte bytesToCrc[2];
    uint8_t crc = 0;
    uint8_t incoming = 0;
    uint32_t tempCo2 = 0;
    uint32_t tempHumidity = 0;
    uint32_t tempTemperature = 0;

    if (checkMeasurementAvailability())
    {
        writeRegister16(sensorAddress, SCD30_Command::Read_Measurement);
        Wire.requestFrom(static_cast<int>(sensorAddress), 18);

        for (uint8_t x = 0; x < 18; x++)
        {
            incoming = Wire.read();

            switch (x)
            {
            case 0:
            case 1:
            case 3:
            case 4:
                tempCo2 <<= 8;
                tempCo2 |= incoming;
                bytesToCrc[x % 3] = incoming;
                break;
            case 6:
            case 7:
            case 9:
            case 10:
                tempTemperature <<= 8;
                tempTemperature |= incoming;
                bytesToCrc[x % 3] = incoming;
                break;
            case 12:
            case 13:
            case 15:
            case 16:
                tempHumidity <<= 8;
                tempHumidity |= incoming;
                bytesToCrc[x % 3] = incoming;
                break;
            default:
                crc = crc8(bytesToCrc, 2);
                if (crc != incoming)
                {
                    return false;
                }
            }
        }

        memcpy(&co2, &tempCo2, sizeof(co2));
        memcpy(&temperature, &tempTemperature, sizeof(temperature));
        memcpy(&humidity, &tempHumidity, sizeof(humidity));

        return true;
    }

    return false;
}

float SCD30::getMeasurement(Measurement measurement)
{
    switch (measurement)
    {
    case Measurement::HUMIDITY:
        return humidity;
    case Measurement::TEMPERATURE:
        return temperature;
    case Measurement::CO2:
        return co2;
    default:
        return NAN;
    }
}