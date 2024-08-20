#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

RoomLightSerial::RoomLightSerial() {}

RoomLightSerial::RoomLightSerial(SoftwareSerial *softSerial) {
    this->serial = softSerial;
    this->transferStruct = TransferStruct{};
    this->transferStruct.command = SwitchOn;
    this->transferStruct.value = "";
    this->receivedChar = "";
    this->lastControlChar = "";
    this->startChar = ":";
    this->eolChar = ",";
    this->termChar = ";";
}

TransferStruct* RoomLightSerial::getTransferStruct() {
    return &this->transferStruct;
}


void RoomLightSerial::clearTransferStruct() {
    this->transferStruct.value = "";
    this->transferBuf = "";
}

void RoomLightSerial::read() {
    if(this->serial->available()) {
        this->clearTransferStruct();
        while (this->serial->available() > 0) {  
            this->transferBuf += (char)this->serial->read();
            delay(2);
        }
        for(char &c : this->transferBuf) {
            this->receivedChar = String(c);
            if (this->receivedChar == this->startChar || this->receivedChar == this->eolChar || this->receivedChar == this->termChar) {
                this->lastControlChar = String(c);
                continue;
            }
            if (this->lastControlChar == this->startChar) {
                this->transferStruct.command = static_cast<RoomLightCommands>(c);
                Serial.println(this->receivedChar);
                Serial.println(c);
                Serial.println(this->transferStruct.command);
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

void RoomLightSerial::write(RoomLightCommands command) {
    this->transferStruct.command = command;
    this->serial->write((byte*)&transferStruct, sizeof(transferStruct));
}

void RoomLightSerial::write(RoomLightCommands command, String value) {
    this->serial->print(this->startChar + static_cast<String>(command) + this->eolChar + String(value) + this->termChar);
}
