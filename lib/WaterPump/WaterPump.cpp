#include <WaterPump.h>

WaterPump::WaterPump(int pump_pin, int button_pin) {
    _pump_pin = pump_pin;
    _button_pin = button_pin;
}

void WaterPump::begin() {
    pinMode(_pump_pin, OUTPUT);
    pinMode(_button_pin, INPUT);
}

void WaterPump::turnOn(int secs = 10) {
    digitalWrite(_pump_pin, HIGH);
    delay(secs * 1000);
    digitalWrite(_pump_pin, LOW);
}

void WaterPump::sync_button() {
    if (digitalRead(_button_pin) == HIGH)
        digitalWrite(_pump_pin, HIGH);
    else
        digitalWrite(_pump_pin, LOW);
}