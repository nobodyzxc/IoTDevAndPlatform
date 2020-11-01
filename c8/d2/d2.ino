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

double calacc(int16_t ax, int16_t ay, int16_t az){
  return sqrt(
      pow((float)ax, 2)
      + pow((float)ay, 2)
      + pow((float)az, 2));
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
  Serial.print("|a| = ");
  Serial.println(calacc(ax, ay, ax));
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
