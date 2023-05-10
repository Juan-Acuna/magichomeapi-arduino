#include "MagicHomeApi.h"

MagicHomeApi::MagicHomeApi(){
  udpAddress = "255.255.255.255";
  udpPort = 48899;
  udp.begin(udpPort);
}

Device MagicHomeApi::Discover(){
  udp.beginPacket(udpAddress, udpPort);
  udp.print("HF-A11ASSISTHREAD");
  udp.endPacket();
  delay(20);
  for(size_t i = 0;i<10;i++){
    int packetSize = udp.parsePacket();
    if (packetSize){
      return Device(FormatIP(udp.remoteIP()), 5577);
    }
    delay(10);
  }
  return Device();
}
char* MagicHomeApi::FormatIP(IPAddress ip){
  char* nip = new char[40]();
  sprintf(nip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return nip;
}