#ifndef SIMPLE_PARSER_H
#define SIMPLE_PARSER_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class SimpleParser {
    public:
        SimpleParser();
        SimpleParser(char del);
        SimpleParser(char del, String parseString);
        String getNextValue();
        String parse(String str);
        String parse(String str, int startIndex);
        void resetIndexes();
        void setParseString(String parseString);
    protected:
        String tempString;
        String parseString;
        char delimiter;
        int startIndex;
        int endIndex;
};
#endif