#define PIROUT 2
#define PHOTOCELL A0
#define bthres 15

void setup() {
  Serial.begin(9600);
  pinMode(PIROUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int brightness = analogRead(A0);
  Serial.print("brightness is: ");
  Serial.print(brightness);
  int motion = digitalRead(PIROUT);
  Serial.print(", people: ");
  Serial.println(motion);
  if(brightness > bthres){
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if(motion) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}
