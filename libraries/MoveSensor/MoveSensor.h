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
  MoveSensor(Relay *rel, PhotoSensor *photo, MoveSensorMode mode, int p);
  void read();
  bool isOn();
  void toggle();
  void setMode(MoveSensorMode mode);

protected:
  void on();
  void off();
  PhotoSensor *photoSensor;
  Relay *relay;
  MoveSensorMode mode;
  int pin;
  bool enabled;
};

#endif
