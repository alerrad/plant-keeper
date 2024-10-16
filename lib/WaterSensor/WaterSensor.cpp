#include <WaterSensor.h>

WaterSensor::WaterSensor(int trig_pin, int echo_pin, float min_dist, float max_dist) {
    _trig_pin = trig_pin;
    _echo_pin = echo_pin;
    _min_dist = min_dist;
    _max_dist = max_dist;
}

void WaterSensor::begin() {
    pinMode(_trig_pin, OUTPUT);
    pinMode(_echo_pin, INPUT);
}

float WaterSensor::getDepthCm() {
    digitalWrite(_trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig_pin, LOW);
    return pulseIn(_echo_pin, HIGH) * 0.034 / 2;
}

/// @returns water level in percentage (0 - 100)
uint8_t WaterSensor::getWaterLevel() {
    float depth = getDepthCm();
    return map(depth, _min_dist, _max_dist, 100, 0);
}