#define SENPOW 7
#define SENPIN A0

void setup(){
  pinMode(SENPOW, OUTPUT);
  digitalWrite(SENPOW, LOW);
  Serial.begin(9600);
}

int readSensor(){
  digitalWrite(SENPOW, HIGH);
  delay(10);
  int val = analogRead(SENPIN);
  digitalWrite(SENPOW, LOW);
  return val;
}

void loop(){
  Serial.print("Water level: ");
  Serial.println(readSensor());
  delay(1000);
}
