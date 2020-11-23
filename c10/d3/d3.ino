#include "MPU6050.h"
#include "HMC5883L.h"
#define LED_PIN 13

MPU6050 accelgyro;
HMC5883L mag;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

bool blinkState = false;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  mag.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection()
      ? "MPU6050 connection successful"
      : "MPU6050 connection failed");
  Serial.println(mag.testConnection() ?
      "HMC5883L connection successful":
      "HMC5883L connection failed");
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  mag.getHeading(&mx, &my, &mz);
    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.println(mz);

  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.println("\t");

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  delay(1000);
}
