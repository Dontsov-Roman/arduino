#include "RoomLightSerial.h"
#include "RoomLightCommands.h"

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial) {
    this->serial = softSerial;
    this->transferStruct = TransferStruct{};
}

TransferStruct* RoomLightSerial::getTransferStruct() {
    return &this->transferStruct;
}

void RoomLightSerial::read() {
    this->serial->readBytes((byte*)&this->transferStruct, sizeof(transferStruct));
    Serial.println(sizeof(transferStruct));
    Serial.println(this->transferStruct.command);
    Serial.println(this->transferStruct.value);
}

void RoomLightSerial::write(RoomLightCommands command, long value) {
    this->transferStruct.command = command;
    this->transferStruct.value = value;
    Serial.println(sizeof(transferStruct));
    this->serial->write((byte*)&this->transferStruct, sizeof(transferStruct));
}
