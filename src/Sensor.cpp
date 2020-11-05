#include <Sensor.hpp>

bool Sensor::checkSensorAvailability(uint8_t sensorAddress)
{
  uint8_t transmissionStatus = 0;

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

bool Sensor::writeRegister8(uint8_t sensorAddress, uint8_t registerAddress)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);

  return (Wire.endTransmission() == 0);
}

bool Sensor::writeRegister8(uint8_t sensorAddress, uint8_t registerAddress, uint8_t registerValue)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);
  Wire.write(registerValue);

  return (Wire.endTransmission() == 0);
}

bool Sensor::writeRegister16(uint8_t sensorAddress, uint16_t registerAddress)
{
  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress >> 8U);
  Wire.write(registerAddress & 0x0FU);

  return (Wire.endTransmission() == 0);
}

bool Sensor::writeRegister16crc(uint8_t sensorAddress, uint16_t registerAddress, uint16_t registerValue)
{
  uint8_t data[2];
  data[0] = registerValue >> 8;
  data[1] = registerValue & 0xFF;
  uint8_t crc = crc8(data, 2); //Calc CRC on the arguments only, not the command

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress >> 8U);
  Wire.write(registerAddress & 0x0FU);
  Wire.write(registerValue >> 8U);
  Wire.write(registerValue & 0x0FU);
  Wire.write(crc);

  return (Wire.endTransmission() == 0);
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

  if (Wire.endTransmission() == 0)
  {
    Wire.requestFrom(static_cast<int>(sensorAddress), 1);

    if (Wire.available() == 1)
    {
      registerValue = static_cast<uint8_t>(Wire.read());
    }
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
    registerValue <<= 8U;
    registerValue |= static_cast<uint8_t>(Wire.read());
  }

  return registerValue;
}

uint16_t Sensor::readRegister16(uint8_t sensorAddress, uint8_t registerAddress)
{
  uint16_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);

  if (Wire.endTransmission() == 0)
  {
    Wire.requestFrom(static_cast<int>(sensorAddress), 2);

    if (Wire.available() == 2)
    {
      registerValue = static_cast<uint8_t>(Wire.read());
      registerValue <<= 8U;
      registerValue |= static_cast<uint8_t>(Wire.read());
    }
  }
  return registerValue;
}

uint16_t Sensor::readRegister16(uint8_t sensorAddress, uint16_t registerAddress)
{
  uint16_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress >> 8);
  Wire.write(registerAddress & 0xFF); // or 0x0F?

  if (Wire.endTransmission() == 0)
  {
    Wire.requestFrom(static_cast<int>(sensorAddress), 2);

    if (Wire.available() == 2)
    {
      registerValue = static_cast<uint8_t>(Wire.read());
      registerValue <<= 8U;
      registerValue |= static_cast<uint8_t>(Wire.read());
    }
  }

  return registerValue;
}

uint32_t Sensor::readRegister24(uint8_t sensorAddress, uint8_t registerAddress)
{
  uint32_t registerValue = 0x00;

  Wire.beginTransmission(sensorAddress);
  Wire.write(registerAddress);

  if (Wire.endTransmission() == 0)
  {
    Wire.requestFrom(static_cast<int>(sensorAddress), 3);

    if (Wire.available() == 3)
    {
      registerValue = static_cast<uint8_t>(Wire.read());
      registerValue <<= 8U;
      registerValue |= static_cast<uint8_t>(Wire.read());
      registerValue <<= 8U;
      registerValue |= static_cast<uint8_t>(Wire.read());
    }
  }

  return registerValue;
}

uint8_t Sensor::crc8(const uint8_t data[], uint8_t len)
{
  uint8_t crc = 0xFF;
  uint8_t polynomial = 0x31;

  for (uint8_t x = 0; x < len; x++)
  {
    crc ^= data[x]; // XOR-in the next input byte

    for (uint8_t i = 0; i < 8; i++)
    {
      if ((crc & 0x80) != 0)
      {
        crc = static_cast<uint8_t>((crc << 1) ^ polynomial);
      }
      else
      {
        crc <<= 1;
      }
    }
  }

  return crc;
}