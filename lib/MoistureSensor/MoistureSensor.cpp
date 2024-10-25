#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int pin, int air_val, int water_val) {
    _pin = pin;
    _air_value = air_val;
    _water_value = water_val;
}

void MoistureSensor::begin() {
    pinMode(_pin, INPUT);
}

/// @returns moisture level in percentage (0 - 100)
uint8_t MoistureSensor::getMoistureLevel() {
    int reading = analogRead(_pin);
    return constrain(map(reading, _water_value, _air_value, 100, 0), 0, 100);
}