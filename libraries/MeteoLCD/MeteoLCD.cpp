#include "MeteoLCD.h"

const char TEMPERATURE[] = "Temperature: ";
const char C[] = "C";
const char HUMIDITY[] = "Humidity: ";
const char H[] = "%";
const char AIR[] = "Air is ";
const char CLEAR[] = "clear";
const char DIRTY[] = "dirty";

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
    air += DIRTY;
  } else {
    air += CLEAR;
  }
  return air;
}
void MeteoLCD::print()
{
  display->setFont(BigFont);
  String temp = getValue(getTemperature());
  display->print(TEMPERATURE+temp+C, LEFT, 0);
  String hum = getValue(getHumidity());
  display->print(HUMIDITY+hum+H, LEFT, pixelPerChar*2);
  display->print(getAir(), LEFT, pixelPerChar*16);

  display->setFont(Grotesk32x64);
  display->print(rtc->gettime("d.m.Y"), CENTER, pixelPerChar*6);
  display->print(rtc->gettime("H:i, D"), CENTER, pixelPerChar*10);
}