#define echoPin 7
#define trigPin 8
#define rPin 3
#define gPin 5
#define bPin 6

#define INFO "dist = "

int safe = 100;
int care = 30;
long duration, distance;

int mode = 0;
const float frac = 58.2;

void rgb(int r, int g, int b){
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / frac;

  if(distance >= safe){
    Serial.print(INFO);
    Serial.println(distance);
    if(mode != 0){
      mode = 0;
      rgb(0, 150, 0);
    }
  }
  else if(distance >= care){
    Serial.print(INFO);
    Serial.println(distance);
    if(mode != 1){
      mode = 1;
      rgb(150, 150, 0);
    }
  }
  else{
    Serial.print(INFO);
    Serial.println(distance);
    if(mode != 2){
      mode = 2;
      rgb(150, 0, 0);
    }
  }
  delay(100);
}
