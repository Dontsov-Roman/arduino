#include <RoomLightServerMediator.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <ResponseCodes.h>

ResponseCodes responseCodes;
RoomLightServerMediator::RoomLightServerMediator() {
    this->isLastRequestInvalid = false;
}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server) {
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
    this->server->on("/led/1", std::bind(&RoomLightServerMediator::ledOnHandler, this));
    this->server->on("/led/0", std::bind(&RoomLightServerMediator::ledOffHandler, this));
    this->server->on("/movement", std::bind(&RoomLightServerMediator::movementModeHandler, this));
    this->server->on("/sendlocalip", std::bind(&RoomLightServerMediator::sendWifiLocalIpHandler, this));
    this->server->on("/set-gps", HTTP_POST, std::bind(&RoomLightServerMediator::setGpsHandler, this));
    this->server->onNotFound(std::bind(&RoomLightServerMediator::notFoundHandler, this));

    // Print the IP address
    Serial.println(WiFi.localIP());
}

void RoomLightServerMediator::ledOnHandler() {
    this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
    this->serial->write(SwitchOnCommand);
}

void RoomLightServerMediator::ledOffHandler() {
    this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
    this->serial->write(SwitchOffCommand);
}


void RoomLightServerMediator::movementModeHandler() {
    this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
    this->serial->write(MovementModeCommand);
}

void RoomLightServerMediator::sendWifiLocalIpHandler() {
    this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
    this->sendWiFiLocalIp();
}

void RoomLightServerMediator::setGpsHandler() {
    this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
    // this->serial->write(SwitchOnCommand);
    // TODO: implement saving date, Time, Lat, Lng;
}

void RoomLightServerMediator::notFoundHandler() {
    this->server->send(responseCodes.notFoundCode, responseCodes.textPlain, "");
    // this->serial->write(SwitchOnCommand);
}

void RoomLightServerMediator::sendWiFiLocalIp() {
    this->serial->write(SetLocalIpCommand, WiFi.localIP().toString());
}

// void RoomLightServerMediator::clientRead() {
//     this->client = server->accept();
//     if (!client) { return; }

//     client.setTimeout(5000);  // default is 1000

//     String req = client.readStringUntil('\r');

//     // Match the request
//     this->isLastRequestInvalid = false;
//     if (req.indexOf(F("/led/0")) != -1) {
//         this->serial->write(SwitchOffCommand);
//     } else if (req.indexOf(F("/led/1")) != -1) {
//         this->serial->write(SwitchOnCommand);
//     } else if (req.indexOf(F("/movement")) != -1) {
//         this->serial->write(MovementModeCommand);
//     } else if (req.indexOf(F("/sendlocalip")) != -1) {
//         this->sendWiFiLocalIp();
//     } else {
//         this->isLastRequestInvalid = true;
//     }

//     // read/ignore the rest of the request
//     while (client.available()) {
//         // byte by byte is not very efficient
//         client.read();
//     }
// }

void RoomLightServerMediator::toggle() {
    this->server->handleClient();
    this->client = server->client();
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
