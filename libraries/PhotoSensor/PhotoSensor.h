#ifndef PHOTO_H
#define PHOTO_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class PhotoSensor
{
public:
  PhotoSensor(int pin, int threshold);
  bool isOn();
  void read();

protected:
  int pin;
  int threshold;
  int resist;
  bool enabled;
};

#endif
