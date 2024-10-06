#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class OledDisplay {
private:
    Adafruit_SSD1306 _display;
public:
    OledDisplay(/* args */);
    
    bool begin();
    void connectingWiFi();
    void displayMeasurements(uint8_t water_level, uint8_t moisture_level, const String& status);
};
