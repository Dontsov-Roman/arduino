#ifndef GPS_CAR_H
#define GPS_CAR_H
#define DEFAULT_GPS_READ_DELAY 1000

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

class GpsCar {
    public:
        // GpsCar();
        GpsCar(
            SoftwareSerial *ss,
            const char *wifiSsid,
            const char *wifiPassword,
            const char *host,
            const char *url,
            const char *port
        );
        void begin();
        void loop();
    protected:
        TinyGPSPlus gps;
        SoftwareSerial *ss;
        ESP8266WiFiMulti WiFiMulti;
        WiFiClient wifiClient;
        HTTPClient httpClient;
        unsigned long int gpsReadDelay;
        void readGpsData();
        char* getGpsData();
        char* getGpsDateTime();
        char* getGpsLatLng();
        char dateTime[32];
        char lng[16];
        char lat[16];
        char latLng[40];
        char allData[72];
    private:
        const char *wifiSsid;
        const char *wifiPassword;
        const char *host;
        const char *port;
        const char *url;
};
#endif