#include <Sensor.hpp>

bool Sensor::checkSensorAvailability(uint8_t sensorAddress)
{
  uint8_t transmissionStatus;

  Wire.beginTransmission(sensorAddress);
  transmissionStatus = Wire.endTransmission();

  return (transmissionStatus == 0);
}

bool Sensor::checkSensorAvailability(uint8_t sensorAddress, uint8_t registerAddress, uint8_t value)
{
  if (checkSensorAvailability(sensorAddress))
  {
    return (value == readRegister8(sensorAddress, registerAddress));
  }

  return false;
}

void Sensor::writeRegister8(uint8_t sensorAddress, uint8_t registerAddress)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
}

void Sensor::writeRegister8(uint8_t sensorAddress, uint8_t registerAddress, uint8_t registerValue)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.write(registerValue);
  Wire.endTransmission();
}

void Sensor::writeRegister16(uint8_t sensorAddress, uint16_t registerAddress)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress >> MSB8);
  Wire.write(registerAddress & Mask15);
  Wire.endTransmission();
}

uint8_t Sensor::readRegister8(uint8_t sensorAddress)
{
  uint8_t registerValue = 0x00;

  Wire.requestFrom(static_cast<int>(sensorAddress), 1);

  if (Wire.available() == 1)
  {
    registerValue = static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}

uint8_t Sensor::readRegister8(uint8_t sensorAddress, uint8_t registerAddress)
{
  uint8_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(static_cast<int>(sensorAddress), 1);

  if (Wire.available() == 1)
  {
    registerValue = static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}

uint16_t Sensor::readRegister16(uint8_t sensorAddress)
{
  uint16_t registerValue = 0;

  Wire.requestFrom(static_cast<int>(sensorAddress), 2);

  if (Wire.available() == 2)
  {
    registerValue = static_cast<uint8_t>(Wire.read());
    registerValue <<= MSB8;
    registerValue |= static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}

uint16_t Sensor::readRegister16(uint8_t sensorAddress, uint8_t registerAddress)
{
  uint16_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(static_cast<int>(sensorAddress), 2);

  if (Wire.available() == 2)
  {
    registerValue = static_cast<uint8_t>(Wire.read());
    registerValue <<= MSB8;
    registerValue |= static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}

uint32_t Sensor::readRegister24(uint8_t sensorAddress, uint8_t registerAddress)
{
  uint32_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(static_cast<int>(sensorAddress), 3);

  if (Wire.available() == 3)
  {
    registerValue = static_cast<uint8_t>(Wire.read());
    registerValue <<= MSB8;
    registerValue |= static_cast<uint8_t>(Wire.read());
    registerValue <<= MSB8;
    registerValue |= static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}
