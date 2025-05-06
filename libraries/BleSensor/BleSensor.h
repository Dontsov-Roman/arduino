#ifndef BLE_SENSOR_H
#define BLE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ISensor.h"

const int DEFAULT_BUFFER_LENGTH = 3;
class BleSensor : public ISensor
{
public:
  BleSensor();
  BleSensor(char *_buf, int _bufLength);
  char *read();
  bool isOn();
  char *getValue();
  void write(char *_buf);

protected:
  char *buf;
  char bleDefaultBuf[DEFAULT_BUFFER_LENGTH];
  int bufLength;
};

#endif
