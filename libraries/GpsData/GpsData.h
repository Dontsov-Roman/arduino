#ifndef GPS_DATA_H
#define GPS_DATA_H
#define DEFAULT_GPS_READ_DELAY 1000

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
class GpsData {
    public:
        GpsData();
        char* getGpsData();
        char* getGpsDateTime();
        char* getGpsLatLng();
        bool isLocationReady = false;
        bool isDateTimeReady = false;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        double latitude;
        double longitude;
    protected:
        char dateTime[32];
        char lng[16];
        char lat[16];
        char latLng[32];
        char allData[64];
};
#endif
