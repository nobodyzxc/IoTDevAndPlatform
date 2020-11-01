#include<Wire.h>

#include "HMC5883L.h"

HMC5883L mag;
int16_t mx, my, mz;

#define BTN_PIN 2
#define echoPin 7
#define trigPin 8
const float frac = 58.2;
long distance, duration;

#define LED_PIN 13
bool blinkState = false;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  Serial.println(mag.testConnection() ?
      "HMC5883L connection successful":
      "HMC5883L connection failed");

  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int obj = 0;
float objdeg[2];
long objdist[2];

float caldist(long *dists, float *degs){
  float theta = abs(degs[0] - degs[1]);
  float a = (float)dists[0], b = (float)(dists[1]);
  return pow(a, 2) + pow(b, 2) - 2 * a * b * cos(theta);
}

void loop(){

  int state = digitalRead(BTN_PIN);

  if(state){
    Serial.print("detect obj: ");
    Serial.println(obj);

    mx = my = mz = 0;
    mag.getHeading(&mx, &my, &mz);

    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.println(mz);

    float heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    float deg = heading * 180 / M_PI;
    objdeg[obj] = deg;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration / frac;

    objdist[obj] = distance;

    Serial.print("obj heading: ");
    Serial.print(objdeg[obj]);
    Serial.print(", dist: ");
    Serial.println(objdist[obj]);

    if(obj){
      Serial.println();
      Serial.print("obj 0 and 1 dist: ");
      Serial.println(caldist(objdist, objdeg));
    }
    obj = 1 - obj;

    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    delay(1000);
  }
  delay(100);
}
