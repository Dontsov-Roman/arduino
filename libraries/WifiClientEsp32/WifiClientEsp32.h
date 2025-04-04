#ifndef WIFI_CLIENT_ESP_32_H
#define WIFI_CLIENT_ESP_32_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <ResponseStruct.h>

#include <IWifiClient.h>

class WifiClientEsp32 : public IWifiClient
{
public:
    WifiClientEsp32();
    WifiClientEsp32(
        const char *wifiSsid,
        const char *wifiPassword);
    void begin();
    bool isConnected();
    String getLocalIP();

protected:
    const char *wifiSsid;
    const char *wifiPassword;
    WiFiMulti wifiMulti;
    WiFiClient client;
};
#endif
