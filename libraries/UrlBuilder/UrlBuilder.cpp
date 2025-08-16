#include "UrlBuilder.h"

UrlBuilder::UrlBuilder() { resetAll(); }
UrlBuilder::UrlBuilder(char *base)
{
    resetAll();
    setBase(base);
}

bool UrlBuilder::setBase(char *base)
{
    this->baseNoQuery = String(base);
}

bool UrlBuilder::addParam(const char *key, const char *value)
{
    if (value != NULL && key != NULL)
    {
        safeCopy(params[this->paramCount].value, value, sizeof(params[this->paramCount].value));
        safeCopy(params[this->paramCount].key, key, sizeof(params[this->paramCount].key));

        this->params[this->paramCount].hasValue = true;
        this->params[this->paramCount].used = true;
        this->paramCount += 1;
        return true;
    }
    return false;
}

bool UrlBuilder::setParam(const char *key, const char *value)
{
    if (!key || !value)
        return false;
    bool replaced = false;
    for (uint16_t i = 0; i < MAX_PARAMS; ++i)
    {
        if (params[i].used && strcmp(params[i].key, key) == 0)
        {
            safeCopy(params[i].value, value, sizeof(params[i].value));
            params[i].used = true;
            params[i].hasValue = true;
            replaced = true;
        }
    }
    return replaced;
}

bool UrlBuilder::removeParam(const char *key)
{
    if (!key)
        return false;
    bool removed = false;
    for (uint16_t i = 0; i < MAX_PARAMS; ++i)
    {
        if (params[i].used && strcmp(params[i].key, key) == 0)
        {
            params[i].used = false;
            params[i].hasValue = false;
            removed = true;
        }
    }
    return removed;
}

void UrlBuilder::clearParams()
{
    for (uint16_t i = 0; i < MAX_PARAMS; ++i)
        params[i].used = false;
    paramCount = 0;
}

String UrlBuilder::build()
{
    String query;
    query += "?";
    for (uint16_t i = 0; i < MAX_PARAMS; ++i)
    {
        if (params[i].hasValue && params[i].used)
        {
            if (query.length() > 1)
            {
                query += "&";
            }
            query += params[i].key;
            query += "=";
            query += params[i].value;
        }
    }
    return String(this->baseNoQuery) + query;
}

void UrlBuilder::resetAll()
{
    baseNoQuery = String("");
    clearParams();
}

void UrlBuilder::safeCopy(char *dst, const char *src, size_t dstCap)
{
    if (!dst || !dstCap)
        return;
    if (!src)
    {
        dst[0] = '\0';
        return;
    }
    size_t n = strlen(src);
    if (n >= dstCap)
        n = dstCap - 1;
    memcpy(dst, src, n);
    dst[n] = '\0';
}