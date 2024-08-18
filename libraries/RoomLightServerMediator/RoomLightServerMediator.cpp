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

void RoomLightServerMediator::sendWiFiLocalIp() {

}

void RoomLightServerMediator::clientRead() {
    if (!client) { return; }
    Serial.println(F("new client"));

    client.setTimeout(5000);  // default is 1000

    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(F("request: "));
    Serial.println(req);

    // Match the request
    long val;
    if (req.indexOf(F("/gpio/0")) != -1) {
        val = 0;
    } else if (req.indexOf(F("/gpio/1")) != -1) {
        val = 1;
    } else {
        Serial.println(F("invalid request"));
        val = digitalRead(LED_BUILTIN);
    }

    // read/ignore the rest of the request
    // do not client.flush(): it is for output only, see below
    while (client.available()) {
        // byte by byte is not very efficient
        client.read();
    }
}

void RoomLightServerMediator::toggle() {
    client = server->accept();
    this->clientRead();
    this->sendResponse();
}

void RoomLightServerMediator::sendResponse() {
    client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n"));
    client.print(F("</html>"));
}
