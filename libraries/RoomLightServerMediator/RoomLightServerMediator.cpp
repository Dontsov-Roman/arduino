#include <RoomLightServerMediator.h>
#include <ESP8266WiFi.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

RoomLightServerMediator::RoomLightServerMediator() {
    this->isLastRequestInvalid = false;
}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, WiFiServer *server) {
    this->serial = serial;
    this->server = server;
    this->isLastRequestInvalid = false;
    this->simpleTimeout = SimpleTimeout(15000);
}

void RoomLightServerMediator::begin(const char *ssid, const char *password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(F("."));
    }

    // Start the server
    server->begin();

    // Print the IP address
    Serial.println(WiFi.localIP());

void RoomLightServerMediator::sendWiFiLocalIp() {
    this->serial->write(SetLocalIpCommand, WiFi.localIP().toString());
}

void RoomLightServerMediator::clientRead() {
    this->client = server->accept();
    if (!client) { return; }

    client.setTimeout(5000);  // default is 1000

    String req = client.readStringUntil('\r');

    // Match the request
    this->isLastRequestInvalid = false;
    if (req.indexOf(F("/led/0")) != -1) {
        this->serial->write(SwitchOnCommand);
    } else if (req.indexOf(F("/led/1")) != -1) {
        this->serial->write(SwitchOffCommand);
    } else if (req.indexOf(F("/movement")) != -1) {
        this->serial->write(MovementModeCommand);
    } else if (req.indexOf(F("/sendlocalip")) != -1) {
        this->sendWiFiLocalIp();
    } else {
        this->isLastRequestInvalid = true;
    }

    // read/ignore the rest of the request
    while (client.available()) {
        // byte by byte is not very efficient
        client.read();
    }
}

void RoomLightServerMediator::toggle() {
    this->clientRead();
    this->sendResponse();
    if (this->simpleTimeout.checkTimeout()){
        this->sendWiFiLocalIp();
    }
}

void RoomLightServerMediator::sendResponse() {
    client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n"));
    if(this->isLastRequestInvalid) {
        client.print(F("<br><br><span style='{color: red}'>Last request was invalid</span>"));
    }
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
    client.print(F("/movement'>Movement Mode</a>"));
    // Movement Mode
    client.print(F("<br><br><a href='http://"));
    client.print(WiFi.localIP());
    client.print(F("/sendlocalip'>Send ip</a>"));
    // Close html
    client.print(F("</html>"));
}
