#include <GpsHomeDisplay.h>

GpsHomeDisplay::GpsHomeDisplay(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    ISimpleDisplay *display,
    SimpleToggleSensor *button,
    NtpTime *ntpTime,
    SimpleTimeout *getGpsTimeout,
    SimpleTimeout *initializationTimeout,
    SimpleTimeout *displaySwitchTimeout,
    SimpleTimeout *reconnectionTimeout)
{
    this->wifiClient = wifiClient;
    this->gpsHttpClient = gpsHttpClient;
    this->display = display;
    this->button = button;
    this->ntpTime = ntpTime;
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
    this->ntpTime->begin();
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
            this->display->writeFirstRow(this->ntpTime->getDayTime());

            this->displaySwitcher.writeSecondRow("Last GPS Date Time:", "IP: " + this->wifiClient->getLocalIP());
            if (this->gpsData.isDateTimeReady)
            {
                this->displaySwitcher.writeThirdRow(this->gpsData.getGpsDateTime(), this->gpsData.getGpsDateTime());
            }
            else
            {
                this->display->writeThirdRow("No GPS Data");
            }
            this->displaySwitcher.switchDisplay();
        }
    }
    else if (this->reconnectionTimeout->checkTimeout())
    {
        this->reconnect();
    }
    this->toggleLight();
    this->ntpTime->loop();
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