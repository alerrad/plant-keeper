#include <Arduino.h>

class WaterSensor {
private:
    float _min_dist = 0.5;
    float _max_dist = 3.2;
    int _trig_pin;
    int _echo_pin;
public:
    WaterSensor(int trig_pin, int echo_pin, float min_dist, float max_dist);

    void begin();
    float getDepthCm();
    uint8_t getWaterLevel();
};