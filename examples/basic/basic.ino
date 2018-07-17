#include <Arduino.h>

#include <Wire.h>
#include <i2cSensorLib.h>

#if defined(ESP8266)
ADC_MODE(ADC_VCC);
#endif

VCC vcc = VCC();
BH1750 bh1750 = BH1750();
SHT3X sht3x = SHT3X(0x45);
BMP180 bmp180 = BMP180();
BME280 bme280 = BME280();

void publishValues() {
  Serial.println("");
  if (vcc.isAvailable) {
    vcc.getValues();
    Serial.print("VCC:    voltage: ");
    Serial.println(vcc.get(Sensor::VOLTAGE_MEASUREMENT));
  }
  if (bh1750.isAvailable) {
    bh1750.getValues();
    Serial.print("BH1750: illuminance: ");
    Serial.println(bh1750.get(Sensor::ILLUMINANCE_MEASUREMENT));
  }
  if (sht3x.isAvailable) {
    sht3x.getValues();
    Serial.print("SHT3X:  temperature: ");
    Serial.print(sht3x.get(Sensor::TEMPERATURE_MEASUREMENT));
    Serial.print(" humidity: ");
    Serial.println(sht3x.get(Sensor::HUMIDITY_MEASUREMENT));
  }
  if (bmp180.isAvailable) {
    bmp180.getValues();
    Serial.print("BMP180: temperature: ");
    Serial.print(bmp180.get(Sensor::TEMPERATURE_MEASUREMENT));
    Serial.print(" pressure: ");
    Serial.println(bmp180.get(Sensor::PRESSURE_MEASUREMENT));
  }
  if (bme280.isAvailable) {
    bme280.getValues();
    Serial.print("BME280: temperature: ");
    Serial.print(bme280.get(Sensor::TEMPERATURE_MEASUREMENT));
    Serial.print(" humidity: ");
    Serial.print(bme280.get(Sensor::HUMIDITY_MEASUREMENT));
    Serial.print(" pressure: ");
    Serial.println(bme280.get(Sensor::PRESSURE_MEASUREMENT));
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  vcc.begin();
  bh1750.begin();
  sht3x.begin();
  bmp180.begin();
  bme280.begin();
}

void loop() {
  while (true) {
    publishValues();
    delay(2000);
  }
}
