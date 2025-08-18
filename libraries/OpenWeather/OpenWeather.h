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
#include <UrlBuilder.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

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
    double temp_min;
    double temp_max;
    int cnt = 3;

protected:
    void findMinMaxTemp();

public:
    OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId);
    OpenWeather(IHttpClient *client, SimpleTimeout *timeout, const char *appId, const char *urlVersion, int cnt);
    void setCoords(char *lat, char *lng);
    void getWeather();
    void loop();
    JsonDocument *getLastJsonDoc();
    void serializeToSerial();
    char *getLastWeather();
    char *getLastTemperature();
    void begin();
    int getCount();
    void setCount(int count);
};
#endif
