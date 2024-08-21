#ifndef ROOM_LIGHT_MEDIATOR_H
#define ROOM_LIGHT_MEDIATOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SimpleSensor.h>
#include <SimpleDigitalOutput.h>
#include <SimpleMovementSensor.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <LocalIpDisplay.h>

class RoomLightMediator {
    public:
        RoomLightMediator();
        RoomLightMediator(RoomLightSerial *serial, SimpleSensor *button, SimpleDigitalOutput *led, SimpleMovementSensor *movementSensor, LocalIpDisplay *lcd);
        void begin();
        void toggle();
    protected:
        RoomLightSerial *serial;
        SimpleSensor *button;
        SimpleDigitalOutput *led;
        SimpleMovementSensor *movementSensor;
        LocalIpDisplay *lcd;

};
#endif