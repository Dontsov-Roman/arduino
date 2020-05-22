#include "KitchenLcd.h"

KitchenLcd::KitchenLcd(LiquidCrystal *_lcd, iarduino_RTC *_rtc, DHT *_dht, SensorButton *_btn, BleSensor *_bs, BleRtcSetter *_brs)
{
  this->lcd = _lcd;
  this->rtc = _rtc;
  this->dht = _dht;
  this->btn = _btn;
  this->bs = _bs;
  this->brs = _brs;
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
  btn->init();
}

void KitchenLcd::print()
{
  brs->setTime();
  bool previous = btn->isOn();
  btn->read();
  if (previous != btn->isOn())
  {
    lcd->clear();
  }
  lcd->setCursor(0, 0);
  lcd->print(rtc->gettime("H:i"));
  lcd->print(", ");
  String temperature = getValue(dht->readTemperature());
  String humidity = getValue(dht->readHumidity());
  String buf = temperature + humidity;
  bs->write(buf.c_str());
  if (btn->isOn())
  {
    lcd->print(temperature);
    lcd->print(" *C");
  }
  else
  {
    lcd->print(humidity);
    lcd->print(" %");
  }
  lcd->setCursor(0, 1);
  lcd->print(rtc->gettime("d-m-Y, D"));
}