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
}

void RoomLightSerial::read() {
    if(this->serial->available()) {
        this->transferBuf = "";
        while (this->serial->available() > 0) {         // ПОКА есть что то на вход    
            this->transferBuf += (char)this->serial->read();        // забиваем строку принятыми данными
            delay(2);                              // ЗАДЕРЖКА. Без неё работает некорректно!
        }
        Serial.println(this->transferBuf);
        // this->receivedChar = String(this->serial->read());
        // delay(2);
        // if(this->receivedChar == this->startChar){
        //     this->lastControlChar = this->receivedChar;
        //     this->transferStruct.command = static_cast<RoomLightCommands>(this->serial->read());
        //     delay(2);
        //     this->receivedChar = String(this->serial->read());
        //     delay(2);
        //     Serial.println("Last chars:");
        //     Serial.println(this->receivedChar);
        //     Serial.println(this->lastControlChar);
        //     if(this->receivedChar == this->eolChar){
        //         this->lastControlChar = this->receivedChar;
        //         this->transferStruct.value = "";
        //         while (this->serial->available() > 0) {
        //             this->receivedChar = this->serial->read();
        //             if(this->receivedChar != this->termChar){
        //                 this->transferStruct.value += (char)this->serial->read();
        //                 delay(2);
        //             }
        //         }
        //     }
        // }
        
        // this->serial->readBytes((byte*)&this->transferStruct, this->serial->available());
        // Serial.println("Last command:");
        // Serial.println(this->transferStruct.command);
        // Serial.println("Last string:");
        // Serial.println(this->transferStruct.value);
        // delay(10);
    }
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
    // String str = "command:" + String(command) + "value:" + value;
    // this->serial->write("test", sizeof("test"));

    // this->serial->write((byte*)&transferStruct, sizeof(transferStruct));
    this->serial->print(this->startChar + String(this->transferStruct.command) + this->eolChar + String(this->transferStruct.value) + this->termChar);
    // this->serial->print("command:" + String(command) + "value:" + value);
    // this->serial->print("command:");
}
