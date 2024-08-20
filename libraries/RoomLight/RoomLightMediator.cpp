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
}

void RoomLightMediator::begin() {
    this->led->begin();
    this->lcd->begin();
    this->movementSensor->calibrate();
    this->lcd->write("No address");
}
void RoomLightMediator::toggle() {
    this->button->read();
    this->movementSensor->read();
    this->serial->read();
    TransferStruct *ts = this->serial->getTransferStruct();
    if(ts->command == SetLocalIp) {
        this->lcd->write(ts->value);
    }
    if (!this->button->isOn()) {
        this->led->switchOn();
    } else {
        switch (ts->command)
        {
        case SwitchOn:
            this->led->switchOn();
            break;
        case SwitchOff:
            this->led->switchOff();
            break;
        case MovementMode:
            if(this->movementSensor->isOn()) {
                this->led->switchOn();
                break;
            }
        default:
            this->led->switchOff();
        }
    }
}