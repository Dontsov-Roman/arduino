#include "KitchenLcd.h"

KitchenLcd::KitchenLcd()
{
}
KitchenLcd::KitchenLcd(LiquidCrystal *_lcd, iarduino_RTC *_rtc)
{
  this->lcd = _lcd;
  this->rtc = _rtc;
}

KitchenLcd::KitchenLcd(LiquidCrystal *_lcd, iarduino_RTC *_rtc, DHT *_dht)
{
  this->lcd = _lcd;
  this->rtc = _rtc;
  this->dht = _dht;
}

void KitchenLcd::setDisplay(LiquidCrystal *_lcd)
{
  this->lcd = _lcd;
}

void KitchenLcd::setRtc(iarduino_RTC *_rtc)
{
  this->rtc = _rtc;
}

void KitchenLcd::init()
{
  lcd->begin(16, 2);
  rtc->begin();
  dht->begin();
}

void KitchenLcd::print()
{
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(rtc->gettime("H:i"));
  lcd->print(", ");
  lcd->print(this->getValue(dht->readTemperature()));
  lcd->print(" *C");
  lcd->setCursor(0, 1);
  lcd->print(rtc->gettime("d-m-Y, D"));
}