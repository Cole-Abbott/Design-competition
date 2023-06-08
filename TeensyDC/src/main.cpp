#include <Arduino.h>
#include "motors.h"
#include "sensors.h"
#include "phototransistor.h"
#include "servo_lib.h"

void line();

#define MAX_SWEEP_ANGLE 180
#define MIN_SWEEP_ANGLE 0

#define Kp .7 // proportional gain for steering

const int photoPin = A3;  // pin 16
const int servoPin = 9;
const int laserPin = 10;

const double angle_target = 115;

static volatile int lineCOunt = 0;

int loopCount = 0;

void setup() {
  Serial.begin(9600);

  motorSetup();
  kickerSevoAngle(0);

  setMotorSpeeds(100, 100);
  sensorSetup(1, line);

  // Servo setup
  servo_Startup(servoPin, MIN_SWEEP_ANGLE, MAX_SWEEP_ANGLE, 0.5); // servo that sweeps from 0° to 90° over 3 seconds

  // Phototransistor setup
  photo_Startup(photoPin, angle_target);

  // Laser setup
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); // turn laser on



}

void loop() {
  delay(10);
  // put your main code here, to run repeatedly:
  static int steerDir = 0;
  static int shootDir = 0;

  static int leftVelocity = 100;
  static int rightVelocity = 100;

  //read line sensor
  readPhotoTransistor();

  // update phototransistor
  photo_Read(servo_GetAngle());


  if (photo_Steer(&steerDir)){ // photo_Steer() must be called BEFORE photo_FindGoalie()
      Serial.println(steerDir);
      leftVelocity = 100 - steerDir * Kp;
      rightVelocity = 100 + steerDir * Kp;
      setMotorSpeeds(leftVelocity, rightVelocity);
  }


  photo_FindGoalie(&shootDir);
   
  // Sweep servo
  // To avoid getting out of sync with our laser system, we reset it every time the servo changes direction.
  if(servo_Sweep() == 1){ // servo changed directions this loop
    photo_Reset();
  }

  if (lineCOunt == 6) { // if we have seen 6 lines keep driving for 0.1s and kick the ball
    setMotorSpeeds(100, 100);
    delay(1200); // time to go 6in, subtract time to kick, also turn
    
    //turn
    if (shootDir == 0) { //goalie on left, turn right to shoot for right
      setMotorSpeeds(200, 100);
    } else {
      setMotorSpeeds(100, 200);
    }

    delay(400);

    //kick
    kickerSevoAngle(180);

    setMotorSpeeds(0, 0);
    while(1){} //stop for now
  }

}

//callback function for line sensor
void line() {
  Serial.println("line");
  lineCOunt++;
}