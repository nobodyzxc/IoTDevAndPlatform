#define PIN 8
#define rPin 3
#define gPin 5
#define bPin 6

unsigned long duration = 0;
unsigned long starttime = 0;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup(){
  Serial.begin(9600);
  pinMode(PIN, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  starttime = millis();
}

void rgb(int r, int g, int b){
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

#define rgboff() rgb(LOW, LOW, LOW)

void loop(){
  duration = pulseIn(PIN, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;
  if((millis() - starttime) > sampletime_ms){
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
    if(concentration < 500)
      rgb(0, 255, 0);
    else if(concentration >= 500 && concentration < 1000)
      rgb(255, 255, 0);
    else
      rgb(255, 0, 0);
  }
  delay(100);

  if((millis() - starttime) <= sampletime_ms){
    Serial.println((millis() - starttime));
  }
}
