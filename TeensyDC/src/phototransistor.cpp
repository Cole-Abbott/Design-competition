#include "phototransistor.h"
#include <Arduino.h>


volatile int photoPin;
volatile double hit_angles_array[200];
volatile bool target_hit;
volatile int hits;
volatile double midpoint_target;

void photo_Startup(int pin, double angle_target){
    photoPin = pin;
    target_hit = false;
    hits = 0;
    midpoint_target = angle_target;
}

// returns 1 if hits target
int photo_Read(double servo_angle){

    int photoVal = photo_GetValue();
    
    if(photoVal > 150 && !target_hit){   // adjust sensitivity here

        target_hit = true;
        hits++;
        hit_angles_array[hits-1] = servo_angle; 
        return 1;
    } else if(photoVal < 100 && target_hit){
        target_hit = false;
    }

    return 0;
}


// returns 1 if a result was found, 0 if it needs to keep sweeping
// assigns "result" proportional to how far we need to steer, with + being left and - being right
// NOTE: MUST BE CALLED BEFORE FindGoalie()
int photo_Steer(int* result){
    if (hits == 3){  // we've seen 3 targets
        double left = hit_angles_array[2];
        double right = hit_angles_array[0];

        if (left < right){ // check that 3rd hit is the left goalpost
          right = left;     // if backwards, switch them.
          left = hit_angles_array[0];
        }

        double midpoint = (left + right) / 2;

        *result = midpoint - midpoint_target;
        return 1;
    }
    return 0; // not enough hits to do calculation
}

// returns 1 if a result was found, 0 if it needs to keep sweeping
// assigns "result" to 0 if goalie is on LEFT, 1 if goalie is on RIGHT
int photo_FindGoalie(int* result){
    if (hits >= 3){  // we've seen 3 targets
        hits = 0;      // reset hits counter and therefore the hit_angles_array[]

        double left = hit_angles_array[2];
        double goalie = hit_angles_array[1];
        double right = hit_angles_array[0];


        if (left < right){ // check that 3rd hit is the left goalpost
          right = left;     // if backwards, switch them.
          left = hit_angles_array[0];
        }

        float goal_width = left - right;
        if (goalie > goal_width/2 + right){ // goalie is on left side
          *result = 0;
          return 1;
        } else {                             // goalie on right side
          *result = 1;
          return 1;
        }
    }
    return 0;
}

void photo_Reset(void){
    hits = 0;
}

int photo_GetValue(void){
    return analogRead(photoPin);
}