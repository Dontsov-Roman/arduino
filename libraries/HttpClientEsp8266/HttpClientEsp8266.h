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
#include <IHttpClient.h>
#include <IWifiClient.h>
#include <WifiClientEsp8266.h>

class HttpClientEsp8266 : public IHttpClient
{
public:
    HttpClientEsp8266(
        const char *host,
        const char *url,
        const char *port);
    void begin();
    ResponseStruct *get();
    ResponseStruct *get(String url);
    ResponseStruct *get(String key, String value);
    ResponseStruct *post(char *body);
    ResponseStruct *post(char *body, String key, String value);
    void setHost(const char *host);
    bool setSecure(bool isSecure);
    void setTimeout(int timeout);

protected:
    WifiClientEsp8266 *wifiClient;
    HTTPClient http;
    WiFiClient client;
    ResponseStruct lastResponse;
    ResponseStruct *request(String url, const char *method, char *body);
    String generateQueryUrl(String url, String key, String value);
    bool isSecure = false;

private:
    char fullUrl[64];
    const char *host;
    const char *port;
    const char *url;
};
#endif
