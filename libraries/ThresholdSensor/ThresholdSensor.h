#ifndef THRESHOLD_SENSOR_H
#define THRESHOLD_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ISensor.h"

class ThresholdSensor : public ISensor
{
public:
  void begin();
  void read();
  bool isOn();
  void setThreshold(int threshold);
  void statusToSerial();

protected:
  uint8_t pin;
  int threshold;
  int resist;
  bool enabled;
};

#endif
