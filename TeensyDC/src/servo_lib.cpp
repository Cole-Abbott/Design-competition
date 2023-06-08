#include <Servo.h>
#include "servo_lib.h"

Servo servo;

double servo_angle;
int servo_dir;
double MAX_SWEEP_ANGLE;
double MIN_SWEEP_ANGLE;
unsigned long prev_time;
double inc;
const unsigned int inc_time = 10; // update at 100 Hz


void servo_Startup(int pin, double min, double max, double sweepTime){
    servo.attach(pin);

    prev_time = millis();
    MAX_SWEEP_ANGLE = max;
    MIN_SWEEP_ANGLE = min;

    servo_dir = 0; // forward
    servo_angle = MIN_SWEEP_ANGLE;

    inc = (MAX_SWEEP_ANGLE - MIN_SWEEP_ANGLE) * (inc_time/1000.0) / sweepTime; // sweep every sweepTime seconds

    servo.write(MIN_SWEEP_ANGLE); // start at min

    //servo.write((min + max) / 2);
    //while(1){}
}

int servo_Sweep(){
    int changed_dir = 0;
    if(servo_dir == 0 && millis() > prev_time + inc_time){
        servo_angle += inc;  // rotate 180° every second
        prev_time = millis();
        if(servo_angle >= MAX_SWEEP_ANGLE){
        servo_dir = 1;
        changed_dir = 1; // to return the fact that we changed directions
        }
    } else if (servo_dir == 1 && millis() > prev_time + inc_time){
        servo_angle -= inc;  // rotate 180° every second
        prev_time = millis();
        if(servo_angle <= MIN_SWEEP_ANGLE){
            servo_dir = 0;
            changed_dir = 1; // to return the fact that we changed directions
        }
    }
    servo.write((int)servo_angle);
    return changed_dir;
}

double servo_GetAngle(){
    return servo_angle;
}