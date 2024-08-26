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
#include <GpsData.h>

class GpsReader {
    public:
        GpsReader(SoftwareSerial *ss);
        void readGpsData();
        char* getGpsData();
        bool isReady();
    protected:
        TinyGPSPlus gps;
        GpsData gpsData;
        SoftwareSerial *ss;
        unsigned long gpsReadDelay;
};
#endif
