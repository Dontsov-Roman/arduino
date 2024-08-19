#include <SimpleSensor.h>
#include <SimpleDigitalOutput.h>
#include <SimpleMovementSensor.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightMediator.h>
#include <RoomLightCommands.h>
#include <TransferStruct.h>

RoomLightMediator::RoomLightMediator() {}

RoomLightMediator::RoomLightMediator(RoomLightSerial *serial, SimpleSensor *button, SimpleDigitalOutput *led, SimpleMovementSensor *movementSensor) {
    this->serial = serial;
    this->button = button;
    this->led = led;
    this->movementSensor = movementSensor;
    this->address = "";
}

void RoomLightMediator::begin() {
    this->led->begin();
    this->movementSensor->calibrate();
}
void RoomLightMediator::toggle() {
    this->button->read();
    if (!this->button->isOn()) {
        this->led->switchOn();
    } else {
        this->serial->read();
        TransferStruct *ts = this->serial->getTransferStruct();
        switch (ts->command)
        {
        case SwitchOn:
            this->led->switchOn();
            break;
        case SwitchOff:
            this->led->switchOff();
            break;
        case SetLocalIp:
            this->address = ts->address;
            break;
        case MovementMode:
            this->movementSensor->read();
            if(this->movementSensor->isOn()) {
                this->led->switchOn();
                break;
            }
        default:
            this->led->switchOff();
        }
    }
}