#include "MeteoLCD.h"

MeteoLCD::MeteoLCD(Adafruit_BMP280 *_bmp280, UTFT *_display, iarduino_RTC *_rtc, GasSensor *_gas, int pixelPerChar)
{
  this->display = _display;
  this->bmp280 = _bmp280;
  this->rtc = _rtc;
  this->pixelPerChar = pixelPerChar;
  this->gas = _gas;
}
String MeteoLCD::getValue(float val)
{
  int va = val * 100;
  String value = String(va / 100, DEC);
  value += ".";
  value += String(va % 100, DEC);
  return value;
}
void MeteoLCD::init()
{
  delay(300);
  while (!bmp280->begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
  rtc->begin();
  display->InitLCD(1);
  display->clrScr();
}

float MeteoLCD::getPressure()
{
  Serial.println(bmp280->readPressure());
  Serial.println(bmp280->readPressure() / 133.322);
  return bmp280->readPressure() / 133.322;
}

float MeteoLCD::getTemperature()
{
  return bmp280->readTemperature();
}

float MeteoLCD::getAltitude(){
  return bmp280->readAltitude();
}

String MeteoLCD::getAir()
{
  gas->read();
  String air(AIR);
  if (gas->isDanger())
  {
    display->setColor(VGA_RED);
    air += DIRTY;
  }
  else
  {
    display->setColor(VGA_LIME);
    air += CLEAR;
  }
  return air;
}

void MeteoLCD::print()
{
  display->setColor(VGA_WHITE);
  display->setFont(BigFont);
  display->print(TEMPERATURE + getValue(getTemperature()) + C, LEFT, 0);
  display->print(PRESSURE + String(getPressure()) + P, LEFT, pixelPerChar * 2);
  display->print(ALTITUDE + String(getAltitude()) + ALT, LEFT, pixelPerChar * 4);
  display->print(getAir(), LEFT, pixelPerChar * 16);
  display->setColor(VGA_WHITE);

  display->setFont(Grotesk32x64);
  display->print(rtc->gettime("H:i, D"), CENTER, pixelPerChar * 6);
  display->print(rtc->gettime("d.m.Y"), CENTER, pixelPerChar * 10);
}