
#include "Arduino.h"
#include <WiFiClient.h>
#include <WiFiUdp.h>

class Device{
  public:
    struct DeviceStatus{
      uint8_t type;
      bool on;
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t ww;
      uint8_t cw;
    };
    Device();
    Device(char *host_led, uint16_t port_led);
    DeviceStatus GetSatus();
    void TurnOn();
    void TurnOff();
    void Switch();
    void SetColor(int r, int g, int b, int w, int brightness);
    void SetColorARGB(int r, int g, int b, int brightness);
    void SetPresetFunction(int f_number, int speed);
    void SetPresetFunctionARGB(int f_number, int speed, int brightness);
    int BrightnessLevel(int value, int brightness);
    bool IsValid();
  private:
    void ClientConnect();
    void ClientDisconnect();
    void SendData(byte data[], int len);
    int CheckRange(int min, int max, int value);
    WiFiClient client;
    char *host;
    uint16_t port;
    bool valid;
};