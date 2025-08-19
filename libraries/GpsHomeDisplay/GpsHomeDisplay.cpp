#include <GpsHomeDisplay.h>

GpsHomeDisplay::GpsHomeDisplay(
    IWifiClient *wifiClient,
    IHttpClient *gpsHttpClient,
    ISimpleDisplay *display,
    SimpleToggleSensor *button,
    NtpTime *ntpTime,
    OpenWeather *openWeather,
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
    this->openWeather = openWeather;
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
    this->openWeather->begin();
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
            ResponseStruct *response = this->gpsHttpClient->get();
            if (response->code == 200)
            {
                this->gpsData.parse(response->response);
            }
        }
        if (this->displaySwitchTimeout->checkTimeout())
        {
            this->display->clear();
            this->display->writeFirstRow(this->ntpTime->getDayTime());

            this->displaySwitcher.writeSecondRow("Last GPS Date Time:", this->openWeather->getLastTemperature());
            this->displaySwitcher.writeThirdRow(
                this->gpsData.isDateTimeReady ? this->gpsData.getGpsDateTime() : "No GPS Data",
                this->openWeather->getLastWeather());
            this->displaySwitcher.switchDisplay();
        }
    }
    else if (this->reconnectionTimeout->checkTimeout())
    {
        this->reconnect();
    }
    this->toggleLight();
    this->ntpTime->loop();
    this->openWeather->loop();
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