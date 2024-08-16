#include "RoomLightSerial.h"

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial, TransferStruct *rStruct, TransferStruct *wStruct) {
    this->serial = softSerial;
    this->readStruct = rStruct;
    this->writeStruct = wStruct;
}

void RoomLightSerial::read() {
}

void RoomLightSerial::write() {
}
