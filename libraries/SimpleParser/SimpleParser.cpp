#include <SimpleParser.h>

SimpleParser::SimpleParser() {
    this->delimiter = ',';
    this->startIndex = 0;
    this->endIndex = 0;
}

SimpleParser::SimpleParser(char delimiter) {
    this->delimiter = delimiter;
    this->startIndex = 0;
    this->endIndex = 0;
}

SimpleParser::SimpleParser(char delimiter, String parseString) {
    this->delimiter = delimiter;
    this->parseString = parseString;
    this->startIndex = 0;
    this->endIndex = 0;
}

void SimpleParser::setParseString(String parseString) {
    this->parseString = parseString;
}

String SimpleParser::parse(String str, int startIndex) {
    this->endIndex = str.indexOf(this->delimiter, startIndex);
    this->tempString = str.substring(startIndex + 1, this->endIndex);
    this->endIndex = 0;
    return this->tempString;
}

String SimpleParser::parse(String str) {
    this->endIndex = str.indexOf(this->delimiter, this->startIndex);
    this->tempString = str.substring(this->startIndex, this->endIndex);
    this->startIndex = this->endIndex + 1;
    return this->tempString;
}
String SimpleParser::getNextValue() {
    return this->parse(this->parseString);
}

void SimpleParser::resetIndexes() {
    this->startIndex = 0;
    this->endIndex = 0;
}