#include <BH1750.hpp>

BH1750::BH1750() = default;

BH1750::BH1750(uint8_t address)
{
  sensorAddress = address;
}

void BH1750::begin()
{
  isAvailable = checkSensorAvailability(sensorAddress);
}

void BH1750::getValues()
{
  writeRegister8(sensorAddress, sensorMode);
  wait(sensorMode);
  illuminance = readRegister16(sensorAddress);
}

void BH1750::wait(Mode mode)
{
  switch (mode)
  {
  case Continuously_H_Resolution_Mode:
  case One_Time_H_Resolution_Mode:
    delayMicroseconds(H_Resolution_Mode);
    break;
  case Continuously_H_Resolution_Mode2:
  case One_Time_H_Resolution_Mode2:
    delayMicroseconds(H_Resolution_Mode2);
    break;
  case Continuously_L_Resolution_Mode:
  case One_Time_L_Resolution_Mode:
    delayMicroseconds(L_Resolution_Mode);
    break;
  default:
  }
}

float BH1750::get(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::ILLUMINANCE:
    return illuminance;
  default:
    return NAN;
  }
}
