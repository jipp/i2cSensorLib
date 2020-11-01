#include <Arduino.h>

#include <BH1750.hpp>
#include <BME280.hpp>
#include <BMP180.hpp>
#include <Dummy.hpp>
#include <Memory.hpp>
#include <SCD30.hpp>
#include <SHT3X.hpp>
#include <VCC.hpp>
#include <Wire.h>

#ifndef SPEED
#define SPEED 460800
#endif

#if defined(ESP8266)
ADC_MODE(ADC_VCC)
#endif

Dummy dummy = Dummy();
VCC vcc = VCC();
Memory memory = Memory();
BH1750 bh1750 = BH1750();
SHT3X sht3x = SHT3X(0x45);
BMP180 bmp180 = BMP180();
BME280 bme280 = BME280();
SCD30 scd30 = SCD30();

void publishValues()
{
  Serial.println();
  if (dummy.isSensorAvailable)
  {
    dummy.readMeasurement();
    Serial.print("Dummy:  temperature: ");
    Serial.print(dummy.getMeasurement(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.print(dummy.getMeasurement(Measurement::HUMIDITY));
    Serial.print(" pressure: ");
    Serial.print(dummy.getMeasurement(Measurement::PRESSURE));
    Serial.print(" illuminance: ");
    Serial.print(dummy.getMeasurement(Measurement::ILLUMINANCE));
    Serial.print(" co2: ");
    Serial.println(dummy.getMeasurement(Measurement::CO2));
  }
  if (vcc.isSensorAvailable)
  {
    vcc.readMeasurement();
    Serial.print("VCC:    voltage: ");
    Serial.println(vcc.getMeasurement(Measurement::VOLTAGE));
  }
  if (memory.isSensorAvailable)
  {
    memory.readMeasurement();
    Serial.print("Memory: byte: ");
    Serial.println(memory.getMeasurement(Measurement::MEMORY));
  }
  if (bh1750.isSensorAvailable)
  {
    bh1750.readMeasurement();
    Serial.print("BH1750: illuminance: ");
    Serial.println(bh1750.getMeasurement(Measurement::ILLUMINANCE));
  }
  if (sht3x.isSensorAvailable)
  {
    sht3x.readMeasurement();
    Serial.print("SHT3X:  temperature: ");
    Serial.print(sht3x.getMeasurement(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.println(sht3x.getMeasurement(Measurement::HUMIDITY));
  }
  if (bmp180.isSensorAvailable)
  {
    bmp180.readMeasurement();
    Serial.print("BMP180: temperature: ");
    Serial.print(bmp180.getMeasurement(Measurement::TEMPERATURE));
    Serial.print(" pressure: ");
    Serial.println(bmp180.getMeasurement(Measurement::PRESSURE));
  }
  if (bme280.isSensorAvailable)
  {
    bme280.readMeasurement();
    Serial.print("BME280: temperature: ");
    Serial.print(bme280.getMeasurement(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.print(bme280.getMeasurement(Measurement::HUMIDITY));
    Serial.print(" pressure: ");
    Serial.println(bme280.getMeasurement(Measurement::PRESSURE));
  }
  if (scd30.isSensorAvailable)
  {
    scd30.readMeasurement();
    Serial.print("SCD30: temperature: ");
    Serial.print(scd30.getMeasurement(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.print(scd30.getMeasurement(Measurement::HUMIDITY));
    Serial.print(" co2: ");
    Serial.println(scd30.getMeasurement(Measurement::CO2));
  }
}

void setup()
{
  Serial.begin(SPEED);
  Wire.begin();
  dummy.begin();
  vcc.begin();
  memory.begin();
  bh1750.begin();
  sht3x.begin();
  bmp180.begin();
  bme280.begin();
  scd30.begin();
}

void loop()
{
  while (true)
  {
    publishValues();
    delay(2000);
  }
}
