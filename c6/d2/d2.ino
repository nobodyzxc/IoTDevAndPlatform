#include "pitches.h"
#define SpeakerPIN 10

#define rPin 3
#define gPin 5
#define bPin 6

int safe = 10;
int care = 13;
int dang = 23;
int noteDuration;

void rgb(int r, int g, int b){
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}



void setup(){
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop(){

  rgb(0, 255, 0);
  noteDuration = 1000 / 2;
  for(int i = 0; i < 20; i++){
    tone(SpeakerPIN, NOTE_C4, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);
    noTone(SpeakerPIN);
  }
  rgb(255, 255, 0);
  delay(3000);
  rgb(255, 0, 0);
  noteDuration = 1000 / 4;
  for(int i = 0; i < 40; i++){
    tone(SpeakerPIN, NOTE_C5, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);
    noTone(SpeakerPIN);
  }
}
