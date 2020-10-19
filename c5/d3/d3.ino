#include <dht.h>
#define dht_dpin A0

dht DHT;

void setup(){
  Serial.begin(9600);
  delay(300);
  Serial.println("Humidity and temperature");
  delay(700);
}

void loop(){
  DHT.read11(dht_dpin);

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.println("%");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C");
  Serial.print("Tdp = ");
  float tdp = DHT.temperature - ((100 - DHT.humidity) / 5);
  Serial.print(tdp);
  Serial.println("C");
  delay(1000);
}
