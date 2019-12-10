#include <Arduino.h>

#include <BH1750.hpp>
#include <BME280.hpp>
#include <BMP180.hpp>
#include <Dummy.hpp>
#include <Memory.hpp>
#include <SHT3X.hpp>
#include <VCC.hpp>
#include <Wire.h>

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

void publishValues()
{
  Serial.println();
  if (dummy.isAvailable)
  {
    dummy.getValues();
    Serial.print("Dummy:  temperature: ");
    Serial.print(dummy.get(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.print(dummy.get(Measurement::HUMIDITY));
    Serial.print(" pressure: ");
    Serial.println(dummy.get(Measurement::PRESSURE));
    Serial.print(" illuminance: ");
    Serial.println(dummy.get(Measurement::ILLUMINANCE));
  }
  if (vcc.isAvailable)
  {
    vcc.getValues();
    Serial.print("VCC:    voltage: ");
    Serial.println(vcc.get(Measurement::VOLTAGE));
  }
  if (memory.isAvailable)
  {
    memory.getValues();
    Serial.print("Memory: byte: ");
    Serial.println(memory.get(Measurement::MEMORY));
  }
  if (bh1750.isAvailable)
  {
    bh1750.getValues();
    Serial.print("BH1750: illuminance: ");
    Serial.println(bh1750.get(Measurement::ILLUMINANCE));
  }
  if (sht3x.isAvailable)
  {
    sht3x.getValues();
    Serial.print("SHT3X:  temperature: ");
    Serial.print(sht3x.get(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.println(sht3x.get(Measurement::HUMIDITY));
  }
  if (bmp180.isAvailable)
  {
    bmp180.getValues();
    Serial.print("BMP180: temperature: ");
    Serial.print(bmp180.get(Measurement::TEMPERATURE));
    Serial.print(" pressure: ");
    Serial.println(bmp180.get(Measurement::PRESSURE));
  }
  if (bme280.isAvailable)
  {
    bme280.getValues();
    Serial.print("BME280: temperature: ");
    Serial.print(bme280.get(Measurement::TEMPERATURE));
    Serial.print(" humidity: ");
    Serial.print(bme280.get(Measurement::HUMIDITY));
    Serial.print(" pressure: ");
    Serial.println(bme280.get(Measurement::PRESSURE));
  }
}

void setup()
{
  Serial.begin(460800);
  Wire.begin();
  dummy.begin();
  vcc.begin();
  memory.begin();
  bh1750.begin();
  sht3x.begin();
  bmp180.begin();
  bme280.begin();
}

void loop()
{
  while (true)
  {
    publishValues();
    delay(2000);
  }
}
