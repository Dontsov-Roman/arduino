#include "RoomLightSerial.h"

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial) {
    this->serial = softSerial;
    this->transferStruct = TransferStruct{};
    // this->transferStruct = tStruct;
}

void RoomLightSerial::read() {
    this->serial->readBytes((byte*)&this->transferStruct, sizeof(transferStruct));
    Serial.println(sizeof(transferStruct));
    Serial.println(this->transferStruct.code);
    Serial.println(this->transferStruct.value);
}

void RoomLightSerial::write(long code, long value) {
    transferStruct.code = code;
    transferStruct.value = value;
    Serial.println(sizeof(transferStruct));
    this->serial->write((byte*)&this->transferStruct, sizeof(transferStruct));
}
