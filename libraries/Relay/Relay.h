#ifndef RELAY_H
#define RELAY_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ISensor.h"

class Relay : public ISensor
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
  void on();
  void off();
};
#endif
