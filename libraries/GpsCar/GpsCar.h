#ifndef GPS_CAR_H
#define GPS_CAR_H
#define GPS_QUERY_KEY "gps"
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <GpsReader.h>
#include <WifiHttpClient.h>
#include <SimpleTimeout.h>
#include <ISimpleDisplay.h>

class GpsCar {
    public:
        GpsCar(
            GpsReader *gpsReader,
            WifiHttpClient *client,
            ISimpleDisplay *display
        );
        void begin();
        void loop();
    protected:
        GpsReader *gpsReader;
        WifiHttpClient *client;
        ISimpleDisplay *display;
        SimpleTimeout timeout = SimpleTimeout(10000);

        const char* gpsQueryKey = GPS_QUERY_KEY;
        char* gpsData;
        char* gpsDateTime;
        char* gpsLatLng;
};
#endif