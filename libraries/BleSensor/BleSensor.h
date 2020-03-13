#ifndef BLE_SENSOR_H
#define BLE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Sensor.h"

const int BUFFER_LENGTH = 3;

class BleSensor : public Sensor
{
public:
  BleSensor();
  void read();
  bool isOn();
  char *getValue();

protected:
  char buf[BUFFER_LENGTH];
};

#endif
