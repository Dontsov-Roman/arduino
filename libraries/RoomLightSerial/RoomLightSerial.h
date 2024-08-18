#ifndef ROOMLIGHT_SERIAL_H
#define ROOMLIGHT_SERIAL_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SoftwareSerial.h>
#include "./TransferStruct.h"

class RoomLightSerial {
    public:
        RoomLightSerial();
        RoomLightSerial(SoftwareSerial *softSerial);
        // RoomLightSerial(SoftwareSerial *softSerial, TransferStruct *tStruct);
        void read();
        void write(long code, long value);
    protected:
        SoftwareSerial *serial;
        TransferStruct transferStruct;
        // TransferStruct *transferStruct;
};

#endif
