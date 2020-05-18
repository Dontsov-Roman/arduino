#include <BmpLcd.h>

BmpLcd::BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280, SensorButton *_btn)
{
  this->display = _display;
  this->bmp280 = _bmp280;
  this->btn = _btn;
}
void BmpLcd::init()
{
  display->begin(16, 2);
  while (!bmp280->begin(BMP280_ADDRESS - 1))
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
}

float BmpLcd::getPressure()
{

  if (btn->isOn())
  {
    return bmp280->readPressure();
  }
  else
  {
    return bmp280->readPressure() / 133.322;
  }
}

float BmpLcd::getTemperature()
{
  return bmp280->readTemperature();
}
String BmpLcd::getPressureUnit()
{

  if (btn->isOn())
  {
    return MM_HG;
  }
  else
  {
    return PA;
  }
}
void BmpLcd::print()
{
  bool previous = btn->isOn();
  btn->read();
  if (previous != btn->isOn())
  {
    display->clear();
  }

  display->setCursor(0, 0);
  display->print(this->getValue(this->getTemperature()));
  display->setCursor(13, 0);
  display->print(" *C");
  display->setCursor(0, 1);
  display->print(this->getValue(this->getPressure()));
  display->setCursor(13, 1);
  display->print(getPressureUnit());
}