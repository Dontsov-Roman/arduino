#ifndef GPS_READER_H
#define GPS_READER_H
#define DEFAULT_GPS_READ_DELAY 1000

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

class GpsReader {
    public:
        GpsReader(SoftwareSerial *ss);
        void readGpsData();
        char* getGpsData();
        char* getGpsDateTime();
        char* getGpsLatLng();
    protected:
        TinyGPSPlus gps;
        SoftwareSerial *ss;
        unsigned long int gpsReadDelay;
        char dateTime[32];
        char lng[16];
        char lat[16];
        char latLng[40];
        char allData[72];
};
#endif
