#define SEN A0

#define BASE 11

int thres[3] = {20, 50, 70};
int len = sizeof thres / sizeof thres[0];

int lv(int val){
  int i = 0;
  for(i = 0; i < len; i++)
    if(val < thres[i]) return i;
  return i;
}

void setup(){
  for(int i = 0; i < len; i++)
    pinMode(BASE + i, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int val = analogRead(A0);
  Serial.println(val);
  int n = lv(val);


  for(int i = 0; i < n; i++)
    digitalWrite(BASE + i, HIGH);

  for(int i = n; i < len; i++)
    digitalWrite(BASE + i, LOW);

  Serial.println(val, DEC);
  delay(100);
}
