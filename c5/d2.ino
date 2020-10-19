#include <dht.h>
#define dht_dpin A0

/*

   1/58.2
   340 m/s
   1cm / 29.1 us



   */

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

  float c_air = 331.3 + 0.606 * DHT.temperature;
  float frac = 1e6 / c_air * 2

  delay(1000);
}
