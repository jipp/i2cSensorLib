#include <VCC.h>

VCC::VCC() {
}

void VCC::begin() {
  #if defined(ESP8266)
  this->isAvailable = true;
  #else
  this->isAvailable = false;
  #endif
}

void VCC::getValues() {
  #if defined(ESP8266)
  this->voltage = ESP.getVcc() / 1000.0;
  #else
  this->voltage = NAN;
  #endif
}

float VCC::get(uint8_t Measurement) {
  switch (Measurement) {
    case VOLTAGE_MEASUREMENT:
    return this->voltage;
    default:
    return NAN;
  }
}
