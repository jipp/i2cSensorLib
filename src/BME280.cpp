#include <BME280.hpp>

BME280::BME280() = default;

BME280::BME280(uint8_t address)
{
  sensorAddress = address;
}

void BME280::begin()
{
  isAvailable = checkSensorAvailability(sensorAddress, BME280_Register::id, BME280_Type::BME280);
  if (isAvailable)
  {
    readCompensationData();
    setParameter();
  }
}

void BME280::getValues()
{
  BME280_Mode::Mode mode;

  mode = getMode();
  if (mode == BME280_Mode::Sleep_mode or mode == BME280_Mode::Forced_mode)
  {
    setMode(BME280_Mode::Forced_mode);
    while (isMeasuring())
    {
      delay(1);
    }
  }
  temperature = getTemperature();
  pressure = getPressure();
  humidity = getHumidity();
}

float BME280::get(Measurement measurement)
{
  switch (measurement)
  {
  case Measurement::TEMPERATURE:
    return temperature;
  case Measurement::PRESSURE:
    return pressure;
  case Measurement::HUMIDITY:
    return humidity;
  default:
    return NAN;
  }
}

bool BME280::isMeasuring()
{
  uint8_t status;

  status = readRegister8(sensorAddress, BME280_Register::status);

  return ((status & (1U << 3U)) == 8);
}

void BME280::setParameter()
{
  if (sensorMode == BME280_Operation::Weather_Monitoring)
  {
    setMode(BME280_Mode::Forced_mode);
    setPressureOversampling(BME280_Oversampling::oversampling_1);
    setTemperatureOversampling(BME280_Oversampling::oversampling_1);
    setHumidityOversampling(BME280_Oversampling::oversampling_1);
    setFilter(BME280_Filter::Filter_off);
  }
  else if (sensorMode == BME280_Operation::Humidity_Sensing)
  {
    setMode(BME280_Mode::Forced_mode);
    setPressureOversampling(BME280_Oversampling::oversampling_skipped);
    setTemperatureOversampling(BME280_Oversampling::oversampling_1);
    setHumidityOversampling(BME280_Oversampling::oversampling_1);
    setFilter(BME280_Filter::Filter_off);
  }
  else if (sensorMode == BME280_Operation::Indoor_Navigation)
  {
    setMode(BME280_Mode::Normal_mode);
    setStandby(BME280_t_sb::t_sb_0_5);
    setPressureOversampling(BME280_Oversampling::oversampling_16);
    setTemperatureOversampling(BME280_Oversampling::oversampling_2);
    setHumidityOversampling(BME280_Oversampling::oversampling_1);
    setFilter(BME280_Filter::Filter_16);
  }
  else if (sensorMode == BME280_Operation::Gaming)
  {
    setMode(BME280_Mode::Normal_mode);
    setStandby(BME280_t_sb::t_sb_0_5);
    setPressureOversampling(BME280_Oversampling::oversampling_4);
    setTemperatureOversampling(BME280_Oversampling::oversampling_1);
    setHumidityOversampling(BME280_Oversampling::oversampling_skipped);
    setFilter(BME280_Filter::Filter_16);
  }
}

