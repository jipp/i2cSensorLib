# i2cSensorLib

The library has the goal to provide the same command syntax for different sensors.

## supported sensors
 * BH1750
 * BME280
 * BMP180
 * SHT3X

## command syntax
 * include library
    #include <i2cSensorLib.h>

 * prepare ADC mode on ESP8266
    ADC_MODE(ADC_VCC);

 * instantiate variable
    VCC vcc = VCC();
    BH1750 bh1750 = BH1750();
    SHT3X sht3x = SHT3X(0x45);
    BMP180 bmp180 = BMP180();
    BME280 bme280 = BME280();

 * check for availability and do compensation calculation
    vcc.begin();
    bh1750.begin();
    sht3x.begin();
    bmp180.begin();
    bme280.begin();

 * get info about availability
    vcc.isAvailable
    bh1750.isAvailable
    sht3x.isAvailable
    bmp180.isAvailable
    bme280.isAvailable

* measure values
   vcc.getValues();
   bh1750.getValues();
   sht3x.getValues();
   bmp180.getValues();
   bme280.getValues();

* get measured getValues
   vcc.get(Sensor::VOLTAGE_MEASUREMENT));
   bh1750.get(Sensor::ILLUMINANCE_MEASUREMENT)
   sht3x.get(Sensor::TEMPERATURE_MEASUREMENT)
   bme280.get(Sensor::HUMIDITY_MEASUREMENT)
   bmp180.get(Sensor::PRESSURE_MEASUREMENT)
