#include <Arduino.h>

class WaterPump {
private:
    const int _pin;
public:
    WaterPump(int pin);

    void begin();
    void turnOn(int secs);
};
