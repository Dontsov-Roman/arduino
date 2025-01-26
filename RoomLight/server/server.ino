#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightServerMediator.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define SERIAL_BEGIN 115200
#define SOFTWARE_SERIAL_BEGIN 300
#define SOFTWARE_SERIAL_TIMEOUT 1000
#define GLOBAL_DELAY 1500
#define AUTH_TOKEN "Bearer ACCESS_TOKEN_ROMAN_DONTSOV"
#define DEVICE_ID "ce569ed6-1311-4dfe-950d-68305a575fd3";
#define THING_ID "ce569ed6-1311-4dfe-950d-68305a575fd3";
#define SECRET_KEY "QG8hrviPPHR5XzSnJMYnggsIS";
#endif


const char* ssid = STASSID;
const char* password = STAPSK;
const String token = AUTH_TOKEN;
const String thingId = THING_ID;

SoftwareSerial softwareSerial(D5, D7); // RX, TX
TransferStruct transferStruct;
RoomLightSerial roomSerial(&softwareSerial);
ESP8266WebServer server(80);
RoomLightServerMediator mediator(&roomSerial, &server, token, thingId);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  
  softwareSerial.begin(SOFTWARE_SERIAL_BEGIN);
  softwareSerial.setTimeout(SOFTWARE_SERIAL_TIMEOUT);
  mediator.begin(ssid, password);
}

void loop() {
  mediator.toggle();
  // delay(GLOBAL_DELAY);
}
