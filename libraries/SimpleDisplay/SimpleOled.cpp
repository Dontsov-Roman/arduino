#include <SimpleOled.h>

void SimpleOled::begin()
{
  // if (!this->display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  // {
  //   Serial.println(F("SSD1306 allocation failed"));
  // }

  this->clear();

  this->display->setTextSize(1); // Draw 2X-scale text
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(0, 0);
  this->display->println(F("initializing..."));
  this->display->display();
}

void SimpleOled::clear()
{
  this->display->clearDisplay();
}

void SimpleOled::writeFirstRow(String string)
{
  this->display->setCursor(0, 0);
  this->display->println(string);
  this->display->display();
}

void SimpleOled::writeSecondRow(String string)
{
  this->display->setCursor(0, 10);
  this->display->println(string);
  this->display->display();
}