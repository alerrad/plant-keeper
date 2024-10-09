#include <OledDisplay.h>

OledDisplay::OledDisplay() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

bool OledDisplay::begin() {
    if (!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        return false;
    _display.clearDisplay();
    _display.setTextWrap(true);
    _display.setTextColor(SSD1306_WHITE);
    _display.display();
    return true;
}

void OledDisplay::connectingWiFi() {
    _display.clearDisplay();
    _display.setCursor(0, 2);
    _display.setTextSize(2);
    _display.print("Connecting\nto WiFi...");
    _display.display();
}

void OledDisplay::displayMeasurements(uint8_t water_level, uint8_t moisture_level, const String &status) {
    _display.clearDisplay();
    _display.setTextSize(1, 2);
    _display.setCursor(0, 0);
    _display.printf("Water lvl: %d%%\nMoisture lvl: %d%%\nStatus: %s", water_level, moisture_level, status);
    _display.display();
}