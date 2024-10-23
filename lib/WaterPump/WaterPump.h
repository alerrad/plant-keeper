#include <Arduino.h>

class WaterPump {
private:
    int _pump_pin;
    int _button_pin;
    bool _button_enabled = true;
    bool _blynk_button_enabled = true;
public:
    WaterPump(int pump_pin, int button_pin);

    void begin();
    void turnOn(int secs = 10);

    void syncButton();
    void blockButton();
    void unblockButton();
    bool isEnabled();
    
    void blockBlynkButton();
    void unblockBlynkButton();
    bool isBlynkButtonEnabled();
};
