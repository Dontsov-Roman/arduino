#include "GasSensor.h"
#include "ThresholdSensor.h"

GasSensor::GasSensor(uint8_t p)
{
    this->pin = p;
    this->threshold = 400;
}

GasSensor::GasSensor(uint8_t p, int t)
{
    this->pin = p;
    this->threshold = t;
}
bool GasSensor::isDanger(){
    return !enabled;
}