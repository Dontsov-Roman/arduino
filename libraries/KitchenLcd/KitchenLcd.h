#ifndef KITCHEN_LCD_H
#define KITCHEN_LCD_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <MyLcd.h>
#include <LiquidCrystal.h>
#include <iarduino_RTC.h>
#include <DHT.h>

class KitchenLcd : public MyLcd
{

public:
  KitchenLcd();
  KitchenLcd(LiquidCrystal *_lcd, iarduino_RTC *_rtc);
  KitchenLcd(LiquidCrystal *_lcd, iarduino_RTC *_rtc, DHT *_dht);
  void setDisplay(LiquidCrystal *_lcd);
  void setRtc(iarduino_RTC *_rtc);
  void init();
  void print();

protected:
  LiquidCrystal *lcd;
  iarduino_RTC *rtc;
  DHT *dht;
};
#endif