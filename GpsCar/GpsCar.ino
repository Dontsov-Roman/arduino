#include <GpsCar.h>
#include <SoftwareSerial.h>

#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define HOST "192.168.0.113"
#define PORT "80"
#define URL "/gps"
#endif

SoftwareSerial ss(D4, D3);
const char* wifiSsid = STASSID;
const char* wifiPassword = STAPSK;
const char* host = HOST;
const char* port = PORT;
const char* url = URL;

GpsCar gpsCar(&ss, wifiSsid, wifiPassword, host, url, port);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  gpsCar.begin();
}

void loop() {
  gpsCar.loop();

}
