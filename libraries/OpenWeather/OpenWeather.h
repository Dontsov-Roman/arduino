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
    JsonDocument doc;
    const char *appId;
    const char *urlVersion = "/data/2.5/forecast";
    char *lat;
    char *lng;

public:
    OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId);
    OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId, const char *urlVersion);
    void setCoords(char *lat, char *lng);
    void getWeather();
    void loop();
    JsonDocument *getLastJsonDoc();
    void serializeToSerial();
    String getLastWeather();
    String getLastTemperature();
};
#endif
