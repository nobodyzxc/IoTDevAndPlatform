#define LED 13
#define BTN 3
int val = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
}

void loop(){
  val = digitalRead(BTN);
  if(val == HIGH){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
