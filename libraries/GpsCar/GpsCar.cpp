#include <GpsCar.h>
#include <SimpleTimeout.h>
#include <ResponseStruct.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    IHttpClient *client,
    ISimpleDisplay *display)
{
    this->gpsReader = gpsReader;
    this->client = client;
    this->display = display;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
}

void GpsCar::begin()
{
    this->display->begin();
    this->timeout.checkTimeout();
    do
    {
        delay(1000);
    } while (!this->timeout.checkTimeout());
    this->client->begin();
    this->display->clear();
    this->display->writeFirstRow(this->localIpString);
    this->display->writeSecondRow(this->client->getLocalIP());
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
                this->client->getLocalIP());
            this->displaySwitcher.switchDisplay();
            ResponseStruct *rp = this->client->get(this->gpsQueryKey, this->gpsData);
            Serial.println(rp->code);
            Serial.println(rp->response);
        }
        else
        {
            this->displaySwitcher.writeFirstRow(
                this->noGpsString,
                this->localIpString);
            this->displaySwitcher.writeSecondRow(
                this->client->getLocalIP(),
                this->client->getLocalIP());
        }
    }
}
