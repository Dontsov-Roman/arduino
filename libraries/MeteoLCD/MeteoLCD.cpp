#include "MeteoLCD.h"

const char temperature[] = "Temperature: ";
const char humidity[] = "Humidity: ";

MeteoLCD::MeteoLCD(DHT dht, UTFT display, int pixelPerChar)
{
  this->display = display;
  this->dht = dht;
  this->tft = TFT_HX8357();
  this->pixelPerChar = pixelPerChar;
  this->tempX = sizeof(temperature) * pixelPerChar;
  this->humX = sizeof(humidity) * pixelPerChar;
}

void MeteoLCD::init()
{
  dht.begin();
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  display.InitLCD(1);
  display.clrScr();
  display.setFont(BigFont);
}
float MeteoLCD::getHumidity()
{
  return dht.readHumidity();
}
float MeteoLCD::getTemperature()
{
  return dht.readTemperature();
}
void MeteoLCD::printToDisplay()
{
  // float h = dht.readHumidity();
  // float t = dht.readTemperature();

  dtostrf(dht.readHumidity(), 2, 2, temp);
  display.print(temperature, LEFT, 0);
  display.print(temp, tempX, 0);
  dtostrf(dht.readTemperature(), 2, 2, hum);
  display.print(humidity, LEFT, pixelPerChar);
  display.print(hum, humX, pixelPerChar);
}