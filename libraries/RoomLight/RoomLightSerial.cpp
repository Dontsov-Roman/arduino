#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial) {
    this->serial = softSerial;
    this->transferStruct = TransferStruct{};
    this->transferStruct.command = SwitchOn;
    // this->transferStruct.address = "000.000.0.000";
}

TransferStruct* RoomLightSerial::getTransferStruct() {
    return &this->transferStruct;
}

void RoomLightSerial::read() {
    this->serial->readBytes((byte*)&this->transferStruct, sizeof(transferStruct));
}

void RoomLightSerial::write(RoomLightCommands command) {
    this->transferStruct.command = command;
    this->serial->write((byte*)&transferStruct, sizeof(transferStruct));
}

void RoomLightSerial::write(RoomLightCommands command, String value) {
    this->transferStruct.command = command;
    // strcpy(this->transferStruct.address, address.c_str());
    // this->transferStruct.value = this->stringToChar(value);
    this->transferStruct.value = value;
    this->serial->write((byte*)&transferStruct, sizeof(transferStruct));
}

char RoomLightSerial::stringToChar(String str) {
    char arr[str.length() + 1]; 
    for (int x = 0; x < sizeof(arr); x++) { 
        arr[x] = str[x]; 
    } 
    return arr;
}