#ifndef OPEN_WEATHER_H
#define OPEN_WEATHER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ArduinoJson.h>
#include <SimpleTimeout.h>
#include <IHttpClient.h>

class OpenWeather
{
private:
    SimpleTimeout *timeout;
    IHttpClient *client;
    const char *appId;
    JsonDocument doc;
    char *lat;
    char *lng;

public:
    OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId);
    void setCoords(char *lat, char *lng);
    void getWeather();
    JsonDocument *getLastJsonDoc();
};
#endif
