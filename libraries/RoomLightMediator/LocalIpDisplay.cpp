#include <LocalIpDisplay.h>

LocalIpDisplay::LocalIpDisplay(LiquidCrystal_I2C *lcd) {
    this->lcd = lcd;
}

void LocalIpDisplay::begin() {
    lcd->init();
    lcd->backlight();
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Initializing...");
}

void LocalIpDisplay::writeAddress(String value) {
    lcd->setCursor(0, 0);
    lcd->print(value);
}

void LocalIpDisplay::writeStatus(String value) {
    lcd->setCursor(0, 1);
    lcd->print(value);
}

void LocalIpDisplay::clear() {
    lcd->clear();
}
