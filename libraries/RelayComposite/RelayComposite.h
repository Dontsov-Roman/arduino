#ifndef RELAY_COMPOSITE_H
#define RELAY_COMPOSITE_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "RelayAbstract.h"

class RelayComposite : public RelayAbstract
{

public:
  RelayAbstract items[];
  RelayComposite::RelayComposite(RelayAbstract it[])
  {
    int i;
    for (i = 0; i < sizeof(it); i++)
    {
      items[i] = it[i];
    }
    // items = it;
  }
  // void add(RelayAbstract item)
  // {
  // }
  void toggle(int val)
  {
    int i;
    for (i = 0; i < sizeof(this->items); i = i + 1)
    {
      this->items[i].toggle(val);
    }
  }
};
#endif