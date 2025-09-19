#include <GpsData.h>
#include <SimpleParser.h>

GpsData::GpsData() {}

char *GpsData::getGpsData()
{
    if (this->isDateTimeReady && this->isLocationReady)
        sprintf(this->allData, "%s,%s", this->getGpsDateTime(), this->getGpsLatLng());
    return this->allData;
}
char *GpsData::getGpsDateTime()
{
    if (this->isDateTimeReady)
    {
        sprintf(
            this->dateTime,
            "%02d/%02d/%02d,%02d:%02d:%02d",
            this->month,
            this->day,
            this->year,
            this->hour,
            this->minute,
            this->second);
    }
    return this->dateTime;
}
char *GpsData::getGpsLatLng()
{
    if (this->isLocationReady)
    {
        dtostrf(this->latitude, 4, 10, this->lat);
        dtostrf(this->longitude, 4, 10, this->lng);
        sprintf(this->latLng, "%s,%s", this->lat, this->lng);
    }
    return this->latLng;
}

double GpsData::toRadians(double degree)
{
    return degree * M_PI / 180.0;
}

double GpsData::getDistanceTo(double lat, double lon)
{
    if (!this->latitude || !this->longitude)
    {
        return 0;
    }
    double dLat = this->toRadians(lat - this->latitude);
    double dLon = this->toRadians(lon - this->longitude);

    double lat1 = toRadians(this->latitude);
    lat = toRadians(lat);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat) *
                   sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c;
}
void GpsData::parse(String str)
{
    this->commandParser.resetIndexes();
    this->dateParser.resetIndexes();
    this->timeParser.resetIndexes();
    this->commandParser.setParseString(str);

    this->dateParser.setParseString(commandParser.getNextValue());
    this->timeParser.setParseString(commandParser.getNextValue());

    this->latitude = commandParser.getNextValue().toDouble();
    this->longitude = commandParser.getNextValue().toDouble();

    this->month = dateParser.getNextValue().toInt();
    this->day = dateParser.getNextValue().toInt();
    this->year = dateParser.getNextValue().toInt();

    this->hour = timeParser.getNextValue().toInt();
    this->minute = timeParser.getNextValue().toInt();
    this->second = timeParser.getNextValue().toInt();

    this->isDateTimeReady = true;
    this->isLocationReady = true;
}