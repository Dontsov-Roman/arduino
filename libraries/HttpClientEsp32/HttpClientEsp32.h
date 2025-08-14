#ifndef ESP_32_HTTP_CLIENT_H
#define ESP_32_HTTP_CLIENT_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <WiFi.h>
#include <WiFiClient.h>

#include <HTTPClient.h>
#include <IHttpClient.h>
#include <WifiClientEsp32.h>

class HttpClientEsp32 : public IHttpClient
{
public:
    HttpClientEsp32(
        const char *host,
        const char *url);

    HttpClientEsp32(
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
    void setSecure(bool isSecure);

protected:
    WifiClientEsp32 *wifiClient;
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
