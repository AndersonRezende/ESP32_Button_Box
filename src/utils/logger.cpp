#include <Arduino.h>
#include "logger.h"

void initLogger(const int baud) {
    Serial.begin(baud);
}

void logPrintln(const char* text) {
    Serial.println(text);
}

void logPrintln(const int value) {
    Serial.println(value);
}

void logPrintln(const char value) {
    Serial.println(value);
}

void logPrint(const char* text) {
    Serial.print(text);
}

void logPrint(const int value) {
    Serial.print(value);
}

void logPrint(const char value) {
    Serial.print(value);
}