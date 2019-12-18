#include <SHT3X.hpp>

SHT3X::SHT3X() = default;

SHT3X::SHT3X(uint8_t address)
{
  sensorAddress = address;
}

void SHT3X::begin()
{
  isAvailable = checkSensorAvailability(sensorAddress);
  if (isAvailable)
  {
    reset();
  }
}

void SHT3X::getValues()
{
  std::array<uint8_t, 6> data;

  writeRegister16(sensorAddress, mode);
  wait(mode);

  Wire.requestFrom(static_cast<int>(sensorAddress), 6);
  if (Wire.available() == 6)
  {
    for (int i = 0; i < 6; i++)
    {
      data[i] = static_cast<uint8_t>(Wire.read());
    }
  }

  temperature = 175.0F * ((data[0] * 256.0F) + data[1]) / 65535.0F - 45.0F;
  humidity = 100.0F * ((data[3] * 256.0F) + data[4]) / 65535.0F;
}

float SHT3X::get(Measurement measurement)
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
