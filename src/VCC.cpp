#include <VCC.h>

VCC::VCC() {
}

void VCC::begin() {
  this->isAvailable = true;
}

void VCC::getValues() {
  this->voltage = ESP.getVcc() / 1000.0;
}

float VCC::get(uint8_t Measurement) {
  switch (Measurement) {
    case VOLTAGE_MEASUREMENT:
    return this->voltage;
    default:
    return NAN;
  }
}
