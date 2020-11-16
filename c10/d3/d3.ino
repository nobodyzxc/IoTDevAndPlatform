#include "Wire.h"
#include "I2Cdev.h"

#include "MPU6050.h"
#include "BMP085.h"
#define LED_PIN 13

MPU6050 accelgyro;
BMP085 barometer;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float temperature;
float pressure;
float seaLevelPressure = 101830;
float altitude;
int32_t lastMicros;
bool blinkState = false;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  barometer.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection()
      ? "MPU6050 connection successful"
      : "MPU6050 connection failed");
  Serial.println(barometer.testConnection()
      ? "MBP085connection successful"
      : "MPB085 connection failed");
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  barometer.setControl(BMP085_MODE_PRESSURE_3);
  while(micros() - lastMicros < barometer.getMeasureDelayMicroseconds());
  pressure = barometer.getPressure();
  altitude = barometer.getAltitude(pressure, seaLevelPressure);
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.println("\t");

  Serial.print("T/P/A\t");
  Serial.print(temperature); Serial.print("\t");
  Serial.print(pressure); Serial.print("\t");
  Serial.print(altitude);
  Serial.println("");

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  delay(100);
}
