#ifndef METEO_LCD_H
#define METEO_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <MyLcd.h>
#include <UTFT.h>
#include <iarduino_RTC.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <GasSensor.h>

extern uint8_t BigFont[];
extern uint8_t Grotesk32x64[];

const char TEMPERATURE[] = "Temperature: ";
const char C[] = "C";
const char HUMIDITY[] = "Humidity: ";
const char H[] = "%";
const char AIR[] = "Air is ";
const char CLEAR[] = "clear";
const char DIRTY[] = "dirty";

class MeteoLCD : public MyLcd
{
public:
  MeteoLCD(DHT *_dht, UTFT *_display, iarduino_RTC *_rtc, GasSensor *_gas, int pixelPerChar);
  void init();
  float getHumidity();
  float getTemperature();
  void print();

protected:
  String getAir();
  DHT *dht;
  UTFT *display;
  iarduino_RTC *rtc;
  GasSensor *gas;
  int pixelPerChar;
  String temp;
  String hum;
};

#endif