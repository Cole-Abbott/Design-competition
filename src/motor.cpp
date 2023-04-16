#include <Encoder.h>

// Drive the two motors forwards and backwards at different speeds
// motor driver - https://www.pololu.com/product/2960

int LED = LED_BUILTIN; // there's always an LED on pin 13

// motor pins
int leftPWM = 4;
int leftDIR = 5;

// encoder pins
int leftEncoderA = 2;
int leftEncoderB = 3;

Encoder encoderLeft(leftEncoderB, leftEncoderA);
long encoderCountLeft  = 0;


void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on
  Serial.begin(9600);

  // set up the motor pins
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);

}

void loop() {
  // note the direction of the motor depends on the DIR pin, the two motors are probably opposite
  analogWrite(leftPWM, 128);
  digitalWrite(leftDIR, LOW);

  for(int i = 0; i < 10; i++){
    encoderCountLeft = encoderLeft.read();
    float leftAngle = encoderCountLeft * 360.0 / 1632.0;
    Serial.println(leftAngle);
    delay(50);
  }
  

  analogWrite(leftPWM, 255);
  digitalWrite(leftDIR, LOW);

  for(int i = 0; i < 10; i++){
    encoderCountLeft = encoderLeft.read();
    float leftAngle = encoderCountLeft * 360.0 / 1632.0;
    Serial.println(leftAngle);
    delay(50);
  }

  analogWrite(leftPWM, 128);
  digitalWrite(leftDIR, HIGH);
 
  for(int i = 0; i < 10; i++){
    encoderCountLeft = encoderLeft.read();
    float leftAngle = encoderCountLeft * 360.0 / 1632.0;
    Serial.println(leftAngle);
    delay(50);
  }

  analogWrite(leftPWM, 255);
  digitalWrite(leftDIR, HIGH);

  for(int i = 0; i < 10; i++){
    encoderCountLeft = encoderLeft.read();
    float leftAngle = encoderCountLeft * 360.0 / 1632.0;
    Serial.println(leftAngle);
    delay(50);
  }

  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);
  
  for(int i = 0; i < 10; i++){
    encoderCountLeft = encoderLeft.read();
    float leftAngle = encoderCountLeft * 360.0 / 1632.0;
    Serial.println(leftAngle);
    delay(50);
  }



}