#include <GpsData.h>

GpsData::GpsData() {}

char* GpsData::getGpsData() {
    if(this->isDateTimeReady && this->isLocationReady)
        sprintf(this->allData, "%s,%s", this->getGpsDateTime(), this->getGpsLatLng());
    return this->allData;
}
char* GpsData::getGpsDateTime() {
    if (this->isDateTimeReady) {
        sprintf(
            this->dateTime,
            "%02d/%02d/%02d %02d:%02d:%02d",
            this->month,
            this->day,
            this->year,
            this->hour,
            this->minute,
            this->second
        );
    }
    return this->dateTime;
}
char* GpsData::getGpsLatLng() {
    if (this->isLocationReady) {
        dtostrf(this->latitude, 4, 10, this->lat);
        dtostrf(this->longitude, 4, 10, this->lng);
        sprintf(this->latLng, "%s,%s", this->lat, this->lng);
    }
    return this->latLng;
}