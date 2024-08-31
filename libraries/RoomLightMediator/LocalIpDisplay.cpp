#include <LocalIpDisplay.h>

LocalIpDisplay::LocalIpDisplay(LiquidCrystal_I2C *display) {
    this->display = display;
}

void LocalIpDisplay::begin() {
    display->init();
    display->backlight();
    display->clear();
    display->setCursor(0, 0);
    display->print("Initializing...");
}

void LocalIpDisplay::writeFirstRow(String value) {
    display->setCursor(0, 0);
    display->print(value);
}

void LocalIpDisplay::writeSecondRow(String value) {
    display->setCursor(0, 1);
    display->print(value);
}

void LocalIpDisplay::clear() {
    display->clear();
}
