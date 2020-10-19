#include "pitches.h"
#define echoPin 7
#define trigPin 8
#define LEDPin 13
#define SpeakerPIN 10

#include <dht.h>
#define dht_dpin A0

/*
   1/58.2
   340 m/s
   1cm / 29.1 us
   */

int safe = 100;
int care = 30;
long duration, distance;

dht DHT;
void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  delay(300);
  Serial.println("Humidity and temperature done");
  delay(700);
}

int mode = 0;

void loop(){

  DHT.read11(dht_dpin);
  float c_air = 331.3 + 0.606 * DHT.temperature;
  float frac = 1e6 / (c_air * 100) * 2;

  Serial.print("speed = ");
  Serial.println(c_air);
  Serial.print("frac = ");
  Serial.println(frac);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  //distance = duration / frac;
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
