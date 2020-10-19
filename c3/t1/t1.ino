int state = LOW;
unsigned int prems = 0;
const long interval = 500;

void setup(){
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    unsigned long curms = millis();
    if(curms - prems >= interval){
        prems = curms;
        state = state == LOW ? HIGH : LOW;
        Serial.println(1);
    }
    digitalWrite(LED_BUILTIN, state);
}
