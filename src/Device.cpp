#include "Device.h"

Device::Device()
{
  valid = false;
}

Device::Device(char *host_led, uint16_t port_led)
{
  valid = true;
  host = host_led;
  port = port_led;
}

void Device::ClientConnect(){
  while(!client.connect(host, port))
  {
    Serial.println("Connection to host failed");
    delay(1000);
  }
}

void Device::ClientDisconnect(){
  client.stop();
}

void Device::TurnOn(){
  if(!IsValid())
    return;
  int len = 4;
  byte b[len] = {0x71, 0x23, 0x0F, 0xA3};
  SendData(b, len);
}

void Device::TurnOff(){
  if(!IsValid())
    return;
  int len = 4;
  byte b[len] = {0x71, 0x24, 0x0F, 0xA4};
  SendData(b, len);
}

void Device::Switch(){
  if(!IsValid())
    return;
  int len = 4;
  byte b[len] = {0x71, 0x24, 0x0F, 0xA4};
  Device::DeviceStatus ds = GetSatus();
  if(!ds.on){
    b[1] = 0x23;
    b[3] = 0xA3;
  }
  SendData(b, len);
}

void Device::SetColor(int r, int g, int b, int w, int brightness){
  if(!IsValid())
    return;
  int len = 8;
  byte data[len] = {0x31, BrightnessLevel(CheckRange(0, 255, r), brightness), BrightnessLevel(CheckRange(0, 255, g), brightness), 
  BrightnessLevel(CheckRange(0, 255, b), brightness), BrightnessLevel(CheckRange(0, 255, w), brightness), 0x00, 0x0f, 0x00};
  int sum = 0;
  for(int i = 0; i < 7; i++){
    sum += data[i];
  }
  data[7] = sum&0xFF;
  SendData(data, len);
}

void Device::SetColorARGB(int r, int g, int b, int brightness){
  if(!IsValid())
    return;
  int len = 13;
  byte data[len] = {0x41,0x01, BrightnessLevel(CheckRange(0, 255, r), brightness), BrightnessLevel(CheckRange(0, 255, g), brightness), 
  BrightnessLevel(CheckRange(0, 255, b), brightness),0x00,0x00,0x00,0x32,0x00,0x00,0xf0,0xe4};
  int sum = 0;
  for(int i = 0; i < 7; i++){
    sum += data[i];
  }
  data[13] = sum&0xFF;
  SendData(data, len);
}

void Device::SetPresetFunction(int f_number, int speed){
  if(!IsValid())
    return;
  int len = 5;
  byte data[len] = {0x61, CheckRange(37, 56, f_number), CheckRange(0, 100, 100-speed), 0x0F, 0x00};
  int sum = 0;
  for(int i = 0; i < 4; i++){
    sum += data[i];
  }
  data[4] = sum&0xFF;
  SendData(data, len);
}

void Device::SetPresetFunctionARGB(int f_number, int speed, int brightness){
  if(!IsValid())
    return;
  int len = 5;
  byte data[len] = {0x42, CheckRange(01, 74, f_number), CheckRange(0, 100, 100-speed), brightness, 0x1c};
  int sum = 0;
  for(int i = 0; i < 4; i++){
    sum += data[i];
  }
  data[4] = sum&0xFF;
  SendData(data, len);
}

Device::DeviceStatus Device::GetSatus(){
  if(!IsValid())
    return Device::DeviceStatus();
  int len = 3;
  byte b[len] = {0x81, 0x8a, 0x8b};
  ClientConnect();
  client.write(b, len);
  delay(15);
  char* resp = new char[40];
  for(int i=0;i<40;i++){
    char x = client.read();
    if(x==-1){
      resp[i]='\0';
      break;
    }else{
      resp[i]=x;
    }
  }
  ClientDisconnect();
  Device::DeviceStatus ds;
  ds.type = resp[1];
  ds.on = resp[2]==0x23;
  ds.r = resp[6];
  ds.g = resp[7];
  ds.b = resp[8];
  ds.ww = resp[9];
  ds.cw = resp[11];
  return ds;
}

void Device::SendData(byte data[], int len){
  if(!IsValid())
    return;
  ClientConnect();
  client.write(data, len);
  ClientDisconnect();
}

int Device::CheckRange(int min, int max, int value){
  if(!IsValid())
    return 0;
  if(min > value){
    value = min;
  }
  else if(max < value){
    value = max;    
  }

  return value;
}

int Device::BrightnessLevel(int value, int brightness){
  if(!IsValid())
    return 0;
  return (value/100) * brightness;
}

bool Device::IsValid(){
  if(!valid)
    Serial.println("Invalid Led!");
  return valid;
}
