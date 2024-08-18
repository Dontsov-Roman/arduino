#ifndef ROOM_LIGHT_SERVER_MEDIATOR_H
#define ROOM_LIGHT_SERVER_MEDIATOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ESP8266WiFi.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

class RoomLightServerMediator {
    public:
        RoomLightServerMediator();
        RoomLightServerMediator(RoomLightSerial *serial, WiFiServer *server);
        void begin(const char* ssid, const char* password);
        void toggle();
    protected:
        RoomLightSerial *serial;
        WiFiServer *server;
        WiFiClient client;
        void clientRead();
        void sendResponse();
        void sendWiFiLocalIp();
};
#endif
