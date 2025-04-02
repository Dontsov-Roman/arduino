#ifndef ESP_8266_HTTP_CLIENT_H
#define ESP_8266_HTTP_CLIENT_H

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
#include <IHttpClient.h>
#include <IWifiClient.h>

class HttpClientEsp8266 : public IHttpClient
{
public:
    HttpClientEsp8266(
        IWifiClient *wifiClient,
        const char *host,
        const char *url,
        const char *port);
    void begin();
    ResponseStruct *get();
    ResponseStruct *get(String key, String value);
    ResponseStruct *post(char *body);
    ResponseStruct *post(char *body, String key, String value);
    void setHost(const char *host);
    String getLocalIP();

protected:
    IWifiClient *wifiClient;
    HTTPClient http;
    WiFiClient client;
    ResponseStruct lastResponse;
    ResponseStruct *request(String url, HTTPMethod method, char *body);
    String generateQueryUrl(String url, String key, String value);
    bool isWifiConnected();

private:
    char fullUrl[64];
    const char *host;
    const char *port;
    const char *url;
};
#endif
