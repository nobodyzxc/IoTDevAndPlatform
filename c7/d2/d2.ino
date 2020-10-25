#include <Servo.h>
#define abs(x) ((x) > 0 ? (x) : -(x))

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9);
}

int brightness = 0;
int bestAngle = 0;

void loop() {
  int b = 0;
  brightness = -1;
  for (pos = 0; pos <= 180; pos += 1) {
    b = analogRead(A0);
    if(b > brightness) brightness = b, bestAngle = pos;
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    b = analogRead(A0);
    if(b > brightness) brightness = b, bestAngle = pos;
    myservo.write(pos);
    delay(15);
  }
  myservo.write(bestAngle);
  delay(15);
  while(1){
    delay(1000);
    b = analogRead(A0);
    if(abs(b - brightness) > brightness / 5)
      break;
  }
}
