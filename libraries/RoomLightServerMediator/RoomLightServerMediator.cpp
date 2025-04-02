#include <RoomLightServerMediator.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <ResponseCodes.h>
#include <StreamString.h>

ResponseCodes responseCodes;
RoomLightServerMediator::RoomLightServerMediator()
{
    this->isLastRequestInvalid = false;
}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server)
{
    this->serial = serial;
    this->server = server;
    this->isLastRequestInvalid = false;
}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server, String token)
{
    this->serial = serial;
    this->server = server;
    this->isLastRequestInvalid = false;
    this->token = token;
}

RoomLightServerMediator::RoomLightServerMediator(RoomLightSerial *serial, ESP8266WebServer *server, String token, String thingId)
{
    this->serial = serial;
    this->server = server;
    this->isLastRequestInvalid = false;
    this->token = token;
    this->thingId = thingId;
}

void RoomLightServerMediator::begin(const char *ssid, const char *password)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(F("."));
    }

    // Print the IP address
    this->localIp = WiFi.localIP().toString();
    Serial.println(this->localIp);

    MDNS.begin(this->localIp);

    this->httpUpdater.setup(this->server);
    // Start the server
    this->server->on("/", std::bind(&RoomLightServerMediator::rootHandler, this));
    this->server->on("/led/1", std::bind(&RoomLightServerMediator::ledOnHandler, this));
    this->server->on("/led/0", std::bind(&RoomLightServerMediator::ledOffHandler, this));
    this->server->on("/movement", std::bind(&RoomLightServerMediator::movementModeHandler, this));
    this->server->on("/sendlocalip", std::bind(&RoomLightServerMediator::sendWifiLocalIpHandler, this));
    this->server->on("/set-gps", std::bind(&RoomLightServerMediator::setGpsHandler, this));
    this->server->on("/get-gps", std::bind(&RoomLightServerMediator::getGpsHandler, this));
    this->server->onNotFound(std::bind(&RoomLightServerMediator::notFoundHandler, this));

    // ask server to track these headers
    const char *headerkeys[] = {AUTHORIZATION_HEADER};
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
    this->server->collectHeaders(headerkeys, headerkeyssize);

    this->server->begin();
}

bool RoomLightServerMediator::isAuthenticated()
{
    if (this->server->hasHeader(AUTHORIZATION_HEADER) && this->server->header(AUTHORIZATION_HEADER) == this->token)
    {
        return true;
    }
    this->server->send(responseCodes.unAuthCode, responseCodes.textPlain, "");
    return false;
}

void RoomLightServerMediator::ledOnHandler()
{
    if (this->isAuthenticated())
    {
        this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
        this->serial->write(SwitchOnCommand);
    }
}

void RoomLightServerMediator::ledOffHandler()
{
    if (this->isAuthenticated())
    {
        this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
        this->serial->write(SwitchOffCommand);
    }
}

void RoomLightServerMediator::movementModeHandler()
{
    if (this->isAuthenticated())
    {
        this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
        this->serial->write(MovementModeCommand);
    }
}

void RoomLightServerMediator::sendWifiLocalIpHandler()
{
    if (this->isAuthenticated())
    {
        this->server->send(responseCodes.okCode, responseCodes.textPlain, "");
        this->sendWiFiLocalIp();
    }
}
String RoomLightServerMediator::getLastGpsData()
{
    String content = "Time: ";
    content += this->lastGpsData.getGpsDateTime();
    content += ", Coordinates: ";
    content += this->lastGpsData.getGpsLatLng();
    return content;
}
void RoomLightServerMediator::setGpsHandler()
{
    String gpsData = this->server->arg("gps");
    this->lastGpsData.parse(gpsData);

    this->server->send(
        responseCodes.okCode,
        responseCodes.textPlain,
        "Ok. " + this->getLastGpsData());
}

void RoomLightServerMediator::getGpsHandler()
{
    if (this->isAuthenticated())
    {
        this->server->send(responseCodes.okCode, responseCodes.textPlain, this->lastGpsData.getGpsData());
    }
}

void RoomLightServerMediator::notFoundHandler()
{
    this->server->send(responseCodes.notFoundCode, responseCodes.textPlain, "");
}
void RoomLightServerMediator::rootHandler()
{
    this->server->send(responseCodes.okCode, responseCodes.textHtml, this->getTemplate());
}
void RoomLightServerMediator::sendWiFiLocalIp()
{
    this->serial->write(SetLocalIpCommand, this->localIp);
}

void RoomLightServerMediator::toggle()
{
    this->server->handleClient();
    this->client = server->client();
    if (this->simpleTimeout.checkTimeout())
    {
        this->sendWiFiLocalIp();
    }
}
const char *RoomLightServerMediator::getTemplate()
{
    StreamString streamString;
    streamString.reserve(500);
    streamString.printf("\
        <html>\
            <head>\
            <title>Room Light Server</title>\
            <style>\
                body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; color: #000088; font-size: 2rem; }\
                button { font-size: 4rem; }\
                ul { text-align: center; }\
                li { margin: 2rem; }\
            </style>\
            <script>\
                function get(url) { fetch(url); };\
                function post(url, body) { fetch(url, { method: 'POST', body:body }); };\
            </script>\
            </head>\
            <body>\
            <div>%s</div>\
            <div>%s</div>\
            <ul>\
                <li>\
                    <button onclick=get('/led/1')>Switch On</button>\
                </li>\
                <li>\
                    <button onclick=get('/led/0')>Switch Off</button>\
                </li>\
                <li>\
                    <button onclick=get('/movement')>Movement mode</button>\
                </li>\
                <li>\
                    <button onclick=get('/sendlocalip')>Send Local Ip</button>\
                </li>\
            </ul>\
            </body>\
        </html>",
                        this->localIp, this->lastGpsData.getGpsData());
    return streamString.c_str();
}
