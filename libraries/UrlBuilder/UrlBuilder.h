#ifndef URL_BUILDER_H
#define URL_BUILDER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class UrlBuilder
{
public:
    static const uint16_t MAX_URL_LEN = 512;
    static const uint16_t MAX_PARAMS = 16;
    static const uint16_t MAX_KEY_LEN = 64;
    static const uint16_t MAX_VAL_LEN = 128;

    struct Pair
    {
        char key[MAX_KEY_LEN];
        char value[MAX_VAL_LEN];
        bool hasValue;
        bool used;
    };

    UrlBuilder();
    UrlBuilder(char *base);

    bool setBase(char *base);
    bool addParam(const char *key, const char *value);
    bool setParam(const char *key, const char *value);
    bool removeParam(const char *key);
    void clearParams();
    String build();

private:
    String baseNoQuery;
    Pair params[MAX_PARAMS];
    uint16_t paramCount = 0;

    static void safeCopy(char *dst, const char *src, size_t dstCap);
    void resetAll();
};
#endif
