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
#include <SimpleTimeout.h>
#include <ISimpleDisplay.h>

class RoomLightMediator {
    public:
        RoomLightMediator();
        RoomLightMediator(
            RoomLightSerial *serial,
            SimpleSensor *button,
            SimpleDigitalOutput *led,
            SimpleMovementSensor *movementSensor,
            ISimpleDisplay *display
        );
        void begin();
        void toggle();
    protected:
        // Button, Movement, Last Command, Led
        String getStatus();
        RoomLightSerial *serial;
        SimpleSensor *button;
        SimpleDigitalOutput *led;
        SimpleMovementSensor *movementSensor;
        ISimpleDisplay *display;
        SimpleTimeout simpleTimeout;
        int lastCommand;
        String eol;
};
#endif