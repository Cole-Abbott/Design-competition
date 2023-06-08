#include "sensors.h"
#include <Arduino.h>
#include <IntervalTimer.h>


#define LINE_THRESHOLD 400

//IntervalTimer sensorTimer;

void (*callback)();
int callbackLineCount;

//setup the line sensor
void sensorSetup(int lineCount, void (*kick)()) {
    pinMode(A6, INPUT);
    callback = kick;
    callbackLineCount = lineCount;
    //sensorTimer.begin(readPhotoTransistor, 100000);

}

//read the line sensor
void readPhotoTransistor() {
    static int lineCount = 0;
    static bool onLine = false;

    int phototrasistorVoltage = analogRead(A6);

    //check if the phototrasistor is on the line
    if (phototrasistorVoltage < LINE_THRESHOLD) {
        if (!onLine) { //if the phototrasistor was not on the line last time
            lineCount++; //increment the line count
            onLine = true; //set the onLine variable to true
        }
    } else { //if the phototrasistor is not on the line
        onLine = false;
    }

    //if the line count is equal to the callback line count, call the callback function
    if (lineCount == callbackLineCount) {
        lineCount = 0;
        callback();
    }



}