#include <LocalIpDisplay.h>

LocalIpDisplay::LocalIpDisplay(LiquidCrystal_I2C *lcd) {
    this->lcd = lcd;
}

void LocalIpDisplay::begin() {
    lcd->init();
    lcd->backlight();
    lcd->setCursor(0, 0);
    lcd->print("Initializing...");
}
void LocalIpDisplay::write(String address) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Local Ip:");
    lcd->setCursor(1, 1);
    lcd->print(address);
}