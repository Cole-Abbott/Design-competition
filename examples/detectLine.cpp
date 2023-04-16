#include <Arduino.h>

#define BUTTON 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World!");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A3, INPUT);

  pinMode(BUTTON, INPUT);
}

void loop() {
  //if line is detected, print line
  if (analogRead(A3) < 200) {
    Serial.print("Line ");
    Serial.println(analogRead(A3));
  
  }
  delay(50); 
}
