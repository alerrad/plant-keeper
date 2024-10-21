#include <Arduino.h>

class WaterPump {
private:
    int _pump_pin;
    int _button_pin;
public:
    WaterPump(int pump_pin, int button_pin);

    void begin();
    void turnOn(int secs);
    void sync_button();
};
