#ifndef SENSOR_H
#define SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Sensor
{
protected:
  uint8_t pin;

public:
  bool isOn();
  void read();
  void statusToSerial();
};

#endif
