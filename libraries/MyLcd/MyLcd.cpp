#include "MyLcd.h"

String MyLcd::getValue(float val)
{
  int va = val * 100;
  String value = String(va / 100, DEC);
  value += ".";
  value += String(va % 100, DEC);
  return value;
}