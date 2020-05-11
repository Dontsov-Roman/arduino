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
#include <Adafruit_BMP280.h>

extern uint8_t BigFont[];
extern uint8_t Grotesk32x64[];

const char TEMPERATURE[] = "Temperature: ";
const char C[] = "C";
const char PRESSURE[] = "Pressure: ";
const char P[] = "mmHg";
const char ALTITUDE[] = "Altitude: ";
const char ALT[] = "m";
const char AIR[] = "Air is ";
const char CLEAR[] = "clear";
const char DIRTY[] = "dirty";

class MeteoLCD : public MyLcd
{
public:
  MeteoLCD(Adafruit_BMP280 *bmp280, UTFT *_display, iarduino_RTC *_rtc, GasSensor *_gas, int pixelPerChar);
  void init();
  float getPressure();
  float getTemperature();
  float getAltitude();
  String getValue(float value);
  void print();

protected:
  String getAir();
  Adafruit_BMP280 *bmp280;
  UTFT *display;
  iarduino_RTC *rtc;
  GasSensor *gas;
  int pixelPerChar;
  String temp;
  String hum;
};

#endif