#include <GpsReader.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <GpsData.h>

GpsReader::GpsReader(SoftwareSerial *ss)
{
  this->ss = ss;
  this->gpsReadDelay = DEFAULT_GPS_READ_DELAY;
}

void GpsReader::readGpsData()
{
  unsigned long start = millis();
  do
  {
    while (ss->available())
    {
      gps.encode(ss->read());
    }
  } while (millis() - start < this->gpsReadDelay);
  if (this->gps.date.isValid() && this->gps.time.isValid())
  {
    this->gpsData.month = this->gps.date.month();
    this->gpsData.day = this->gps.date.day();
    this->gpsData.year = this->gps.date.year();
    this->gpsData.hour = this->gps.time.hour();
    this->gpsData.minute = this->gps.time.minute();
    this->gpsData.second = this->gps.time.second();
    this->gpsData.isDateTimeReady = true;
  }
  if (this->gps.location.isValid())
  {
    this->gpsData.latitude = this->gps.location.lat();
    this->gpsData.longitude = this->gps.location.lng();
    this->gpsData.isLocationReady = true;
  }
  this->fixTimeByGmt();
}

char *GpsReader::getGpsData()
{
  return this->gpsData.getGpsData();
}

char *GpsReader::getGpsDateTime()
{
  return this->gpsData.getGpsDateTime();
}

char *GpsReader::getGpsLatLng()
{
  return this->gpsData.getGpsLatLng();
}

bool GpsReader::isReady()
{
  // Serial.println("Date time is ready:");
  // Serial.println(this->gpsData.isDateTimeReady);
  // Serial.println("Location is ready:");
  // Serial.println(this->gpsData.isLocationReady);
  return this->gpsData.isDateTimeReady && this->gpsData.isLocationReady;
}

void GpsReader::fixTimeByGmt()
{
  if (this->isReady())
  {
    this->GMT = this->gpsData.latitude / 12;
    // Winter time
    if (this->gpsData.month > 10 || this->gpsData.month < 5)
    {
      this->GMT = this->GMT - 1;
    }
    // Fix next day
    if (this->gpsData.hour + GMT >= 24)
    {
      this->gpsData.hour = this->gpsData.hour + this->GMT - 24;
      this->gpsData.day = this->gpsData.day + 1;
    }
    else
    {
      this->gpsData.hour = this->gpsData.hour + this->GMT;
    }
  }
}