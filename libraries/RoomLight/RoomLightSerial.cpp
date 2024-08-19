#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

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

}

void RoomLightSerial::write(RoomLightCommands command) {
    this->transferStruct.command = command;
    this->serial->write((byte*)&this->transferStruct, sizeof(transferStruct));
}

void RoomLightSerial::write(RoomLightCommands command, long value) {
    this->transferStruct.command = command;
    this->transferStruct.value = value;
    this->serial->write((byte*)&this->transferStruct, sizeof(transferStruct));
}

void RoomLightSerial::write(RoomLightCommands command, String address) {
    this->transferStruct.command = command;
    this->transferStruct.address = address;
    this->serial->write((byte*)&this->transferStruct, sizeof(transferStruct));
}