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
  this->sendWiFiLocalIp();
}

void RoomLightServerMediator::sendWiFiLocalIp() {
    this->serial->write(SetLocalIp, WiFi.localIP().toString());
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
    if (req.indexOf(F("/led/0")) != -1) {
        this->serial->write(SwitchOn);
    } else if (req.indexOf(F("/led/1")) != -1) {
        this->serial->write(SwitchOff);
    } else if (req.indexOf(F("/movement")) != -1) {
        this->serial->write(MovementMode);
    } else {
        Serial.println(F("invalid request"));
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
    // Switch on link
    client.print(F("<br><br><a href='http://"));
    client.print(WiFi.localIP());
    client.print(F("/led/1'>Switch On</a>"));
    // Switch off link
    client.print(F("<br><br><a href='http://"));
    client.print(WiFi.localIP());
    client.print(F("/led/0'>Switch Off</a>"));
    // Movement Mode
    client.print(F("<br><br><a href='http://"));
    client.print(WiFi.localIP());
    client.print(F("/movement'>Switch Off</a>"));
    client.print(F("</html>"));
}
