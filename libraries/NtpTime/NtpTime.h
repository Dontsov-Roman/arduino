#ifndef NTP_TIME_H
#define NTP_TIME_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <time.h>
#include <SimpleTimeout.h>
class NtpTime
{
public:
    NtpTime(SimpleTimeout *timeout, const char *ntpServer);
    NtpTime(SimpleTimeout *timeout, const char *ntpServer, long gmtOffset);
    NtpTime(SimpleTimeout *timeout, const char *ntpServer, long gmtOffset, int dayLightOffset);
    void begin();
    void fetchTime();
    void loop();
    tm *getTimeStruct();
    char *getTime();
    char *getDate();
    char *getDay();
    char *getDayTime();

private:
    tm timeStruct;
    SimpleTimeout *timeout;
    const char *ntpServer;
    long gmtOffset = 7200;
    int dayLightOffset = 3600;
    char time[9];
    char date[9];
    char day[12];
    char dayTime[16];
};
#endif
