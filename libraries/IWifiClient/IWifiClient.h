#ifndef ABSTRACT_WIFI_CLIENT_H
#define ABSTRACT_WIFI_CLIENT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class IWifiClient
{
public:
    virtual void begin();
    virtual bool isConnected();
    virtual String getLocalIP();
};
#endif
