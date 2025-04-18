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
#include <GpsData.h>

#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

// #include <GpsSaver.h>
#define AUTHORIZATION_HEADER "Authorization"

class RoomLightServerMediator {
    public:
        RoomLightServerMediator();
        RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server);
        RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server, String token);
        RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server, String token, String thingId);
        void begin(const char* ssid, const char* password);
        void toggle();
    protected:
        void sendWiFiLocalIp();
        bool isLastRequestInvalid;
        const char* getTemplate();
        String getLastGpsData();
        SimpleTimeout simpleTimeout = SimpleTimeout(15000);
        RoomLightSerial *serial;
        GpsData lastGpsData;
        ESP8266HTTPUpdateServer httpUpdater;
        // GpsSaver gpsSaver;
        ESP8266WebServer *server;
        WiFiClient client;
        String localIp;
        String token;
        String thingId;
    private:
        void rootHandler();
        void ledOnHandler();
        void ledOffHandler();
        void movementModeHandler();
        void sendWifiLocalIpHandler();
        void notFoundHandler();
        void setGpsHandler();
        void getGpsHandler();
        bool isAuthenticated();
};
#endif
