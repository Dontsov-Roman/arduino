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
        RoomLightSerial(SoftwareSerial *softSerial, TransferStruct *rStruct, TransferStruct *wStruct);
        void read();
        void write();
    protected:
        SoftwareSerial *serial;
        TransferStruct *readStruct;
        TransferStruct *writeStruct;
};

#endif
