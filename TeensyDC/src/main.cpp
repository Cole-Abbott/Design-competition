#include <Arduino.h>
#include <Servo.h>
#include <Encoder.h>
#include <IntervalTimer.h>
#include "motors.h"
#include "sensors.h"

void kick();

void setup() {
  Serial.begin(9600);

  motorSetup();
  sensorSetup(3, kick);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  //wait for user to enter a 1 or 0
  //it 1 move the servo to 90 degrees
  //if 0 move the servo to 0 degrees
  //if 2 set motor to 500
  //if 3 set motor to 0
  //if 4 set motor to -500


  switch (Serial.read())
  {
  case '1':
    kickerSevoAngle(180);
    Serial.println("Servo at 180 degrees");
    break;

  case '0':
    kickerSevoAngle(0);
    Serial.println("Servo at 0 degrees");
    break;
  case '2':
    setMotorSpeeds(500, 500);
    break;

  case '3': 
    setMotorSpeeds(0, 0);
    break;

  case '4':
    setMotorSpeeds(-500, -500);
    break;

  }

}


void kick() {
  Serial.println("Kick");
  kickerSevoAngle(180);
}