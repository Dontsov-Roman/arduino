#ifndef GPS_CAR_H
#define GPS_CAR_H
#define GPS_QUERY_KEY "gps"
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <GpsReader.h>
#include <SimpleTimeout.h>
#include <ISimpleDisplay.h>
#include <SimpleDisplaySwitcher.h>
#include <IHttpClient.h>
#include <IWifiClient.h>

class GpsCar
{
public:
    GpsCar(
        GpsReader *gpsReader,
        IWifiClient *wifiClient,
        IHttpClient *client,
        ISimpleDisplay *display);

    GpsCar(
        GpsReader *gpsReader,
        IWifiClient *wifiClient,
        IHttpClient *client,
        ISimpleDisplay *display,
        int loopTimeout);
    void begin();
    void loop();

protected:
    GpsReader *gpsReader;
    IWifiClient *wifiClient;
    IHttpClient *client;
    ISimpleDisplay *display;
    SimpleDisplaySwitcher displaySwitcher;
    SimpleTimeout timeout;

    const char *gpsQueryKey = GPS_QUERY_KEY;
    char *gpsData;
    char *gpsDateTime;
    char *gpsLatLng;
    String localIpString = "Local IP:";
    String noGpsString = "No Gps Signal";
};
#endif