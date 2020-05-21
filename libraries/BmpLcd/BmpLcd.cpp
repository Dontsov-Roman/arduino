#include <BmpLcd.h>

BmpLcd::BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280, SensorButton *_btn)
{
  this->display = _display;
  this->bmp280 = _bmp280;
  this->btn = _btn;
  this->displayType = SHORT_DISPLAY;
}
BmpLcd::BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280)
{
  this->display = _display;
  this->bmp280 = _bmp280;
  this->displayType = LONG_DISPLAY;
}
void BmpLcd::init()
{
  if (displayType == LONG_DISPLAY)
  {
    display->begin(16, 2);
  }
  else
  {
    display->begin(8, 2);
  }
  while (!bmp280->begin(BMP280_ADDRESS - 1))
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
}
float BmpLcd::getPressurePa()
{
  return bmp280->readPressure();
}
float BmpLcd::getPressureMh()
{
  return bmp280->readPressure() / 133.322;
}

float BmpLcd::getPressure()
{

  if (btn->isOn())
  {
    return getPressurePa();
  }
  else
  {
    return getPressureMh();
  }
}
float BmpLcd::getTemperatureC()
{
  return bmp280->readTemperature();
}
float BmpLcd::getTemperatureF()
{
  return getTemperatureC() * 1.8 + 32;
}

float BmpLcd::getTemperature()
{
  return getTemperatureC();
}
String BmpLcd::getPressureUnit()
{

  if (btn->isOn())
  {
    return PA;
  }
  else
  {
    return MM_HG;
  }
}
void BmpLcd::printShort()
{
  bool previous = btn->isOn();
  btn->read();
  if (previous != btn->isOn())
  {
    display->clear();
  }

  display->setCursor(0, 0);
  display->print(getValue(getTemperature()));
  display->setCursor(5, 0);
  display->print(C);
  display->setCursor(8, 0);
  display->print(getPressure());
  display->setCursor(6, 1);
  display->print(getPressureUnit());
}

void BmpLcd::printLong()
{
  display->setCursor(0, 0);
  display->print(getValue(getTemperature()));
  display->setCursor(5, 0);
  display->print(C);
  display->setCursor(0, 1);
  display->print(getPressure());
  display->setCursor(8, 0);
  display->print(getPressureMh());
  display->setCursor(14, 0);
  display->print(MM_HG);
  display->setCursor(0, 1);

  display->print(getValue(getTemperatureF()));
  display->setCursor(5, 1);
  display->print(F);
  display->setCursor(8, 1);
  display->print(getPressurePa());
  display->print(PA);
}

void BmpLcd::print()
{
  if (displayType == LONG_DISPLAY)
  {
    printLong();
  }
  else
  {
    printShort();
  }
}
