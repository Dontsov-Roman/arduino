#include <GpsData.h>

GpsData::GpsData() {}

char* GpsData::getGpsData() {
    sprintf(this->allData, "%s,%s", this->getGpsDateTime(), this->getGpsLatLng());
    return this->allData;
}
char* GpsData::getGpsDateTime() {
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
    
    return this->dateTime;
}
char* GpsData::getGpsLatLng() {
    dtostrf(this->latitude, 4, 8, this->lat);
    dtostrf(this->longitude, 4, 8, this->lng);
    sprintf(this->latLng, "%s,%s", this->lat, this->lng);
    return this->latLng;
}