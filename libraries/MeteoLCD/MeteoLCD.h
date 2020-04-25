#ifndef METEO_LCD_H
#define METEO_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <UTFT.h>
#include <TFT_HX8357.h>
#include "DHT.h"

class MeteoLCD
{
public:
  MeteoLCD(DHT dht, UTFT display, int pixelPerChar);
  void init();
  float getHumidity();
  float getTemperature();
  void printToDisplay();

protected:
  DHT dht;
  UTFT display;
  TFT_HX8357 tft;
  int pixelPerChar;
  char temp[2];
  char hum[2];
  int tempX;
  int humX;
}