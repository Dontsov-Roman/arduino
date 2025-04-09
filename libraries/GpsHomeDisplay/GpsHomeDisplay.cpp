#include <GpsHomeDisplay.h>

GpsHomeDisplay::GpsHomeDisplay(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    ISimpleDisplay *display,
    SimpleToggleSensor *button,
    SimpleTimeout *getGpsTimeout,
    SimpleTimeout *initializationTimeout,
    SimpleTimeout *displaySwitchTimeout,
    SimpleTimeout *reconnectionTimeout)
{
    this->wifiClient = wifiClient;
    this->gpsHttpClient = gpsHttpClient;
    this->display = display;
    this->button = button;
    this->getGpsTimeout = getGpsTimeout;
    this->initializationTimeout = initializationTimeout;
    this->displaySwitchTimeout = displaySwitchTimeout;
    this->reconnectionTimeout = reconnectionTimeout;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
    this->gpsData = GpsData();
}
void GpsHomeDisplay::begin()
{
    this->button->begin();
    this->gpsHttpClient->begin();
    this->display->begin();

    this->initializationTimeout->checkTimeout();
    do
    {
        delay(1000);
    } while (!this->initializationTimeout->checkTimeout());
}
void GpsHomeDisplay::loop()
{
    if (this->wifiClient->isConnected())
    {
        if (this->getGpsTimeout->checkTimeout())
        {
            this->gpsData.parse(this->gpsHttpClient->get()->response);
        }
        if (this->displaySwitchTimeout->checkTimeout())
        {
            this->display->clear();
            this->displaySwitcher.writeFirstRow("Last GPS Date Time:", "Local IP:");
            if (this->gpsData.isDateTimeReady)
            {
                this->displaySwitcher.writeSecondRow(this->gpsData.getGpsDateTime(), this->wifiClient->getLocalIP());
            }
            else
            {
                this->displaySwitcher.writeSecondRow("No GPS Data", this->wifiClient->getLocalIP());
            }
            this->displaySwitcher.switchDisplay();
        }
    }
    else if (this->reconnectionTimeout->checkTimeout())
    {
        this->reconnect();
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
    this->display->writeFirstRow("No connection");
    this->display->writeSecondRow("Reconnecting...");
    this->wifiClient->begin();
}