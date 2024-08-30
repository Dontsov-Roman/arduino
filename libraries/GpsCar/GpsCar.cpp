#include <GpsCar.h>
#include <SimpleTimeout.h>
#include <ResponseStruct.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    WifiHttpClient *client
) {
    this->gpsReader = gpsReader;
    this->client = client;
}

void GpsCar::begin() {
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
            this->gpsData = this->gpsReader->getGpsData();
            ResponseStruct *rp = this->client->post(this->gpsData, this->gpsQueryKey, this->gpsData);
        }
    }
}
