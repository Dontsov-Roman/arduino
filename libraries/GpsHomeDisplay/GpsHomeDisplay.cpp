#include <GpsHomeDisplay.h>

GpsHomeDisplay::GpsHomeDisplay(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    ISimpleDisplay *display,
    SimpleToggleSensor *button,
    SimpleTimeout *getGpsTimeout)
{
    this->wifiClient = wifiClient;
    this->gpsHttpClient = gpsHttpClient;
    this->display = display;
    this->button = button;
    this->getGpsTimeout = getGpsTimeout;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
    this->gpsData = GpsData();
}
void GpsHomeDisplay::begin()
{
    this->button->begin();
    this->gpsHttpClient->begin();
    this->display->begin();

    this->getGpsTimeout->checkTimeout();
    do
    {
        delay(1000);
    } while (!this->getGpsTimeout->checkTimeout());
}
void GpsHomeDisplay::loop()
{
    if (this->getGpsTimeout->checkTimeout())
    {
        this->display->clear();
        if (this->wifiClient->isConnected())
        {
            this->gpsData.parse(this->gpsHttpClient->get());
            if (this->gpsData.isDateTimeReady)
            {
                this->displaySwitcher.writeFirstRow("Last GPS Date Time:", "Local IP:");
                this->displaySwitcher.writeSecondRow(this->gpsData.getGpsDateTime(), this->wifiClient->getLocalIP());
            }
        }
        else
        {
            this->reconnect();
        }
        this->displaySwitcher.switchDisplay();
    }
    this->toggleLight();
}
void GpsHomeDisplay::toggleLight()
{
    this->button->read();
    if (this->previousButtonState != this->button->isOn())
    {
        this->previousButtonState = this->button->isOn();
        this->gpsHttpClient->get(this->previousButtonState ? this->turnOnLightUrl : this->turnOffLightUrl);
    }
}
void GpsHomeDisplay::reconnect()
{
    this->display->clear();
    this->displaySwitcher.writeFirstRow("No connection", "No connection");
    this->displaySwitcher.writeSecondRow("Reconnecting...", "Reconnecting...");
    this->wifiClient->begin();
}