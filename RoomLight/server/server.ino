#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightServerMediator.h>

#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define SERIAL_BEGIN 9600
#define SOFTWARE_SERIAL_BEGIN 300
#define SOFTWARE_SERIAL_TIMEOUT 1000
#define GLOBAL_DELAY 1500
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

SoftwareSerial softwareSerial(D5, D7); // RX, TX
TransferStruct transferStruct;
RoomLightSerial roomSerial(&softwareSerial);
WiFiServer server(80);
RoomLightServerMediator mediator(&roomSerial, &server);


void setup() {
  Serial.begin(SERIAL_BEGIN);
  
  softwareSerial.begin(SOFTWARE_SERIAL_BEGIN);
  softwareSerial.setTimeout(SOFTWARE_SERIAL_TIMEOUT);
  mediator.begin(ssid, password);
}

void loop() {
  mediator.toggle();
  delay(GLOBAL_DELAY);
}
