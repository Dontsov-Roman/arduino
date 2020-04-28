#ifndef PHOTO_H
#define PHOTO_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ThresholdSensor.h"

class PhotoSensor : public ThresholdSensor
{
  public:
    PhotoSensor(uint8_t p);
    PhotoSensor(uint8_t p, int t);
};

#endif
