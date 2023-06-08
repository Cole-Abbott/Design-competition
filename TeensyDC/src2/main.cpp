#include <Arduino.h>
#include "phototransistor.h"
#include "servo_lib.h"

#define MAX_SWEEP_ANGLE 180
#define MIN_SWEEP_ANGLE 0

const int photoPin = A2;  // pin 16
const int servoPin = 9;
const int laserPin = 10;

const double angle_target = 90;


void setup() {
  Serial.begin(9600);

  // Servo setup
  servo_Startup(servoPin, MIN_SWEEP_ANGLE, MAX_SWEEP_ANGLE, 3); // servo that sweeps from 0° to 90° over 3 seconds

  // Phototransistor setup
  photo_Startup(photoPin, angle_target);

  // Laser setup
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW); // turn laser on
}

void loop() {

  static int left_or_right = 0; // 0 = goalie on left, 1 = goalie on right. Or 0 = steer left, 1 = steer right

  // update phototransistor
  if (photo_Read(servo_GetAngle())){
    Serial.println("HIT");
  }
  if(photo_Steer(&left_or_right)){  // photo_Steer() must be called BEFORE photo_FindGoalie()
    if(left_or_right == 0){ // we need to steer left...
      Serial.println("Steer left!");
    } else{
      Serial.println("Steer right!");
    }
  }
  if(photo_FindGoalie(&left_or_right)){
    if(left_or_right == 0){ // goalie is on the left...
      Serial.println("Shoot for the RIGHT!");
    } else{                 // goalie is on the right...
      Serial.println("Shoot for the LEFT!");
    }
  }

  // Sweep servo
  // To avoid getting out of sync with our laser system, we reset it every time the servo changes direction.
  if(servo_Sweep() == 1){ // servo changed directions this loop
    photo_Reset();
  }
}