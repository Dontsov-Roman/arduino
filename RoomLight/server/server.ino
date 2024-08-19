#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightServerMediator.h>

#ifndef STASSID
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define SERIAL_BEGIN 9600
#define GLOBAL_DELAY 1200
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

SoftwareSerial softwareSerial(D5, D6); // RX, TX
TransferStruct transferStruct;
RoomLightSerial roomSerial(&softwareSerial);
WiFiServer server(80);
RoomLightServerMediator mediator(&roomSerial, &server);

// TransferStruct ts;
// char ipAddr[] = "192.168.0.113";

void setup() {
  Serial.begin(SERIAL_BEGIN);
  
  // ts.command = SetLocalIp;
  // ts.address = "192.168.0.113";
  softwareSerial.begin(SERIAL_BEGIN);
  mediator.begin(ssid, password);
}

void loop() {
  mediator.toggle();
  // Serial.println("TS:");
  // Serial.println(sizeof(ts));
  // Serial.println("Address:");
  // Serial.println(sizeof(ts.address));
  // Serial.println("Char:");
  // Serial.println(sizeof(ipAddr));
  delay(1000);
}
