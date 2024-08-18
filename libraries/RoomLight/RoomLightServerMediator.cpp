#include <RoomLightServerMediator.h>
#include <ESP8266WiFi.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

RoomLightServerMediator::RoomLightServerMediator() {}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, WiFiServer *server) {
    this->serial = serial;
    this->server = server;
}

void RoomLightServerMediator::begin(const char *ssid, const char *password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server->begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void RoomLightServerMediator::toggle() {
}
