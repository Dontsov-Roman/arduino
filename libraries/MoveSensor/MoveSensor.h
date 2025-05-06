#ifndef MOVE_SENSOR_H
#define MOVE_SENSOR_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "ISensor.h"
#include "PhotoSensor.h"
#include "Relay.h"
#include "./MoveSensorMode.h"

class MoveSensor : public ISensor
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
  void setPhotoSensorThreshold(int threshold);

protected:
  PhotoSensor *photoSensor;
  Relay *moveRelay;
  Relay *lightRelay;
  MoveSensorMode mode;
  bool enabled;
  int bit;
};

#endif
