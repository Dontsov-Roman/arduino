#include <NtpTime.h>

NtpTime::NtpTime(SimpleTimeout *timeout, const char *ntpServer)
{
    this->timeout = timeout;
    this->ntpServer = ntpServer;
}
NtpTime::NtpTime(SimpleTimeout *timeout, const char *ntpServer, const long gmtOffset)
{
    this->timeout = timeout;
    this->ntpServer = ntpServer;
    this->gmtOffset = gmtOffset;
}
NtpTime::NtpTime(SimpleTimeout *timeout, const char *ntpServer, const long gmtOffset, const int dayLightOffset)
{
    this->timeout = timeout;
    this->ntpServer = ntpServer;
    this->gmtOffset = gmtOffset;
    this->dayLightOffset = dayLightOffset;
}
void NtpTime::begin()
{
    configTime(this->gmtOffset, this->dayLightOffset, this->ntpServer);
}
void NtpTime::fetchTime()
{
    getLocalTime(&this->timeStruct);
    strftime(this->time, 9, "%H:%M:%S", &this->timeStruct);
    strftime(this->date, 9, "%D", &this->timeStruct);
    strftime(this->day, 12, "%b %d, %a", &this->timeStruct);
    strftime(this->dayTime, sizeof(this->dayTime), "%d %b, %a %H:%M:%S", &this->timeStruct);

    if (!this->launched)
    {
        this->launched = true;
        strftime(this->launchTime, sizeof(this->launchTime), "%d %b, %a %H:%M:%S", &this->timeStruct);
    }
}
tm *NtpTime::getTimeStruct()
{
    return &this->timeStruct;
}
void NtpTime::loop()
{
    if (this->timeout->checkTimeout())
    {
        this->fetchTime();
    }
}
char *NtpTime::getTime()
{
    return this->time;
}
char *NtpTime::getDay()
{
    return this->day;
}

char *NtpTime::getDayTime()
{
    return this->dayTime;
}
char *NtpTime::getDate()
{
    return this->date;
}
char *NtpTime::getLaunchTime()
{
    return this->launchTime;
}