int ans = -1;
int pushButton = 2;
#define rPin 3
#define gPin 5
#define bPin 6

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  // make the pins outputs:
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void rgb(int r, int g, int b){
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

void rgboff(){
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

void loop() {
  // if there's any serial available, read it:
  int buttonState = digitalRead(pushButton);
  if(buttonState){
    ans = analogRead(A0);
    Serial.print("set answer to ");
    Serial.println(ans);
    rgboff();
  }

  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int guess = Serial.parseInt();

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      if(ans == -1){
        Serial.println("press button to set a value");
      }
      if(guess < ans)
        Serial.println("guess larger..."), rgboff();
      else if(guess > ans)
        Serial.println("guess smaller..."), rgboff();
      else{
        Serial.println("Yup, it's the value!");
        rgb(255, 0, 0);
      }
    }
  }
}
