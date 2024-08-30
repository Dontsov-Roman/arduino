#ifndef GPS_DATA_H
#define GPS_DATA_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SimpleParser.h>

class GpsData {
    public:
        GpsData();
        char* getGpsData();
        char* getGpsDateTime();
        char* getGpsLatLng();
        void parse(String str);
        bool isLocationReady = false;
        bool isDateTimeReady = false;
        long year;
        long month;
        long day;
        long hour;
        long minute;
        long second;
        double latitude;
        double longitude;
    protected:
        char dateTime[32];
        char lng[16];
        char lat[16];
        char latLng[32];
        char allData[64];
        SimpleParser commandParser = SimpleParser(',');
        SimpleParser dateParser = SimpleParser('/');
        SimpleParser timeParser = SimpleParser(':');
};
#endif
