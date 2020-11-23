#define SEN A0
#define LED 13
int val = 0;

void setup(){
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(A0);
  digitalWrite(LED, HIGH)
  delay(val);
  digitalWrite(LED, LOW);
  delay(val);
  Serial.println(val, DEC);
}
