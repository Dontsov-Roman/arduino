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
    this->eol = ",";
    this->simpleTimeout = SimpleTimeout();
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
    } else {
        this->lastCommand = ts->command;
    }
    if (!this->button->isOn()) {
        this->led->switchOn();
    } else {
        switch (this->lastCommand)
        {
            case SwitchOnCommand:
                this->led->switchOn();
                break;
            case MovementModeCommand:
                if(this->movementSensor->isOn()) {
                    this->led->switchOn();
                } else {
                    this->led->switchOff();
                }
                break;
            case SwitchOffCommand:
            case NothingCommand:
            default:
                this->led->switchOff();
                break;
        }
    }
    if (this->simpleTimeout.checkTimeout()) {
        this->lcd->writeStatus(this->getStatus());
    }
}
String RoomLightMediator::getStatus() {
    return String(
        "B:" +String(!this->button->isOn()) + eol +
        "M:" + String(this->movementSensor->isOn()) + eol +
        "C:" + String(this->lastCommand) + eol +
        "L:" +String(this->led->isOn())
    );
}