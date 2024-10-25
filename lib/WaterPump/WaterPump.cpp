#include <WaterPump.h>

WaterPump::WaterPump(int pump_pin, int button_pin) {
    _pump_pin = pump_pin;
    _button_pin = button_pin;
}

void WaterPump::begin() {
    pinMode(_pump_pin, OUTPUT);
    pinMode(_button_pin, INPUT);
}

void WaterPump::turnOn(int secs) {
    // Block buttons to not interfere with their loop
    blockButton();
    blockBlynkButton();
    // Water the plant for *secs* seconds
    digitalWrite(_pump_pin, HIGH);
    delay(secs * 1000);
    digitalWrite(_pump_pin, LOW);
    // Enable buttons after watering
    unblockBlynkButton();
    unblockButton();
}

void WaterPump::syncButton() {
    if (_button_enabled) {
        if (digitalRead(_button_pin) == HIGH) {
            blockBlynkButton();
            digitalWrite(_pump_pin, HIGH);
        } else {
            digitalWrite(_pump_pin, LOW);
            unblockBlynkButton();
        }
    }
}

void WaterPump::blockButton() {
    _button_enabled = false;
}

void WaterPump::unblockButton() {
    _button_enabled = true;
}

bool WaterPump::isEnabled() {
    return _button_enabled;
}

bool WaterPump::isBlynkButtonEnabled() {
    return _blynk_button_enabled;
}

void WaterPump::blockBlynkButton() {
    _blynk_button_enabled = false;
}

void WaterPump::unblockBlynkButton() {
    _blynk_button_enabled = true;
}