#ifndef GPS_CAR_H
#define GPS_CAR_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <TinyGPSPlus.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <GpsReader.h>
#include <WifiHttpClient.h>

class GpsCar {
    public:
        GpsCar(
            GpsReader *gpsReader,
            WifiHttpClient *client
        );
        void begin();
        void loop();
    protected:
        GpsReader *gpsReader;
        WifiHttpClient *client;
};
#endif