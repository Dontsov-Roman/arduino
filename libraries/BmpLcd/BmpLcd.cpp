#include <BmpLcd.h>

BmpLcd::BmpLcd(LiquidCrystal *_display, Adafruit_BMP280 *_bmp280, SensorButton *_btn)
{
  this->display = _display;
  this->bmp280 = _bmp280;
  this->btn = _btn;
}
void BmpLcd::init()
{
  Serial.println("TEST");
  display->begin(8, 2);
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
    return PA;
  }
  else
  {
    return MM_HG;
  }
}
void BmpLcd::print()
{

  Serial.println(this->getValue(this->getTemperature()));
  Serial.println(this->getValue(this->getPressure()));
  Serial.println(getPressureUnit());

  bool previous = btn->isOn();
  btn->read();
  if (previous != btn->isOn())
  {
    display->clear();
  }

  display->setCursor(0, 0);
  display->print(getValue(getTemperature()));
  display->setCursor(6, 0);
  display->print("*C");
  display->setCursor(0, 1);
  display->print(getPressure());
  display->setCursor(6, 1);
  display->print(getPressureUnit());
}