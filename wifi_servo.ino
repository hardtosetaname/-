#include <ESP8266WiFi.h>
#include <Servo.h>
Servo servox;
Servo servoy;

const char* Ssid     = "your_wifi-id";
const char* Password = "your_password";

const char* Server = "192.168.2.175";
const int Port = 2666;

bool Flag = false;
WiFiClient client;

void setup() {
  WiFi.begin(Ssid, Password);
  servox.attach(2);
  servoy.attach(4);
}

void loop() {
  unsigned char asa[3] = {0};
  if(Flag==false && WiFi.status()==WL_CONNECTED)
  {
    Flag=true;
    client.connect(Server, Port);
  }
  while(client.available()){ 
    client.read(asa,2);
    servox.write(asa[0]);
    servoy.write(asa[1]);
  }
}
