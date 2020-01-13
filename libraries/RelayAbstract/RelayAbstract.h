#ifndef RELAY_ABSTRACT_H
#define RELAY_ABSTRACT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class RelayAbstract
{
public:
  virtual void toggle(int val);
};
#endif