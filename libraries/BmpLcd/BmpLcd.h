#ifndef BMP_LCD_H
#define BMP_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <MyLcd.h>
#include <SensorButton.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

const char MM_HG[] = "mH";
const char PA[] = "Pa";
const char C[] = "*C";
const char F[] = "*F";

const int SHORT_DISPLAY = 1;
const int LONG_DISPLAY = 2;

class BmpLcd : public MyLcd
{
public:
  BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280, SensorButton *_btn);
  BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280);
  void init();
  float getPressure();
  float getTemperature();
  void print();
  String getPressureUnit();

protected:
  Adafruit_BMP280 *bmp280;
  LiquidCrystal *display;
  SensorButton *btn;
  void printLong();
  void printShort();
  float getPressurePa();
  float getPressureMh();
  float getTemperatureC();
  float getTemperatureF();

  int displayType;
};

#endif
