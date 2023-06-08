#ifndef photo
#define photo

#include <Arduino.h>

// run before everything else
void photo_Startup(int pin, double angle_target);

// run every loop.
// returns 1 if hits target.
// takes in the current angle of the servo, so it can record it if it hits.
int photo_Read(double servo_angle);

// returns 1 if a result was found, 0 if it needs to keep sweeping
// assigns "result" proportional to how far we need to steer, with + being left and - being right
// NOTE: MUST BE CALLED BEFORE FindGoalie()
int photo_Steer(int* result);

// run every loop.
// returns 1 if a result was found, 0 if it needs to keep sweeping
// assigns "result" to 0 if goalie is on LEFT, 1 if goalie is on RIGHT
int photo_FindGoalie(int* result);

// used to avoid getting "out of sync" with the servo
void photo_Reset(void);

// get current value of phototransistor, from 0 to 1024
int photo_GetValue(void);

#endif
