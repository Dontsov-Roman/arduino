#ifndef BLE_SENSOR_H
#define BLE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Sensor.h"

const int BUFFER_LENGTH = 12;

class BleSensor : public Sensor
{
public:
  BleSensor();
  BleSensor(char *_buf, int _bufLength);
  void read();
  bool isOn();
  char *getValue();

protected:
  char buf[BUFFER_LENGTH];
  char *customBuf;
  int bufLength;
  bool isCustomBuf;
};

#endif
