#ifndef PHOTO_H
#define PHOTO_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Sensor.h"

class PhotoSensor : public Sensor
{
public:
  PhotoSensor(int pin, int threshold);
  void read();

protected:
  int pin;
  int threshold;
  int resist;
  bool enabled;
};

#endif
