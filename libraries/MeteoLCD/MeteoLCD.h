#ifndef METEO_LCD_H
#define METEO_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <UTFT.h>
// #include "iarduino_RTC"
#include "DHT.h"

extern uint8_t BigFont[];
class MeteoLCD
{
public:
  MeteoLCD(DHT *_dht, UTFT *_display, int pixelPerChar);
  void init();
  float getHumidity();
  float getTemperature();
  void printToDisplay();
  String getValue(float value);

protected:
  DHT *dht;
  UTFT *display;
  // iarduino_RTC *time;
  int pixelPerChar;
  String temp;
  String hum;
  int tempX;
  int humX;
};

#endif