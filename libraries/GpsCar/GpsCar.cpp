#include <GpsCar.h>
#include <SimpleTimeout.h>
#include <ResponseStruct.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    IWifiClient *wifiClient,
    IHttpClient *client,
    ISimpleDisplay *display)
{
    this->gpsReader = gpsReader;
    this->client = client;
    this->wifiClient = wifiClient;
    this->display = display;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
    this->timeout = SimpleTimeout(10000);
}
GpsCar::GpsCar(
    GpsReader *gpsReader,
    IWifiClient *wifiClient,
    IHttpClient *client,
    ISimpleDisplay *display,
    int loopTimeout)
{
    this->gpsReader = gpsReader;
    this->client = client;
    this->wifiClient = wifiClient;
    this->display = display;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
    this->timeout = SimpleTimeout(loopTimeout);
}

void GpsCar::begin()
{
    this->wifiClient->begin();
    this->display->begin();
    this->timeout.checkTimeout();
    do
    {
        delay(1000);
    } while (!this->timeout.checkTimeout());
    this->client->begin();
    this->display->clear();
    this->display->writeFirstRow(this->localIpString);
    this->display->writeSecondRow(this->wifiClient->getLocalIP());
}
void GpsCar::loop()
{
    if (this->timeout.checkTimeout())
    {
        this->display->clear();
        this->gpsReader->readGpsData();
        if (this->gpsReader->isReady())
        {
            this->gpsData = this->gpsReader->getGpsData();
            this->displaySwitcher.writeFirstRow(
                this->gpsReader->getGpsDateTime(),
                this->localIpString);
            this->displaySwitcher.writeSecondRow(
                this->gpsReader->getGpsLatLng(),
                this->wifiClient->getLocalIP());
            this->displaySwitcher.switchDisplay();
            ResponseStruct *rp = this->client->get(this->gpsQueryKey, this->gpsData);
        }
        else
        {
            this->displaySwitcher.writeFirstRow(
                this->noGpsString,
                this->localIpString);
            this->displaySwitcher.writeSecondRow(
                this->wifiClient->getLocalIP(),
                this->wifiClient->getLocalIP());
        }
    }
}
