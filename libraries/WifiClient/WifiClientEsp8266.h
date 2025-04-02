#ifndef WIFI_CLIENT_ESP_8266_H
#define WIFI_CLIENT_ESP_8266_H
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

#include <IWifiClient.h>

class WifiClientEsp8266 : public IWifiClient
{
public:
    WifiClientEsp8266();
    WifiClientEsp8266(
        const char *wifiSsid,
        const char *wifiPassword);
    void begin();
    bool isConnected();
    String getLocalIP();

protected:
    const char *wifiSsid;
    const char *wifiPassword;
    ESP8266WiFiMulti wifiMulti;
    WiFiClient client;
};
#endif
