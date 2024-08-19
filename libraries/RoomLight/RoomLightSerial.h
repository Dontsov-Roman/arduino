#ifndef ROOMLIGHT_SERIAL_H
#define ROOMLIGHT_SERIAL_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SoftwareSerial.h>
#include "./TransferStruct.h"
#include "./RoomLightCommands.h"

class RoomLightSerial {
    public:
        RoomLightSerial();
        RoomLightSerial(SoftwareSerial *softSerial);
        TransferStruct* getTransferStruct();
        void read();
        void write(RoomLightCommands command);
        void write(RoomLightCommands command, long value);
        void write(RoomLightCommands command, String address);
    protected:
        SoftwareSerial *serial;
        TransferStruct transferStruct;
};

#endif
