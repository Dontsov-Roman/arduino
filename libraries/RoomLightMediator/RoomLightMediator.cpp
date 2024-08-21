#include <SimpleSensor.h>
#include <SimpleDigitalOutput.h>
#include <SimpleMovementSensor.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightMediator.h>
#include <RoomLightCommands.h>
#include <TransferStruct.h>

RoomLightMediator::RoomLightMediator() {}

RoomLightMediator::RoomLightMediator(RoomLightSerial *serial, SimpleSensor *button, SimpleDigitalOutput *led, SimpleMovementSensor *movementSensor, LocalIpDisplay *lcd) {
    this->serial = serial;
    this->button = button;
    this->led = led;
    this->movementSensor = movementSensor;
    this->lcd = lcd;
    this->lcdStatusTimeout = 5;
    this->lastUpdateMillis = 0;
}

void RoomLightMediator::begin() {
    this->led->begin();
    this->lcd->begin();
    this->movementSensor->calibrate();
    this->lcd->clear();
    this->lcd->writeAddress("No address");
}
void RoomLightMediator::toggle() {
    this->button->read();
    this->movementSensor->read();
    this->serial->read();
    TransferStruct *ts = this->serial->getTransferStruct();
    if(ts->command == SetLocalIpCommand) {
        this->lcd->writeAddress(ts->value);
        delay(300);
        this->serial->clearTransferStruct();
    }
    if (!this->button->isOn()) {
        this->led->switchOn();
    } else {
        switch (ts->command)
        {
            case SwitchOnCommand:
                this->led->switchOn();
                break;
            case SwitchOffCommand:
                this->led->switchOff();
                break;
            case MovementModeCommand:
                if(this->movementSensor->isOn()) {
                    this->led->switchOn();
                } else {
                    this->led->switchOff();
                }
                break;
            case NothingCommand:
            default:
                break;
        }
    }
    if (this->checkLcdStatus()) {
        this->lcd->writeStatus(this->getStatus());
    }
}
String RoomLightMediator::getStatus() {
    return String(String(!this->button->isOn()) + ',' + String(this->movementSensor->isOn()) + ',' + String(this->serial->getTransferStruct()->command) + ',' + String(this->led->isOn()));
}
bool RoomLightMediator::checkLcdStatus() {
    int mil_sec = millis();
    if (mil_sec - this->lastUpdateMillis > this->lcdStatusTimeout) {
        this->lastUpdateMillis = mil_sec;
        return true;
    }
    return false;
}