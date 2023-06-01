#include <Arduino.h>
#include <Servo.h>
//move a servo motor on a teensy 4.0



//create a servo object for kicker
Servo kickerServo;

void setup() {
  Serial.begin(9600);

  //attach the servo to pin 9
  kickerServo.attach(2);
  //set the servo to 0 degrees
  kickerServo.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World!");
  delay(1000);

  //wait for user to enter a 1 or 0
  //it 1 move the servo to 90 degrees
  //if 0 move the servo to 0 degrees

  switch (Serial.read())
  {
  case '1':
    kickerServo.write(180);
    Serial.println("Servo at 180 degrees");
    break;

  case '0':
    kickerServo.write(0);
    Serial.println("Servo at 0 degrees");
    break;

  }


}
