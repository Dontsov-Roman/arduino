#ifndef WIFI_HTTP_CLIENT_H
#define WIFI_HTTP_CLIENT_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ResponseStruct.h>
#include <ESP8266WebServer.h>

class WifiHttpClient {
    public:
        WifiHttpClient(
            const char *wifiSsid,
            const char *wifiPassword,
            const char *host,
            const char *url,
            const char *port
        );
        void begin();
        ResponseStruct* get();
        ResponseStruct* get(char *key, char *value);
        ResponseStruct* post(char *body);
        ResponseStruct* post(char *body, char *key, char *value);
        ResponseStruct* post(char *body, const char *key, char *value);
        bool isWifiConnected();
        void setHost(const char *host);
    protected:
        ESP8266WiFiMulti wifiMulti;
        WiFiClient client;
        HTTPClient http;
        ResponseStruct lastResponse;
        ResponseStruct* request(char *url, HTTPMethod method, char *body);
        char* generateQueryUrl(char *url, char *key, char *value);
        char* generateQueryUrl(char *url, const char *key, char *value);
    private:
        const char *wifiSsid;
        const char *wifiPassword;
        char fullUrl[64];
        const char *host;
        const char *port;
        const char *url;

};
#endif
