#include <GpsCar.h>
#include <SimpleTimeout.h>
#include <ResponseStruct.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    WifiHttpClient *client,
    ISimpleDisplay *display
) {
    this->gpsReader = gpsReader;
    this->client = client;
    this->display = display;
    this->displaySwitcher = SimpleDisplaySwitcher(this->display);
}

void GpsCar::begin() {
    this->display->begin();
    this->timeout.checkTimeout();
    do {
        delay(1000);
    } while(!this->timeout.checkTimeout());
    this->client->begin();
}
void GpsCar::loop() {
    if(this->timeout.checkTimeout()) {
        this->gpsReader->readGpsData();
        if(this->gpsReader->isReady()){
            this->display->clear();
            this->gpsData = this->gpsReader->getGpsData();
            this->displaySwitcher.writeFirstRow(
                this->gpsReader->getGpsDateTime(),
                "Local IP:"
            );
            this->displaySwitcher.writeSecondRow(
                this->gpsReader->getGpsLatLng(),
                this->client->getLocalIP()
            );
            this->displaySwitcher.switchDisplay();
            // this->display->writeFirstRow(this->gpsReader->getGpsDateTime());
            // this->display->writeSecondRow(this->gpsReader->getGpsLatLng());
            ResponseStruct *rp = this->client->post(this->gpsData, this->gpsQueryKey, this->gpsData);
            Serial.println(this->gpsData);
        }
    }
}
