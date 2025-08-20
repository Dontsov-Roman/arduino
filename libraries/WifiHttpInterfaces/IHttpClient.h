#ifndef I_HTTP_CLIENT_H
#define I_HTTP_CLIENT_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ResponseStruct.h>

#define HTTP_METHOD_GET "GET"
#define HTTP_METHOD_POST "POST"
#define HTTP_METHOD_PUT "PUT"
#define HTTP_METHOD_PATCH "PATCH"
#define HTTP_METHOD_DELETE "DELETE"
#define HTTP_HEADER_CONTENT_LENGTH "Content-Length"
#define HTTP_HEADER_CONTENT_TYPE "Content-Type"
#define HTTP_HEADER_CONNECTION "Connection"
#define HTTP_HEADER_TRANSFER_ENCODING "Transfer-Encoding"
#define HTTP_HEADER_USER_AGENT "User-Agent"
#define HTTP_HEADER_VALUE_CHUNKED "chunked"

class IHttpClient
{
public:
    virtual void begin();
    virtual ResponseStruct *get();
    virtual ResponseStruct *get(String url);
    virtual ResponseStruct *get(String key, String value);
    virtual ResponseStruct *post(char *body);
    virtual ResponseStruct *post(char *body, String key, String value);
    virtual void setHost(const char *host);
    virtual void setSecure(bool isSecure);
    virtual void setTimeout(int timeout);
};
#endif
