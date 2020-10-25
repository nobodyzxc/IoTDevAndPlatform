#include "Servo.h"

Servo myservo;

int angle = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  while (Serial.available() > 0) {
    int angle = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.print("adjust to ");
      Serial.println(angle);
      myservo.write(angle);
      delay(15);
    }
  }
}
