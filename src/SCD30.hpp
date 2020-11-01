#ifndef SCD30_HPP
#define SCD30_HPP

#include <Arduino.h>
#include <Sensor.hpp>
#include <Wire.h>

class SCD30_Command
{
public:
    enum Command
    {
        Trigger_Continouos_Measurement = 0x0010,
        Stop_Continuous_Measurement = 0x0104,
        Set_Measurement_interval = 0x4600,
        Get_Data_Ready_Status = 0x0202,
        Read_Measurement = 0x0300,
        Automatic_Self_Calibration = 0x5306,
        Set_Forced_Recalibration_Value = 0x5204,
        Set_Temperature_Offset = 0x5403,
        Altitude_Compensation = 0x5102
    };
};

class SCD30 : public Sensor
{
public:
    SCD30();
    explicit SCD30(uint8_t address);
    bool begin() override;
    bool checkMeasurementAvailability() override;
    void readMeasurement() override;
    float getMeasurement(Measurement measurement) override;

private:
    const uint8_t defaultSensorAddress = 0x61;
    uint8_t sensorAddress = defaultSensorAddress;
    float temperature = 0.0;
    float humidity = 0.0;
    float co2 = 0.0;
};

#endif
