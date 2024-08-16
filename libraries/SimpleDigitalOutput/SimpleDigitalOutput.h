#ifndef SIMPLE_DIGITAL_OUTPUT_H
#define SIMPLE_DIGITAL_OUTPUT_H
#define SIMPLE_MOVEMENT_SENSOR_DEFAULT_CALIBRATION_TIME 5;
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "SimpleSensor.h"

class SimpleDigitalOutput : public SimpleSensor
{
    public:
        SimpleDigitalOutput();
        SimpleDigitalOutput(uint8_t p);
        void switchOn();
        void switchOff();
        void begin();
};
#endif