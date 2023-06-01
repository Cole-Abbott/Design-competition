#include "sensors.h"
#include <Arduino.h>
#include <IntervalTimer.h>


#define LINE_THRESHOLD 400

IntervalTimer sensorTimer;
void readPhotoTransistor();

void (*callback)();
int callbackLineCount;

void sensorSetup(int lineCount, void (*kick)()) {
    pinMode(A8, INPUT);
    callback = kick;
    callbackLineCount = lineCount;
    sensorTimer.begin(readPhotoTransistor, 10000);

}

void readPhotoTransistor() {
    static int lineCount = 0;
    static bool onLine = false;

    int phototrasistorVoltage = analogRead(A8);

    if (phototrasistorVoltage < LINE_THRESHOLD) {
        if (!onLine) {
            lineCount++;
            onLine = true;
        }
    } else {
        onLine = false;
    }

    if (lineCount == callbackLineCount) {
        Serial.println("Line count reached");
        callback();
        lineCount = 0;
    }



}