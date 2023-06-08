#include <Arduino.h>
#include <Servo.h>
#include <Encoder.h>
#include <IntervalTimer.h>
#include "motors.h"

IntervalTimer myTimer;

//create a servo object for kicker
Servo kickerServo;

// motor pins
int leftPWM = 3;
int leftDIR = 0;
int rightPWM = 2;
int rightDIR = 1;

// encoder pins
int leftEncoderA = 4;
int leftEncoderB = 5;
int rightEncoderA = 6;
int rightEncoderB = 7;

// swap A and B if turning the motor forwards gives a negative position
Encoder encoderLeft(leftEncoderA, leftEncoderB);
Encoder encoderRight(rightEncoderB, rightEncoderA);
long encoderCountLeft  = 0;
long encoderCountRight = 0;

// variables shared between loop() and motorPID()
volatile float desiredLeftVelocity = 0;
volatile float desiredRightVelocity = 0;
volatile float KP = 0.05; // how hard to try to follow the desired velocity

void motorPID();

void motorSetup() {

  //attach the servo to pin 9
  kickerServo.attach(22);
  //set the servo to 0 degrees
  kickerServo.write(0);

  //left motor
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);

  //right motor
  pinMode(rightPWM, OUTPUT);
  pinMode(rightDIR, OUTPUT);
  analogWrite(rightPWM, 0);
  digitalWrite(rightDIR, LOW);

  // turn on the automatic function call to control the motor velocities
  myTimer.begin(motorPID, 10000);  //(in microseconds) run motorPID() every 0.01s (100Hz)

}

void motorPID() {
  static float prevLeftAngle = 0;
  static float prevRightAngle = 0;
  static int leftDuty = 0;
  static int rightDuty = 0;

  float leftAngle, leftVelocity;
  float rightAngle, rightVelocity;

  // calculate the motor angles
  encoderCountLeft = encoderLeft.read();
  encoderCountRight = encoderRight.read();
  leftAngle = encoderCountLeft * 360.0 / 1632.0;
  rightAngle = encoderCountRight * 360.0 / 1632.0;

  // calculate the motor velocities (to do: filter for smoothness)
  leftVelocity = (leftAngle - prevLeftAngle) / 0.01;
  rightVelocity = (rightAngle - prevRightAngle) / 0.01;

  
  // remember the position for next time (needed for velocity calculation)
  prevLeftAngle = leftAngle;
  prevRightAngle = rightAngle;

  // calculate error in velocity
  float leftVelocityError = desiredLeftVelocity - leftVelocity;
  float rightVelocityError = desiredRightVelocity - rightVelocity;

  // if the velocity error is 0, then continue to use the duty cycle
  // else change the duty cycle accordingly
  int leftDutyChange = KP * leftVelocityError;
  leftDuty += leftDutyChange;
  if (leftDuty < -255) {
    leftDuty = -255;
  }
  if (leftDuty > 255) {
    leftDuty = 255;
  }
  if (leftDuty < 0) {
    digitalWrite(leftDIR, HIGH);
  }
  else {
    digitalWrite(leftDIR, LOW);
  }
  analogWrite(leftPWM, leftDuty);

  int rightDutyChange = KP * rightVelocityError;
  rightDuty += rightDutyChange;
  if (rightDuty < -255) {
    rightDuty = -255;
  }
  if (rightDuty > 255) {
    rightDuty = 255;
  }
  if (rightDuty < 0) {
    digitalWrite(rightDIR, LOW);
  }
  else {
    digitalWrite(rightDIR, HIGH);
  }
  analogWrite(rightPWM, rightDuty);
  
}



void setMotorSpeeds(float leftSpeed, float rightSpeed) {
  desiredLeftVelocity = leftSpeed;
  desiredRightVelocity = rightSpeed;
}

void kickerSevoAngle(int angle){
    kickerServo.write(angle);
}
