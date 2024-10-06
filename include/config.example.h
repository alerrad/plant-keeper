#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Change to your Blynk config
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// Max and min values of capacitive moisture sensor (might be different for everyone)
const struct MOISTURE_SENSOR {
    constexpr static const int AIR_VALUE = 715;
    constexpr static const int WATER_VALUE = 530;
};

// Max and min values of Water sensor (might be different for everyone)
const struct WATER_LEVEL_SENSOR {
    constexpr static const float MIN_DEPTH = 2;
    constexpr static const float MAX_DEPTH = 5.2;
};

// Change to your WIFI info
const struct WIFI_CONF {
    constexpr static char* uuid = "";
    constexpr static const char* pass = "";
};

// Threshold moisture percentage at which pump turns on
#define MOISTURE_THRESHOLD_PERC 30

#endif