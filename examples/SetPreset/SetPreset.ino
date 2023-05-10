#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MagicHomeApi.h>

Device Led("IP", 5577); // you may find it in your router settings or get it from MagicHomeApi.Discover

void setup()
{
  Serial.begin(115200);
  Serial.println("Connecting...\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "PASSWORD"); // change it to your ssid and password
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void loop()
{
  Led.SetPresetFunction(40,100);
  delay(10000);
}