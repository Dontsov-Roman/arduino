#include "MeteoLCD.h"


MeteoLCD::MeteoLCD(DHT *_dht, UTFT *_display, iarduino_RTC *_rtc, GasSensor *_gas, int pixelPerChar)
{
  this->display = _display;
  this->dht = _dht;
  this->rtc = _rtc;
  this->pixelPerChar = pixelPerChar;
  this->gas = _gas;
}
String MeteoLCD::getValue(float val){
  int va = val*100;
  String value = String(va/100, DEC); 
  value += ".";
  value += String(va%100, DEC);
  return value;
}
void MeteoLCD::init()
{
  delay(300);
  dht->begin();
  rtc->begin();
  display->InitLCD(1);
  display->clrScr();
}

float MeteoLCD::getHumidity()
{
  return dht->readHumidity();
}

float MeteoLCD::getTemperature()
{
  return dht->readTemperature();
}

String MeteoLCD::getAir(){
  gas->read();
  String air(AIR);
  if(gas->isDanger()){
    display->setColor(VGA_RED);
    air += DIRTY;
  } else {
    display->setColor(VGA_GREEN);
    air += CLEAR;
  }
  return air;
}

void MeteoLCD::print()
{
  display->setColor(VGA_WHITE);
  display->setFont(BigFont);
  display->print(TEMPERATURE+getValue(getTemperature())+C, LEFT, 0);
  display->print(HUMIDITY+getValue(getHumidity())+H, LEFT, pixelPerChar*2);
  display->print(getAir(), LEFT, pixelPerChar*16);
  display->setColor(VGA_WHITE);

  display->setFont(Grotesk32x64);
  display->print(rtc->gettime("d.m.Y"), CENTER, pixelPerChar*6);
  display->print(rtc->gettime("H:i, D"), CENTER, pixelPerChar*10);
}