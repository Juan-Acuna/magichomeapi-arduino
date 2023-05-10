/* 
  This example includes the "Discover" function.
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "MagicHomeApi.h"

const char* IP = "192.168.1.2";
const char* SSID = "Wifi casa 3";
const char* PWD = "unaklabe";

int btnA = 15;
Device led;

void setup()
{
  delay(500);
  pinMode(btnA, INPUT);
  Serial.begin(115200);
  Serial.println("Connecting...\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
  MagicHomeApi api;
  do{
    led = api.Discover();
  }while(!led.IsValid());
}

void loop()
{
  if(digitalRead(btnA)){
    led.Switch();
    while(digitalRead(btnA)){
      delay(10);
    }
  }
}