#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
  bool isOn();
  void read();

protected:
  bool enabled;
};

#endif
