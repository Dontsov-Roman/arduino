#ifndef I_HTTP_CLIENT_H
#define I_HTTP_CLIENT_H

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
class IHttpClient
{
public:
    virtual void begin();
    virtual ResponseStruct *get();
    virtual ResponseStruct *get(String key, String value);
    virtual ResponseStruct *post(char *body);
    virtual ResponseStruct *post(char *body, String key, String value);
    virtual void setHost(const char *host);
    virtual ResponseStruct *request(String url, HTTPMethod method, char *body);
    virtual String generateQueryUrl(String url, String key, String value);
};
#endif
