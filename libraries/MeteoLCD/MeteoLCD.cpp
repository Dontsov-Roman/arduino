#include "MeteoLCD.h"

const char temperature[] = "Temperature: ";
const char humidity[] = "Humidity: ";

MeteoLCD::MeteoLCD(DHT *_dht, UTFT *_display, iarduino_RTC *_rtc, int pixelPerChar)
{
  this->display = _display;
  this->dht = _dht;
  this->rtc = _rtc;
  this->pixelPerChar = pixelPerChar;
  this->tempX = sizeof(temperature) * pixelPerChar;
  this->humX = sizeof(humidity) * pixelPerChar;
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
  display->setFont(BigFont);
}
float MeteoLCD::getHumidity()
{
  return dht->readHumidity();
}
float MeteoLCD::getTemperature()
{
  return dht->readTemperature();
}
void MeteoLCD::printToDisplay()
{
  String temp = getValue(getTemperature());
  display->print(temperature, LEFT, 0);
  display->print(temp, tempX, 0);
  String hum = getValue(getHumidity());
  display->print(humidity, LEFT, pixelPerChar*2);
  display->print(hum, humX, pixelPerChar*2);
  display->print(rtc->gettime("d-m-Y, H:i, D"), CENTER, pixelPerChar*4);
}