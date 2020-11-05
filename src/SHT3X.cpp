#include <SHT3X.hpp>

// TODO (jipp) avoid delay statements

SHT3X::SHT3X() = default;

SHT3X::SHT3X(uint8_t address)
{
  sensorAddress = address;
}

bool SHT3X::begin()
{
  isSensorAvailable = checkSensorAvailability(sensorAddress);

  if (isSensorAvailable)
  {
    reset();
  }

  return isSensorAvailable;
}

bool SHT3X::checkMeasurementAvailability()
{
  isMeasurementAvailable = false;

  if (isSensorAvailable)
  {
    isMeasurementAvailable = true;
  }

  return isMeasurementAvailable;
}

bool SHT3X::readMeasurement()
{
  uint8_t data1 = 0;
  uint8_t data2 = 0;
  uint8_t data4 = 0;
  uint8_t data5 = 0;

  if (checkMeasurementAvailability())
  {
    writeRegister16(sensorAddress, mode);
    wait(mode);

    Wire.requestFrom(static_cast<int>(sensorAddress), 6);
    if (Wire.available() == 6)
    {
      data1 = static_cast<uint8_t>(Wire.read());
      data2 = static_cast<uint8_t>(Wire.read());
      Wire.read();
      data4 = static_cast<uint8_t>(Wire.read());
      data5 = static_cast<uint8_t>(Wire.read());
      Wire.read();
    }

    temperature = 175.0F * static_cast<float>((data1 << 8U) + data2) / 65535.0F - 45.0F;
    humidity = 100.0F * static_cast<float>((data4 << 8U) + data5) / 65535.0F;

    return true;
  }

  return false;
}

float SHT3X::getMeasurement(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::TEMPERATURE:
    return temperature;
  case Measurement::HUMIDITY:
    return humidity;
  default:
    return NAN;
  }
}

void SHT3X::reset()
{
  writeRegister16(sensorAddress, SHT3X_Register::SOFT_RESET);
  delay(1);
}

void SHT3X::wait(SHT3X_Mode::Mode mode)
{
  switch (mode)
  {
  case SHT3X_Mode::H_REPEATABILITY_CLOCK_STRETCHING:
    delay(15);
    break;
  case SHT3X_Mode::M_REPEATABILITY_CLOCK_STRETCHING:
    delay(6);
    break;
  case SHT3X_Mode::L_REPEATABILITY_CLOCK_STRETCHING:
    delay(4);
    break;
  case SHT3X_Mode::H_REPEATABILITY:
    delay(15);
    break;
  case SHT3X_Mode::M_REPEATABILITY:
    delay(6);
    break;
  case SHT3X_Mode::L_REPEATABILITY:
    delay(4);
    break;
  }
}
