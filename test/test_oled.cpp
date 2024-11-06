#include <Arduino.h>
#include <unity.h>
#include <OledDisplay.h>

OledDisplay oled;

void test_oled_initialization(void) {
    bool initialized = oled.begin();
    Serial.println(initialized);
    TEST_ASSERT_TRUE_MESSAGE(initialized, "OLED initialization successful");
}

void test_oled_display_text(void) {
    oled.displayMeasurements(70, 70, "Test Message");
    TEST_PASS_MESSAGE("OLED text displayed successfully");
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  
  RUN_TEST(test_oled_initialization);
  RUN_TEST(test_oled_display_text);

  UNITY_END();
}

void loop() {}