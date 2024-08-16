#ifndef SIMPLE_MOVEMENT_SENSOR_H
#define SIMPLE_MOVEMENT_SENSOR_H
#define SIMPLE_MOVEMENT_SENSOR_DEFAULT_CALIBRATION_TIME 5;
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "SimpleSensor.h"

class SimpleMovementSensor : public SimpleSensor
{
    protected:
        int calibrationTime;
    public:
        SimpleMovementSensor();
        // pin
        SimpleMovementSensor(uint8_t p);
        // pin and calibration time in seconds, DEFAULT is 5 seconds
        SimpleMovementSensor(uint8_t p, int calibrationTime);
        // Should be calibrated in setup
        void calibrate();
};
#endif
