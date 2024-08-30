#ifndef GPS_CAR_H
#define GPS_CAR_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <GpsReader.h>
#include <WifiHttpClient.h>
#include <SimpleTimeout.h>

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
        SimpleTimeout timeout;
        char* gpsQueryKey;
};
#endif