#include <GpsCar.h>
#include <SoftwareSerial.h>
#include <GpsReader.h>
#include <WifiHttpClient.h>

#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define HOST "192.168.0.113"
#define PORT "80"
#define URL "/gps"
#endif

const char* wifiSsid = STASSID;
const char* wifiPassword = STAPSK;
const char* host = HOST;
const char* port = PORT;
const char* url = URL;

SoftwareSerial ss(D4, D3);
GpsReader gpsReader(&ss);
WifiHttpClient wifiHttpClient(wifiSsid, wifiPassword, host, url, port);
GpsCar gpsCar(&gpsReader, &wifiHttpClient);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  gpsCar.begin();
}

void loop() {
  gpsCar.loop();
}
