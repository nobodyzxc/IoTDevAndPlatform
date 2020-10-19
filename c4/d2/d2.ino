/*
   Calibration

   Demonstrates one technique for calibrating sensor input. The sensor readings
   during the first five seconds of the sketch execution define the minimum and
   maximum of expected values attached to the sensor pin.

   The sensor minimum and maximum initial values may seem backwards. Initially,
   you set the minimum high and listen for anything lower, saving it as the new
   minimum. Likewise, you set the maximum low and listen for anything higher as
   the new maximum.

   The circuit:
   - analog sensor (potentiometer will do) attached to analog input 0
   - LED attached from digital pin 9 to ground

   created 29 Oct 2008
   by David A Mellis
   modified 30 Aug 2011
   by Tom Igoe

   This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/Calibration
 */

// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 0;        // minimum sensor value
int sensorMax = 1023;           // maximum sensor value

const int numReadings = 10;
// the readings from the analog input
int readings[numReadings];
// the index of the current reading
int readIndex = 0;
// the running total
int total = 0;
// the average
int average = 0;

int smooth(int value){
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = value;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  return average;
}

int calibration(int value){
  // apply the calibration to the sensor reading
  value = map(value, sensorMin, sensorMax, 0, 255);
  //Serial.print("after map: ");
  //Serial.println(value);

  // in case the sensor value is outside the range seen during calibration
  value = constrain(value, 0, 255);
  //Serial.print("after constrain: ");
  //Serial.println(value);
  return value;
}

void setup() {
  Serial.begin(9600);
  // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  for (int thisReading = 0;
      thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  // read the sensor:
  int cal, smo;
  sensorValue = analogRead(sensorPin);
  cal = calibration(sensorValue);
  smo = smooth(cal);
  Serial.print(sensorValue);
  Serial.print(" to cal: ");
  Serial.print(cal);
  Serial.print(" to smo: ");
  Serial.println(smo);
  // fade the LED using the calibrated value:
  analogWrite(ledPin, smo);
  // delay in between reads for stability
  delay(1);
}
