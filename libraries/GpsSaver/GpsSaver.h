#ifndef GPS_SAVER_H
#define GPS_SAVER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
// #include <cppQueue.h>

class GpsSaver {
    public:
        GpsSaver();
        void addData(String data);
    protected:
        // cppQueue data;
};
#endif
