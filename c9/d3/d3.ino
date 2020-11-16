#include "Servo.h"
#define SENPOW 7
#define SENPIN A0
#define sensorMin 0
#define sensorMax 520

Servo myservo;

void setup(){
  pinMode(SENPOW, OUTPUT);
  digitalWrite(SENPOW, LOW);
  myservo.attach(9);
  Serial.begin(9600);
}

int calibration(int value, int min, int max){
  value = map(value, sensorMin, sensorMax, min, max);
  value = constrain(value, min, max);
  return value;
}

int readSensor(){
  digitalWrite(SENPOW, HIGH);
  delay(10);
  int val = analogRead(SENPIN);
  digitalWrite(SENPOW, LOW);
  return val;
}

int readLv(){
  Serial.print("Water level: ");
  int level = calibration(readSensor(), 0, 100);
  Serial.println(level);
  return level;
}

void move(int pos){
  while(readLv() >= 100)
    delay(50);
  myservo.write(pos);
  delay(50);
}

void loop(){
  int pos = 0;
  for (pos = 0; pos <= 180;
      move(pos), pos += 1);
  for (pos = 180; pos >= 0;
      move(pos), pos -= 1);
}
