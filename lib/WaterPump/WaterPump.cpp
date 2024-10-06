#include <WaterPump.h>

WaterPump::WaterPump(int pin) : _pin(pin) {};

void WaterPump::begin() {
    pinMode(_pin, OUTPUT);
}

void WaterPump::turnOn(int secs = 10) {
    digitalWrite(_pin, HIGH);
    delay(secs * 1000);
    digitalWrite(_pin, LOW);
}