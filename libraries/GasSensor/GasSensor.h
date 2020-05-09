#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ThresholdSensor.h"

class GasSensor : public ThresholdSensor
{
    public:
        GasSensor(uint8_t p);
        GasSensor(uint8_t p, int t);
        bool isDanger();
};

#endif
