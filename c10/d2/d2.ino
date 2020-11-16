#define PIROUT 2
#define PHOTOCELL A0
#define bthres 200

void setup() {
  Serial.begin(9600);
  pinMode(PIROUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int brightness = analogRead(A0);
  Serial.print("brightness: ");
  Serial.println(brightness);
  if(brightness > bthres){
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if(digitalRead(PIROUT) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}
