#ifndef servo_lib
#define servo_lib

#include <Arduino.h>

// run before everything else.
// "max" and "min" and the sweeping range
void servo_Startup(int pin, double max, double min, double sweepTime);

// run every loop
// returns a 1 if the servo changed direction on this call of the function, 0 otherwise
int servo_Sweep();

// returns current angle of the servo
double servo_GetAngle();

#endif