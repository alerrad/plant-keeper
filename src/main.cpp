#include <config.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

// Custom libs
#include <MoistureSensor.h>
#include <WaterSensor.h>
#include <OledDisplay.h>
#include <WaterPump.h>


BlynkTimer timer;
MoistureSensor moistureSensor(A0, MOISTURE_SENSOR::AIR_VALUE, MOISTURE_SENSOR::WATER_VALUE);
WaterSensor waterSensor(D6, D7, WATER_LEVEL_SENSOR::MIN_DEPTH, WATER_LEVEL_SENSOR::MAX_DEPTH);
WaterPump waterPump(D5, D4);
OledDisplay oled;


// Blynk dashboard button
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V3);
}
BLYNK_WRITE(V3) {
  if (waterPump.isBlynkButtonEnabled()) {
    if (param.asInt() && waterSensor.getWaterLevel() > WATER_LEVEL_THRESHOLD_PERC) {
      digitalWrite(D5, HIGH);
      waterPump.blockButton();
    } else {
      digitalWrite(D5, LOW);
      waterPump.unblockButton();
    }
  }
}

// Function to handle sensor readings and display updates
void sensorReadingsTimer() {
  uint8_t moisture_lvl = moistureSensor.getMoistureLevel();
  uint8_t water_lvl = waterSensor.getWaterLevel();

  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    oled.displayMeasurements(water_lvl, moisture_lvl, "online");
    Blynk.virtualWrite(V0, moisture_lvl);
    Blynk.virtualWrite(V1, water_lvl);
  } else {
    oled.displayMeasurements(water_lvl, moisture_lvl, "offline");
  }

  if (moisture_lvl <= MOISTURE_THRESHOLD_PERC && water_lvl > WATER_LEVEL_THRESHOLD_PERC) {
    oled.displayMeasurements(water_lvl, moisture_lvl, "watering");
    Blynk.virtualWrite(V3, HIGH);
    waterPump.turnOn(10);
    Blynk.virtualWrite(V3, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  moistureSensor.begin();
  waterSensor.begin();
  oled.begin();
  waterPump.begin();

  WiFi.begin(WIFI_CONF::SSID, WIFI_CONF::PASS);

  unsigned long start = millis();

  // 10 seconds to connect, else run without Blynk
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    oled.connectingWiFi();
    delay(500);
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_CONF::SSID, WIFI_CONF::PASS);
  }

  // set interval for sensor updates
  timer.setInterval(10000L, sensorReadingsTimer);
  
  delay(1500);
}

void loop() {
  waterPump.syncButton();
  timer.run();
  Blynk.run();
}
