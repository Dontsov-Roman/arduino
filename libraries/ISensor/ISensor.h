#ifndef I_SENSOR_H
#define I_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class ISensor
{
protected:
  uint8_t pin;

public:
  virtual bool isOn();
  virtual void read();
  virtual void statusToSerial();
};

#endif
