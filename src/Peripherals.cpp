#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"


DHT dht(DHT_PIN , DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) {
  return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}


void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN); // 0 to 4095
    int raw_voltage = analogRead(VOLTAGE_PIN); // 0 to 4095
    
   voltage = mapFloat(raw_voltage , 0 , 4095 , 0 , 250);

   if(bayStatus == "CHARGING")
   {
   current = mapFloat(raw_current , 0 , 4095 , 0 , 32);
   } 
   power=voltage*current ;
    
    
    //to read temperature 

    float t  = dht.readTemperature(DHT_PIN );
    if(!(isnan(t)))temperature = t;
     
    
   

}
bool plugin_flag = 1;
bool plugout_flag = 1;

void plug_status(void)
{
   bool pluginReading = digitalRead(BTN_PLUGIN);
   
   // detect the sw is pressed
   if (pluginReading == LOW && plugin_flag)
      {  
        // plug in switch is pressed
        plugin_flag = 0;

        // change bay_status FREE to charging
        if (bayStatus == "FREE")
        {
          bayStatus="CHARGING";
          Serial.println("Bay 1 plugin detected,Bay is charging");
          digitalWrite(RELAY_PIN,HIGH);
        }
        //update leds
      }
   if (pluginReading == HIGH)
   {
      plugin_flag = 1;
   }   


   bool plugoutReading = digitalRead(BTN_PLUGOUT);
   
   // detect the sw is pressed
   if (plugoutReading == LOW && plugout_flag)
      {  
        // plug in switch is pressed
        plugout_flag = 0;

        // change bay_status charging to FREE
        if (bayStatus == "CHARGING")
        {
          bayStatus="FREE";
          Serial.println("Bay 1 plugout detected, Bay is Free");
        }
        //update leds
      } 
   if (plugout_flag == HIGH)
     {
      plugout_flag = 1;
     }
   
}
void update_led_status(void)
{
  if(bayStatus == "FREE")
  {
   digitalWrite(LED_GREEN,HIGH);
   digitalWrite(LED_YELLOW,LOW);
  }
  else
  {
   digitalWrite(LED_GREEN,LOW);
   digitalWrite(LED_YELLOW,HIGH);

  }
}
