#include "pitches.h"
#define echoPin 7
#define trigPin 8
#define LEDPin 13
#define SpeakerPIN 10

int safe = 100;
int care = 30;
long duration, distance;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

int mode = 0;

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if(distance >= safe){
    Serial.println(distance);
    digitalWrite(LEDPin, LOW);
  }
  else if(distance >= care){
    Serial.println(distance);
    digitalWrite(LEDPin, HIGH);
    int noteDuration = 1000 / 2;
    for(int i = 0; i < 2; i++){
      tone(SpeakerPIN, NOTE_C4, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(SpeakerPIN);
    }
  }
  else{
    Serial.println(distance);
    digitalWrite(LEDPin, HIGH);
    int noteDuration = 1000 / 4;
    for(int i = 0; i < 4; i++){
      tone(SpeakerPIN, NOTE_C4, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(SpeakerPIN);
    }
  }
  delay(50);
}
