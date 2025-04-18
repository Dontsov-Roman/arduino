#ifndef GPS_HOME_DISPLAY_H
#define GPS_HOME_DISPLAY_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <SimpleTimeout.h>
#include <ISimpleDisplay.h>
#include <SimpleDisplaySwitcher.h>
#include <IHttpClient.h>
#include <IWifiClient.h>
#include <GpsData.h>
#include <SimpleToggleSensor.h>
#include <NtpTime.h>

class GpsHomeDisplay
{
public:
    GpsHomeDisplay(
        IWifiClient *wifiClient,
        IHttpClient *gpsHttpClient,
        ISimpleDisplay *display,
        SimpleToggleSensor *button,
        NtpTime *ntpTime,
        SimpleTimeout *getGpsTimeout,
        SimpleTimeout *initializationTimeout,
        SimpleTimeout *displaySwitchTimeout,
        SimpleTimeout *reconnectionTimeout);
    void begin();
    void loop();

private:
    IWifiClient *wifiClient;
    IHttpClient *gpsHttpClient;
    ISimpleDisplay *display;
    SimpleToggleSensor *button;
    SimpleTimeout *getGpsTimeout;
    SimpleTimeout *initializationTimeout;
    SimpleTimeout *displaySwitchTimeout;
    SimpleTimeout *reconnectionTimeout;
    SimpleDisplaySwitcher displaySwitcher;
    GpsData gpsData;
    NtpTime *ntpTime;
    bool previousButtonState = false;
    void reconnect();
    void toggleLight();
    String turnOnLightUrl = "/led/1";
    String turnOffLightUrl = "/led/0";
};
#endif
