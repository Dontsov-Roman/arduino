#ifndef ROOM_LIGHT_SERVER_MEDIATOR_H
#define ROOM_LIGHT_SERVER_MEDIATOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <SimpleTimeout.h>
#include <ResponseCodes.h>

class RoomLightServerMediator {
    public:
        RoomLightServerMediator();
        RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server);
        void begin(const char* ssid, const char* password);
        void toggle();
    protected:
        void sendWiFiLocalIp();
        bool isLastRequestInvalid;
        const char* getTemplate();
        SimpleTimeout simpleTimeout;
        RoomLightSerial *serial;
        ESP8266WebServer *server;
        WiFiClient client;
        String textPlain = "text/plain";
        int okCode = 200;
        int notFoundCode = 200;
        String localIp;
    private:
        void rootHandler();
        void ledOnHandler();
        void ledOffHandler();
        void movementModeHandler();
        void setGpsHandler();
        void sendWifiLocalIpHandler();
        void notFoundHandler();
};
#endif
