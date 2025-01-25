#ifndef SIMPLE_TOGGLE_SENSOR_H
#define SIMPLE_TOGGLE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
// #include "Sensor.h"
#include "SimpleSensor.h"
#include <SimpleTimeout.h>

class SimpleToggleSensor : public SimpleSensor
{
protected:
    bool enabled;
    uint8_t pin;
    SimpleTimeout *timeout;

public:
    SimpleToggleSensor();
    SimpleToggleSensor(uint8_t p, SimpleTimeout *timeout);
    void begin();
    void read();
    bool isOn();
    void statusToSerial();
};

#endif