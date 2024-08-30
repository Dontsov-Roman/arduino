#include <GpsCar.h>
#include <SimpleTimeout.h>
#include <ResponseStruct.h>

GpsCar::GpsCar(
    GpsReader *gpsReader,
    WifiHttpClient *client
) {
    this->gpsReader = gpsReader;
    this->client = client;
    this->timeout = SimpleTimeout(10000);
    sprintf(this->gpsQueryKey, "%s", "gps");
}

void GpsCar::begin() {
    this->timeout.checkTimeout();
    do {
        delay(1000);
    } while(!this->timeout.checkTimeout());
    this->client->begin();
}
void GpsCar::loop() {
    this->gpsReader->readGpsData();
    if(this->timeout.checkTimeout() && this->gpsReader->isReady()) {
        char* data = this->gpsReader->getGpsData();
        ResponseStruct *rp = this->client->post(data, this->gpsQueryKey, data);
        Serial.println(rp->code);
    }
}
