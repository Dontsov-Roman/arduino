#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "MoveBleMediator.h"
#include "BleSensor.h"
#include "MoveSensor.h"

MoveBleMediator::MoveBleMediator(MoveSensor *MS, BleSensor *BS) : moveSensor(MS), bleSensor(BS) {}

void MoveBleMediator::read()
{
  bleSensor->read();
  moveSensor->read();
  char *value = bleSensor->getValue();
  switch (String(value[0]).toInt())
  {
  case 1:
    moveSensor->setMode(PHOTORESISTOR);
    moveSensor->toggle();
    break;

  case 2:
    moveSensor->setMode(TOGGLE);
    moveSensor->toggle(String(value[1]).toInt());
    break;

  case 0:
  default:
    moveSensor->setMode(MOVEMENT);
    moveSensor->toggle();
    break;
  }
}