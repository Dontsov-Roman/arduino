#ifndef MOVE_SENSOR_H
#define MOVE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Sensor.h"
#include "PhotoSensor.h"
#include "Relay.h"
#include "./MoveSensorMode.h"

class MoveSensor : public Sensor
{
public:
  MoveSensor(Relay *rel, Relay *lightRel, PhotoSensor *photo, MoveSensorMode mode);
  void read();
  bool isOn();
  void toggle();
  void toggle(int bit);
  void setMode(MoveSensorMode mode);
  void on();
  void off();

protected:
  PhotoSensor *photoSensor;
  Relay *moveRelay;
  Relay *lightRelay;
  MoveSensorMode mode;
  bool enabled;
  int bit;
};

#endif
