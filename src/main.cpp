#include <Arduino.h>
#include <WiFi.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "network.h"
#include "telemetry.h"



void setup()
{

    Serial.begin(115200);
    dht.begin();  // initialise sesnor
    pinMode(BTN_PLUGIN,INPUT_PULLUP);
    pinMode(BTN_PLUGOUT,INPUT_PULLUP);
    pinMode(RELAY_PIN,OUTPUT);
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_YELLOW,OUTPUT);
    pinMode(LED_RED,OUTPUT);
    connectWiFi();
    
 // Configure MQTT server
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);

    connectMQTT();


}
unsigned long now;
unsigned long last_print;

void loop()
{
    //push vals every 5 sec
    now = millis();
    if((now - last_print) > 5000)
    {
        last_print = now;
        sample_sensor();

        publishTelemetry();  


    }
    plug_status();
    update_led_status();

    
}

 