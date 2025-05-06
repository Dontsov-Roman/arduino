#ifndef SIMPLE_SENSOR_H
#define SIMPLE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ISensor.h"

class SimpleSensor : public ISensor
{
protected:
    bool enabled;
    uint8_t pin;

public:
    SimpleSensor();
    // pin
    SimpleSensor(uint8_t p);
    void begin();
    void read();
    bool isOn();
    void statusToSerial();
};

#endif