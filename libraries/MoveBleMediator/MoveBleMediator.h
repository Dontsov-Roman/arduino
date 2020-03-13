#ifndef MOVE_BLE_MEDIATOR_H
#define MOVE_BLE_MEDIATOR_H
#include "BleSensor.h"
#include "MoveSensor.h"

class MoveBleMediator
{
public:
  MoveBleMediator(MoveSensor *MS, BleSensor *BS);
  void read();

protected:
  MoveSensor *moveSensor;
  BleSensor *bleSensor;
};

#endif
