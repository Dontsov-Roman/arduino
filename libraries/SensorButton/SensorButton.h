#ifndef SENSOR_BUTTON_H
#define SENSOR_BUTTON_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <Sensor.h>

class SensorButton : public Sensor
{
public:
  SensorButton(uint8_t _pin);
  SensorButton(uint8_t _pin, bool defaultValue);
  void init();
  bool isOn();
  void read();

protected:
  bool value;
};

#endif
