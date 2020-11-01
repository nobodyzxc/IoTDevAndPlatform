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

double calroll(int16_t gx, int16_t gy, int16_t gz){
  return atan(-(float)gx / (float)gz);
}

double calpitch(int16_t gx, int16_t gy, int16_t gz){
  return atan((float)gy / sqrt(pow((float)gx, 2) + pow((float)gz, 2)));
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
  Serial.print("roll = ");
  Serial.println(calroll(gx, gy, gx));
  Serial.print("pitch = ");
  Serial.println(calpitch(gx, gy, gx));
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
