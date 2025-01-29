#define ledPin 13

#include <Arduino.h>


void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  Serial.println("Hello World");
}
