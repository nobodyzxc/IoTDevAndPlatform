#include <Servo.h>
//#define abs(x) ((x) > 0 ? (x) : -(x))

Servo myservo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

int brightness = 0;
int bestAngle = 0;

void printBest(){
  Serial.print("best angle:");
  Serial.println(bestAngle);
  Serial.print("max val:");
  Serial.println(brightness);
}

void loop() {
  int b = 0;
  brightness = -1;
  for (pos = 0; pos <= 120; pos += 1) {
    b = analogRead(A0);
    Serial.println(b);
    if(b > brightness) brightness = b, bestAngle = pos, printBest();
    myservo.write(pos);
    delay(50);
  }
//  for (pos = 180; pos >= 0; pos -= 1) {
//    Serial.println(b);
//    b = analogRead(A0);
//    Serial.println(b);
//    if(b > brightness) brightness = b, bestAngle = pos, printBest();
//    myservo.write(pos);
//    delay(50);
//  }
  myservo.write(bestAngle);
  delay(50);
  Serial.print("best angle:");
  Serial.println(bestAngle);
  Serial.print("max val:");
  Serial.println(brightness);
  while(1){
    delay(1000);
    b = analogRead(A0);
    int diff = abs(b - brightness);
    if(diff > brightness / 2){
      Serial.print("diff:");
      Serial.println(diff);
      Serial.print(" > ");
      Serial.println(brightness / 3);
      //break;
    }
  }
}
