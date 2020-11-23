/*
   Melody

   Plays a melody

circuit:
- 8 ohm speaker on digital pin 8

created 21 Jan 2010
modified 30 Aug 2011
by Tom Igoe

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/Tone
 */

#include "pitches.h"

/*
// notes in the melody:
int melody[] = {
NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
4, 8, 8, 4, 4, 4, 4, 4
};
 */
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,

  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,

  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,

};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,

  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,

  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
};

int pushButton = 2;

void play(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(noteDurations) / sizeof(int); thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
//  play();
}

unsigned int count = 0;
unsigned int rec = 0;

void loop() {
  int buttonState = digitalRead(pushButton);
  int sensorReading = analogRead(A0);
  if(buttonState){
    count++;
    Serial.println("click");
    delay(500);
  }
  else{
    if(count > 3){
      Serial.println("play");
      for (int thisNote = 0; thisNote < rec; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
      }
      rec = 0;
      count = 0;
    }
    else if(count){
      int thisPitch = map(sensorReading, 0, 1000, 120, 1500);
      melody[rec] = thisPitch;
      Serial.println("record:");
      Serial.println(sensorReading);
      Serial.println(thisPitch);
      rec++;
      count = 0;
    }
  }
  delay(10);
}
