#include <GpsReader.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

GpsReader::GpsReader(SoftwareSerial *ss) {
    this->gps = TinyGPSPlus();
    this->ss = ss;
    this->gpsReadDelay = DEFAULT_GPS_READ_DELAY;
}

void GpsReader::readGpsData() {
  unsigned long start = millis();
  do 
  {
    while (ss->available())
      gps.encode(ss->read());
  } while (millis() - start < this->gpsReadDelay);
}

char* GpsReader::getGpsData() {
    sprintf(this->allData, "%s,%s", this->getGpsDateTime(), this->getGpsLatLng());
    return this->allData;
}
char* GpsReader::getGpsDateTime() {
    if (this->gps.date.isValid() && this->gps.time.isValid()) {
        sprintf(
            this->dateTime,
            "%02d/%02d/%02d %02d:%02d:%02d",
            this->gps.date.month(),
            this->gps.date.day(),
            this->gps.date.year(),
            this->gps.time.hour(),
            this->gps.time.minute(),
            this->gps.time.second()
        );
    }
    
    return this->dateTime;
}
char* GpsReader::getGpsLatLng() {
    if (this->gps.location.isValid()) {
        dtostrf(this->gps.location.lat(), 4, 10, this->lat);
        dtostrf(this->gps.location.lng(), 4, 10, this->lng);
        sprintf(this->latLng, "%s,%s", this->lat, this->lng);
    }
    Serial.println(this->gps.location.isValid());
    
    return this->latLng;
}