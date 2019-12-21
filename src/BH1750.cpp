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

void BH1750::wait(BH1750_Instruction::Opecode instruction)
{
  switch (instruction)
  {
  case BH1750_Instruction::Continuously_H_Resolution_Mode:
  case BH1750_Instruction::One_Time_H_Resolution_Mode:
    delayMicroseconds(BH1750_Measurement_Mode::H_Resolution_Mode);
    break;
  case BH1750_Instruction::Continuously_H_Resolution_Mode2:
  case BH1750_Instruction::One_Time_H_Resolution_Mode2:
    delayMicroseconds(BH1750_Measurement_Mode::H_Resolution_Mode2);
    break;
  case BH1750_Instruction::Continuously_L_Resolution_Mode:
  case BH1750_Instruction::One_Time_L_Resolution_Mode:
    delayMicroseconds(BH1750_Measurement_Mode::L_Resolution_Mode);
    break;
  default:;
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
