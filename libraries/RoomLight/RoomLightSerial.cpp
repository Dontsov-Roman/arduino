#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial) {
    this->serial = softSerial;
    this->transferStruct = TransferStruct{};
    this->transferStruct.command = NothingCommand;
    
    this->startChar = ":";
    this->eolChar = ",";
    this->termChar = ";";

    this->transferStruct.value = "";
    this->receivedChar = "";
    this->lastControlChar = "";
}

TransferStruct* RoomLightSerial::getTransferStruct() {
    return &this->transferStruct;
}


void RoomLightSerial::clearTransferStruct() {
    this->transferStruct.value = "";
    this->transferBuf = "";
    this->receivedChar = "";
    this->lastControlChar = "";
}

void RoomLightSerial::read() {
    if(this->serial->available()) {
        this->clearTransferStruct();
        while (this->serial->available() > 0) {  
            this->transferBuf += (char)this->serial->read();
            delay(2);
        }
        // Serial.println(this->transferBuf);
        for(char &c : this->transferBuf) {
            this->receivedChar = String(c);
            if (this->receivedChar == this->startChar || this->receivedChar == this->eolChar || this->receivedChar == this->termChar) {
                this->lastControlChar = String(c);
                continue;
            }
            if (this->lastControlChar == this->startChar) {
                this->transferStruct.command = c - '0';
            } else if(this->lastControlChar == this->eolChar) {
                this->transferStruct.value += this->receivedChar;
            } else if(this->lastControlChar == this->termChar) {
                break;
            }
        }
        Serial.println("Last command:");
        Serial.println(this->transferStruct.command);
        Serial.println("Last string:");
        Serial.println(this->transferStruct.value);
    }
}

void RoomLightSerial::write(int command) {
    this->transferStruct.command = command;
    this->serial->print(this->startChar + String(command) + this->termChar);
}

void RoomLightSerial::write(int command, String value) {
    this->serial->print(this->startChar + String(command) + this->eolChar + value + this->termChar);
}
