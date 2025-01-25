#ifndef KITCHEN_LIGHT_MEDIATOR_H
#define KITCHEN_LIGHT_MEDIATOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <PhotoSensor.h>
#include <SimpleToggleSensor.h>
#include <SimpleDigitalOutput.h>
#include <SimpleMovementSensor.h>
#include <SimpleTimeout.h>

class KitchenLightMediator
{
public:
    KitchenLightMediator(
        PhotoSensor *lightSensor,
        SimpleToggleSensor *button,
        SimpleMovementSensor *movementSensor,
        SimpleDigitalOutput *output,
        SimpleTimeout *timeout);
    void toggle();
    void begin();

private:
    PhotoSensor *lightSensor;
    SimpleToggleSensor *button;
    SimpleMovementSensor *movementSensor;
    SimpleDigitalOutput *output;
    SimpleTimeout *timeout;
};
#endif
