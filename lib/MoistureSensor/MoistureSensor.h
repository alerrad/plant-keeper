#include <Arduino.h>

class MoistureSensor {
private:
    int _water_value;
    int _air_value;
    int _pin;
public:
    MoistureSensor(int pin, int air_val, int water_val);

    void begin();
    uint8_t getMoistureLevel();
};