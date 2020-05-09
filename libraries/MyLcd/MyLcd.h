#ifndef MY_LCD_H
#define MY_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class MyLcd
{
public:
  String getValue(float value);
};
#endif
