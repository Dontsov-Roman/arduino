#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightServerMediator.h>
#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define SERIAL_BEGIN 9600
#define GLOBAL_DELAY 200
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

SoftwareSerial mySerial(D5, D6); // RX, TX
TransferStruct transferStruct;
RoomLightSerial roomSerial(&mySerial);
WiFiServer server(80);
RoomLightServerMediator serverMediator(&roomSerial, &server);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  mySerial.begin(SERIAL_BEGIN);
  serverMediator.begin(ssid, password);
}

void loop() {
  serverMediator.toggle();
  delay(GLOBAL_DELAY);
}
