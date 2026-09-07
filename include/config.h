#ifndef CONFIG_H
#define CONFIG_H

// ---------------------------------------------------------------------
// Pin configuration — SRS Section 8.1
// ---------------------------------------------------------------------
#define VOLTAGE_PIN   34
#define CURRENT_PIN   35
#define DHT_PIN       15
#define RELAY_PIN     26
#define BTN_PLUGIN    32
#define BTN_PLUGOUT   33
#define LED_GREEN     18
#define LED_YELLOW    19
#define LED_RED       21
#define DHT_TYPE DHT22



static const char* WIFI_SSID = "Wokwi-GUEST";
static const char* WIFI_PASS = "";

// ---------------- ThingsBoard Details ----------------
static const char* MQTT_SERVER = "mqtt.thingsboard.cloud";
static const int MQTT_PORT = 1883;

static const char* BAY_ID = "BAY1";
static const char*TB_TOKEN ="foxsg0zkc79qyxap82l1";

#endif
