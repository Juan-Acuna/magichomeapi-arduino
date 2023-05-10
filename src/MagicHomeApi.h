/*
  MagicHomeApi.h - Library for local communicating with MagicHome LED strip controller.
  It support rgbw version only but in future may have an update.
  Created by Anton Panurin(Tommy4chan), October 17, 2022.
*/
#ifndef MagicHomeApi_h
#define MagicHomeApi_h

#include "Device.h"

class MagicHomeApi
{
  public:
    MagicHomeApi();
    Device Discover();
  private:
    char *udpAddress;
    uint16_t udpPort;
    WiFiUDP udp;
    char* FormatIP(IPAddress ip);
};

#endif