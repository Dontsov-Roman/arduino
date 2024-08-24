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
        int get();
        int post();
    protected:
        ESP8266WiFiMulti wifiMulti;
        WiFiClient wifi;
        HTTPClient http;
        bool isWifiConnected();
    private:
        const char *wifiSsid;
        const char *wifiPassword;
        char *fullUrl;
        const char *host;
        const char *port;
        const char *url;

};
#endif
