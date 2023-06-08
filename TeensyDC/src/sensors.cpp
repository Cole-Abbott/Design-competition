#include "sensors.h"
#include <Arduino.h>
#include <IntervalTimer.h>


#define LINE_THRESHOLD 600

//IntervalTimer sensorTimer;

void (*callback)();
int callbackLineCount;

void sensorSetup(int lineCount, void (*kick)()) {
    pinMode(A6, INPUT);
    callback = kick;
    callbackLineCount = lineCount;
    //sensorTimer.begin(readPhotoTransistor, 100000);

}

void readPhotoTransistor() {
    static int lineCount = 0;
    static bool onLine = false;

    int phototrasistorVoltage = analogRead(A6);

    if (phototrasistorVoltage < LINE_THRESHOLD) {
        if (!onLine) {
            lineCount++;
            onLine = true;
        }
    } else {
        onLine = false;
    }

    if (lineCount == callbackLineCount) {
        lineCount = 0;
        callback();
    }



}