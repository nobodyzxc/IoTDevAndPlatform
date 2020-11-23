/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
 --------Use This Sketch To------------------------------------------
 1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
 2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
 2) Learn about using a PulseSensor Library "Object".
 4) Blinks LED on PIN 13 with user's Heartbeat.
 --------------------------------------------------------------------*/

#include "pitches.h"
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,

//  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
//  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
//
//  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
//  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,

};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,

//  4, 4, 4, 4, 4, 4, 2,
//  4, 4, 4, 4, 4, 4, 2,
//
//  4, 4, 4, 4, 4, 4, 2,
//  4, 4, 4, 4, 4, 4, 2,
};

void setup() {

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);

  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }
}

int getBPM(){
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    Serial.println("♥  A HeartBeat Happened ! ");
    Serial.print("BPM: ");
    Serial.println(myBPM);
  }
  else return 1;
  return myBPM;
}

float BPM2rate(int bpm){
  if(bpm < 70)
    return 1;
  else if(bpm < 80)
    return 1.5;
  else return 2;
}

void loop() {
  int rate = BPM2rate(getBPM());
  for (int thisNote = 0; thisNote < sizeof(noteDurations) / sizeof(int); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30 / rate;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
