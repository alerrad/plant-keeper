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
WaterSensor waterSensor(D6, D7, WATER_LEVEL_SENSOR::MIN_VALUE, WATER_LEVEL_SENSOR::MAX_VALUE);
OledDisplay oled;
WaterPump waterPump(D5);

// Blynk dashboard button
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V3);
  // Blynk.syncAll();
}
BLYNK_WRITE(V3) {
  if (param.asInt())
    digitalWrite(D5, HIGH);
  else
    digitalWrite(D5, LOW);
}

void sensorReadingsTimer() {
  uint8_t moisture_lvl = moistureSensor.getMoistureLevel();
  uint8_t water_lvl = waterSensor.getWaterLevel();
  oled.displayMeasurements(water_lvl, moisture_lvl, "online");
  Blynk.virtualWrite(V0, moisture_lvl);
  Blynk.virtualWrite(V1, water_lvl);

  if (moisture_lvl <= MOISTURE_THRESHOLD_PERC && water_lvl > 10) {
    waterPump.turnOn(10);
  }
}

void setup() {
  Serial.begin(115200);

  moistureSensor.begin();
  waterSensor.begin();
  oled.begin();
  waterPump.begin();

  WiFi.begin(WIFI_CONF::SSID, WIFI_CONF::PASS);

  while (WiFi.status() != WL_CONNECTED) {
    oled.connectingWiFi();
    delay(500);
  }
  // Once Wifi connected, connect to blynk dashboard
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_CONF::SSID, WIFI_CONF::PASS);

  // set interval for sensor updates
  timer.setInterval(10000L, sensorReadingsTimer);
  
  delay(1500);
}

void loop() {
  timer.run();
  Blynk.run();
}
