#ifndef RELAY_H
#define RELAY_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Sensor.h"

class Relay : public Sensor
{
protected:
  int pin;
  int bit;
  bool enabled;

public:
  Relay(int p, int b);
  void toggle(int val);
  void read();
  int getPin();
  int getBit();
  bool isOn();
};
#endif
