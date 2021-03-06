#include "Wire.h"
#include "MPU6050.h"
#include "I2Cdev.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define LED_PIN 13
bool blinkState = false;

void setup(){
  Wire.begin();
  Serial.begin(38400);

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ?
      "MPU6050 connection successful" :
      "MPU6050 connection failed");

  pinMode(LED_PIN, OUTPUT);
}

double calroll(float x, float y, float z){
  return atan(-x / z);
}

double calpitch(float x, float y, float z){
  return atan((y / sqrt(pow(x, 2) + pow(z, 2))));
}

double calacc(float x, float y, float z){
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void loop(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
  float x = (float)ax / 16384, y = (float)ay / 16384, z = (float)az / 16384;
  Serial.print("Gx: "); Serial.print(x); Serial.print("\t");
  Serial.print("Gy: "); Serial.print(y); Serial.print("\t");
  Serial.print("Gz: "); Serial.print(z); Serial.print("\t");
  Serial.println(" <- in +/- 2G");
  Serial.print("|a| = ");
  Serial.println(calacc(x, y, z));
  Serial.print("roll = ");
  Serial.println(calroll(x, y, z));
  Serial.print("pitch = ");
  Serial.println(calpitch(x, y, z));
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  delay(1000);
}