void BME280::readCompensationData()
{
  trimming.t1 = (readRegister8(sensorAddress, BME280_Trimming::dig_T1_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_T1_LSB);
  trimming.t2 = (readRegister8(sensorAddress, BME280_Trimming::dig_T2_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_T2_LSB);
  trimming.t3 = (readRegister8(sensorAddress, BME280_Trimming::dig_T3_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_T3_LSB);

  trimming.p1 = (readRegister8(sensorAddress, BME280_Trimming::dig_P1_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P1_LSB);
  trimming.p2 = (readRegister8(sensorAddress, BME280_Trimming::dig_P2_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P2_LSB);
  trimming.p3 = (readRegister8(sensorAddress, BME280_Trimming::dig_P3_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P3_LSB);
  trimming.p4 = (readRegister8(sensorAddress, BME280_Trimming::dig_P4_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P4_LSB);
  trimming.p5 = (readRegister8(sensorAddress, BME280_Trimming::dig_P5_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P5_LSB);
  trimming.p6 = (readRegister8(sensorAddress, BME280_Trimming::dig_P6_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P6_LSB);
  trimming.p7 = (readRegister8(sensorAddress, BME280_Trimming::dig_P7_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P7_LSB);
  trimming.p8 = (readRegister8(sensorAddress, BME280_Trimming::dig_P8_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P8_LSB);
  trimming.p9 = (readRegister8(sensorAddress, BME280_Trimming::dig_P9_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_P9_LSB);

  trimming.h1 = readRegister8(sensorAddress, BME280_Trimming::dig_H1);
  trimming.h2 = (readRegister8(sensorAddress, BME280_Trimming::dig_H2_MSB) << 8U) + readRegister8(sensorAddress, BME280_Trimming::dig_H2_LSB);
  trimming.h3 = readRegister8(sensorAddress, BME280_Trimming::dig_H3);
  trimming.h4 = (readRegister8(sensorAddress, BME280_Trimming::dig_H4_MSB) << 4U) + (readRegister8(sensorAddress, BME280_Trimming::dig_H4_LSB) & 0x0FU);
  trimming.h5 = (readRegister8(sensorAddress, BME280_Trimming::dig_H5_MSB) << 4U) + (static_cast<uint16_t>(readRegister8(sensorAddress, BME280_Trimming::dig_H5_LSB) >> 4U) & 0x0FU);
  trimming.h6 = readRegister8(sensorAddress, BME280_Trimming::dig_H6);
}

void BME280::setStandby(uint8_t t_sb)
{
  uint8_t data;
  BME280_Mode::Mode originalMode;

  originalMode = getMode();
  setMode(BME280_Mode::Sleep_mode);
  data = readRegister8(sensorAddress, BME280_Register::config);
  data &= ~((1U << 7U) | (1U << 6U) | (1U << 5U));
  data |= static_cast<uint8_t>(t_sb << 5U);
  writeRegister8(sensorAddress, BME280_Register::config, data);
  setMode(originalMode);
}

void BME280::setFilter(uint8_t filter)
{
  uint8_t data;
  BME280_Mode::Mode originalMode;

  originalMode = getMode();
  setMode(BME280_Mode::Sleep_mode);
  data = readRegister8(sensorAddress, BME280_Register::config);
  data &= ~((1U << 4U) | (1U << 3U) | (1U << 2U));
  data |= static_cast<uint8_t>(filter << 2U);
  writeRegister8(sensorAddress, BME280_Register::config, data);
  setMode(originalMode);
}

void BME280::setPressureOversampling(uint8_t osrs_p)
{
  uint8_t data;
  BME280_Mode::Mode originalMode;

  originalMode = getMode();
  setMode(BME280_Mode::Sleep_mode);
  data = readRegister8(sensorAddress, BME280_Register::ctrl_meas);
  data &= ~((1U << 4U) | (1U << 3U) | (1U << 2U));
  data |= static_cast<uint8_t>(osrs_p << 2U);
  writeRegister8(sensorAddress, BME280_Register::ctrl_meas, data);
  setMode(originalMode);
}

void BME280::setTemperatureOversampling(uint8_t osrs_t)
{
  uint8_t data;
  BME280_Mode::Mode originalMode;

  originalMode = getMode();
  setMode(BME280_Mode::Sleep_mode);
  data = readRegister8(sensorAddress, BME280_Register::ctrl_meas);
  data &= ~((1U << 7U) | (1U << 6U) | (1U << 5U));
  data |= static_cast<uint8_t>(osrs_t << 5U);
  writeRegister8(sensorAddress, BME280_Register::ctrl_meas, data);
  setMode(originalMode);
}

void BME280::setHumidityOversampling(uint8_t osrs_h)
{
  uint8_t data;
  BME280_Mode::Mode originalMode;

  originalMode = getMode();
  setMode(BME280_Mode::Sleep_mode);
  data = readRegister8(sensorAddress, BME280_Register::ctrl_hum);
  data &= ~((1U << 2U) | (1U << 1U) | (1U << 0U));
  data |= static_cast<uint8_t>(osrs_h << 0U);
  writeRegister8(sensorAddress, BME280_Register::ctrl_hum, data);
  setMode(originalMode);
}

void BME280::setMode(BME280_Mode::Mode mode)
{
  uint8_t data;

  data = readRegister8(sensorAddress, BME280_Register::ctrl_meas);
  data &= ~((1U << 1U) | (1U << 0U));
  data |= static_cast<uint8_t>(mode);
  writeRegister8(sensorAddress, BME280_Register::ctrl_meas, data);
}

BME280_Mode::Mode BME280::getMode()
{
  uint8_t data;

  data = readRegister8(sensorAddress, BME280_Register::ctrl_meas);

  return static_cast<BME280_Mode::Mode>(data & 0x03U);
}

// BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T)
// {
//   BME280_S32_t var1, var2, T;
//   var1 = ((((adc_T >> 3) – ((BME280_S32_t)dig_T1 << 1))) * ((BME280_S32_t)dig_T2)) >> 11;
//   var2 = (((((adc_T >> 4) – ((BME280_S32_t)dig_T1)) * ((adc_T >> 4) – ((BME280_S32_t)dig_T1))) >> 12) * ((BME280_S32_t)dig_T3)) >> 14;
//   t_fine = var1 + var2;
//   T = (t_fine * 5 + 128) >> 8;
//   return T;
// }

float BME280::getTemperature()
{
  int32_t var1;
  int32_t var2;
  int32_t T;
  uint8_t temp_msb;
  uint8_t temp_lsb;
  uint8_t temp_xlsb;
  int32_t adc_T;

  temp_msb = readRegister8(this->sensorAddress, BME280_Register::temp_msb);
  temp_lsb = readRegister8(this->sensorAddress, BME280_Register::temp_lsb);
  temp_xlsb = readRegister8(this->sensorAddress, BME280_Register::temp_xlsb);

  adc_T = (static_cast<uint32_t>(temp_msb) << 12U) | (static_cast<uint32_t>(temp_lsb) << 4U) | ((static_cast<uint32_t>(temp_xlsb) >> 4U) & 0x0FU);

  var1 = ((((adc_T >> 3U) - (static_cast<int32_t>(trimming.t1) << 1U))) * (static_cast<int32_t>(trimming.t2))) >> 11U;
  var2 = (((((adc_T >> 4U) - (static_cast<int32_t>(trimming.t1))) * ((adc_T >> 4U) - static_cast<int32_t>(trimming.t1))) >> 12U) * static_cast<int32_t>(trimming.t3)) >> 14U;
  t_fine = var1 + var2;
  T = (t_fine * 5 + 128) >> 8U;

  return T / 100.0F;
}

// BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P)
// {
//   BME280_S64_t var1, var2, p;
//   var1 = ((BME280_S64_t)t_fine) – 128000;
//   var2 = var1 * var1 * (BME280_S64_t)dig_P6;
//   var2 = var2 + ((var1 * (BME280_S64_t)dig_P5) << 17);
//   var2 = var2 + (((BME280_S64_t)dig_P4) << 35);
//   var1 = ((var1 * var1 * (BME280_S64_t)dig_P3) >> 8) + ((var1 * (BME280_S64_t)dig_P2) << 12);
//   var1 = (((((BME280_S64_t)1) << 47) + var1)) * ((BME280_S64_t)dig_P1) >> 33;
//   if (var1 == 0)
//   {
//     return 0; // avoid exception caused by division by zero
//   }
//   p = 1048576 - adc_P;
//   p = (((p << 31) - var2) * 3125) / var1;
//   var1 = (((BME280_S64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
//   var2 = (((BME280_S64_t)dig_P8) * p) >> 19;
//   p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)dig_P7) << 4);
//   return (BME280_U32_t)p;
// }

float BME280::getPressure()
{
  int64_t var1;
  int64_t var2;
  int64_t P;
  uint8_t press_msb;
  uint8_t press_lsb;
  uint8_t press_xlsb;
  int32_t adc_P;

  press_msb = readRegister8(this->sensorAddress, BME280_Register::press_msb);
  press_lsb = readRegister8(this->sensorAddress, BME280_Register::press_lsb);
  press_xlsb = readRegister8(this->sensorAddress, BME280_Register::press_xlsb);

  adc_P = (static_cast<uint32_t>(press_msb) << 12U) | (static_cast<uint32_t>(press_lsb) << 4U) | ((static_cast<uint32_t>(press_xlsb) >> 4U) & 0x0FU);

  var1 = static_cast<int64_t>(t_fine) - 128000;
  var2 = var1 * var1 * static_cast<int64_t>(trimming.p6);
  var2 = var2 + ((var1 * static_cast<int64_t>(trimming.p5)) << 17U);
  var2 = var2 + (static_cast<int64_t>(trimming.p4) << 35U);
  var1 = ((var1 * var1 * static_cast<int64_t>(trimming.p3)) >> 8U) + ((var1 * static_cast<int64_t>(trimming.p2)) << 12U);
  var1 = ((1LL << 47U) + var1) * static_cast<int64_t>(trimming.p1) >> 33U;
  if (var1 == 0)
  {
    return 0;
  }
  P = 1048576 - adc_P;
  P = (((P << 31U) - var2) * 3125) / var1;
  var1 = (static_cast<int64_t>(trimming.p9) * (P >> 13U) * (P >> 13U)) >> 25U;
  var2 = (static_cast<int64_t>(trimming.p8) * P) >> 19U;
  P = ((P + var1 + var2) >> 8U) + (static_cast<int64_t>(trimming.p7) << 4U);

  return static_cast<uint32_t>(P) / 256.0F / 100.0F;
}

// BME280_U32_t bme280_compensate_H_int32(BME280_S32_t adc_H)
// {
//   BME280_S32_t v_x1_u32r;
//   v_x1_u32r = (t_fine - ((BME280_S32_t)76800));
//   v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)dig_H4) << 20) - (((BME280_S32_t)dig_H5) * v_x1_u32r)) + ((BME280_S32_t)16384)) >> 15) * (((((((v_x1_u32r * ((BME280_S32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((BME280_S32_t)dig_H3)) >> 11) + ((BME280_S32_t)32768))) >> 10) + ((BME280_S32_t)2097152)) * ((BME280_S32_t)dig_H2) + 8192) >> 14));
//   v_x1_u32r = (v_x1_u32r – (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((BME280_S32_t)dig_H1)) >> 4));
//   v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
//   v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
//   return (BME280_U32_t)(v_x1_u32r >> 12);
// }

float BME280::getHumidity()
{
  int32_t var1;
  uint8_t hum_msb;
  uint8_t hum_lsb;
  int32_t adc_H;

  hum_msb = readRegister8(this->sensorAddress, BME280_Register::hum_msb);
  hum_lsb = readRegister8(this->sensorAddress, BME280_Register::hum_lsb);

  adc_H = (hum_msb << 8U) + (hum_lsb);

  var1 = t_fine - 76800L;
  var1 = (((((adc_H << 14) - (static_cast<int32_t>(trimming.h4) << 20) - (static_cast<int32_t>(trimming.h5) * var1)) + 16384L) >> 15U) * (((((((var1 * static_cast<int32_t>(trimming.h6)) >> 10U) * (((var1 * static_cast<int32_t>(trimming.h3)) >> 11U) + 32768L)) >> 10U) + 2097152L) * static_cast<int32_t>(trimming.h2) + 8192) >> 14U));
  var1 = (var1 - (((((var1 >> 15U) * (var1 >> 15U)) >> 7U) * static_cast<int32_t>(trimming.h1)) >> 4U));
  var1 = (var1 < 0 ? 0 : var1);
  var1 = (var1 > 419430400 ? 419430400 : var1);

  return static_cast<uint32_t>(var1 >> 12U) / 1024.0F;
}
