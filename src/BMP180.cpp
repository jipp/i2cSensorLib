#include <BMP180.hpp>

// TODO (jipp) avoid delay statements

BMP180::BMP180() = default;

BMP180::BMP180(uint8_t address)
{
  sensorAddress = address;
}

bool BMP180::begin()
{
  isSensorAvailable = checkSensorAvailability(sensorAddress, BMP180_Register::chip_id, id);

  if (isSensorAvailable)
  {
    readCalibrationData();
  }

  return isSensorAvailable;
}

bool BMP180::checkMeasurementAvailability()
{
  isMeasurementAvailable = false;

  if (isSensorAvailable)
  {
    isMeasurementAvailable = true;
  }

  return isMeasurementAvailable;
}

bool BMP180::readMeasurement()
{
  if (checkMeasurementAvailability())
  {
    readUncompensatedTemperature();
    readUncompensatedPressure();
    temperature = calculateTrueTemperature();
    pressure = calculateTruePressure();

    return true;
  }

  return false;
}

float BMP180::getMeasurement(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::TEMPERATURE:
    return temperature;
  case Measurement::PRESSURE:
    return pressure;
  default:
    return NAN;
  }
}

void BMP180::conversionTime(BME180_Mode::OSS mode)
{
  switch (mode)
  {
  case BME180_Mode::ULTRA_LOW_POWER:
    delayMicroseconds(4500);
    break;
  case BME180_Mode::STANDARD:
    delayMicroseconds(7500);
    break;
  case BME180_Mode::HIGH_RESOLUTION:
    delayMicroseconds(13500);
    break;
  case BME180_Mode::ULTRA_HIGH_RESOLUTION:
    delayMicroseconds(25500);
    break;
  default:;
  }
}

uint16_t BMP180::controlRegisterValue(BME180_Mode::OSS mode)
{
  switch (mode)
  {
  case BME180_Mode::ULTRA_LOW_POWER:
    return BMP180_RegisterValue::OSS0;
  case BME180_Mode::STANDARD:
    return BMP180_RegisterValue::OSS1;
  case BME180_Mode::HIGH_RESOLUTION:
    return BMP180_RegisterValue::OSS2;
  case BME180_Mode::ULTRA_HIGH_RESOLUTION:
    return BMP180_RegisterValue::OSS3;
  default:
    return 0;
  }
}

void BMP180::readCalibrationData()
{
  calibrationCoefficients.ac1 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC1));
  calibrationCoefficients.ac2 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC2));
  calibrationCoefficients.ac3 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC3));
  calibrationCoefficients.ac4 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC4));
  calibrationCoefficients.ac5 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC5));
  calibrationCoefficients.ac6 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_AC6));
  calibrationCoefficients.b1 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_B1));
  calibrationCoefficients.b2 = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_B2));
  calibrationCoefficients.mb = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_MB));
  calibrationCoefficients.mc = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_MC));
  calibrationCoefficients.md = readRegister16(sensorAddress, static_cast<uint8_t>(BME180_Calibration::REGISTER_MD));
}

void BMP180::readUncompensatedTemperature()
{
  uint8_t MSB = 0;
  uint8_t LSB = 0;

  writeRegister8(sensorAddress, BMP180_Register::ctrl_meas, BMP180_RegisterValue::temperature);
  delayMicroseconds(4500);

  MSB = readRegister8(sensorAddress, BMP180_Register::out_msb);
  LSB = readRegister8(sensorAddress, BMP180_Register::out_lsb);

  UT = (MSB << 8U) + LSB;
}

void BMP180::readUncompensatedPressure()
{
  uint8_t MSB = 0;
  uint8_t LSB = 0;
  uint8_t XLSB = 0;

  writeRegister8(sensorAddress, BMP180_Register::ctrl_meas, controlRegisterValue(mode) + (mode << 6U));
  conversionTime(mode);

  MSB = readRegister8(sensorAddress, BMP180_Register::out_msb);
  LSB = readRegister8(sensorAddress, BMP180_Register::out_lsb);
  XLSB = readRegister8(sensorAddress, BMP180_Register::out_xlsb);

  UP = ((static_cast<int32_t>(MSB) << 16U) | (LSB << 8U) | XLSB) >> (8U - mode);
}

float BMP180::calculateTrueTemperature()
{
  int32_t X1 = 0;
  int32_t X2 = 0;
  int32_t T = 0;

  X1 = (UT - calibrationCoefficients.ac6) * calibrationCoefficients.ac5 >> 15U;
  X2 = (calibrationCoefficients.mc << 11U) / (X1 + calibrationCoefficients.md);
  B5 = X1 + X2;
  T = (B5 + 8) >> 4;

  return T / 10.0F;
}

float BMP180::calculateTruePressure()
{
  int32_t B6 = 0;
  int32_t X1 = 0;
  int32_t X2 = 0;
  int32_t X3 = 0;
  int32_t B3 = 0;
  int32_t p = 0;
  uint32_t B4 = 0;
  uint32_t B7 = 0;

  B6 = B5 - 4000;
  X1 = (calibrationCoefficients.b2 * (B6 * B6 >> 12U)) >> 11U;
  X2 = calibrationCoefficients.ac2 * B6 >> 11U;
  X3 = X1 + X2;
  B3 = (((static_cast<int32_t>(calibrationCoefficients.ac1) * 4 + X3) << mode) + 2) / 4;
  X1 = calibrationCoefficients.ac3 * B6 >> 13U;
  X2 = (calibrationCoefficients.b1 * (B6 * B6 >> 12U)) >> 16U;
  X3 = ((X1 + X2) + 2) >> 2U;
  B4 = calibrationCoefficients.ac4 * static_cast<uint32_t>(X3 + 32768) >> 15U;
  B7 = (static_cast<uint32_t>(UP) - B3) * (50000 >> mode);
  if (B7 < 0x80000000)
  {
    p = (B7 * 2) / B4;
  }
  else
  {
    p = (B7 / B4) * 2;
  }
  X1 = (p >> 8U) * (p >> 8U);
  X1 = (X1 * 3038) >> 16U;
  X2 = (-7357 * p) >> 16U;
  p = p + ((X1 + X2 + 3791) >> 4U);

  return p / 100.0F;
}
