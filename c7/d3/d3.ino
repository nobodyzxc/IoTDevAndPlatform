#include "Wire.h"
#include "I2Cdev.h"
#include "BMP085.h"
BMP085 barometer;
float temperature;
float pressure;
float seaLevelPressure = 101830;
float altitude;
int32_t lastMicros;
int pushButton = 2;
#define LED1F 11
#define LED2F 12
#define LED3F 13

void setup() {
  Wire.begin();

  Serial.begin(38400);

  Serial.println("Initializing I2C devices...");
  barometer.initialize();

  Serial.println("Testing device connections...");
  Serial.println(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");

  pinMode(pushButton, INPUT);
  pinMode(LED1F, OUTPUT);
  pinMode(LED2F, OUTPUT);
  pinMode(LED3F, OUTPUT);
  digitalWrite(LED1F, 1);
  digitalWrite(LED2F, 1);
  digitalWrite(LED3F, 1);
}

float meansure(){
  // request temperature
  barometer.setControl(BMP085_MODE_TEMPERATURE);

  // wait appropriate time for conversion (4.5ms delay)
  lastMicros = micros();
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

  // read calibrated temperature value in degrees Celsius
  temperature = barometer.getTemperatureC();

  // request pressure (3x oversampling mode, high detail, 23.5ms delay)
  barometer.setControl(BMP085_MODE_PRESSURE_3);
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

  // read calibrated pressure value in Pascals (Pa)
  pressure = barometer.getPressure();

  // calculate absolute altitude in meters based on known pressure
  // (may pass a second "sea level pressure" parameter here,
  // otherwise uses the standard value of 101325 Pa)
  altitude = barometer.getAltitude(pressure, seaLevelPressure);

  // display measured values if appropriate
  Serial.print("T/P/A\t");
  Serial.print(temperature); Serial.print("\t");
  Serial.print(pressure); Serial.print("\t");
  Serial.print(altitude);
  Serial.println("");
  return altitude;
}

int mode = 0;
float firstFloor = 0;
float secondFloor = 0;
void loop() {

  int buttonState = digitalRead(pushButton);
  if(buttonState){
    Serial.println("button pressed...");
    if(mode == 0){
      digitalWrite(LED1F, 0);
      firstFloor = meansure();
      Serial.print("firstFloor = ");
      Serial.println(firstFloor);
    }
    else if(mode == 1){
      secondFloor = meansure();
      Serial.print("secondFloor = ");
      Serial.println(secondFloor);
      digitalWrite(LED2F, 0);
      digitalWrite(LED3F, 0);
    }
    else if(mode == 2){
      float m = meansure();
      Serial.print("Floor = ");
      Serial.println(m);
      float gap = ((m - firstFloor) / abs(secondFloor - firstFloor)) + 1;
      int floor = int(gap) + ((gap - int(gap)) >= 0.5 ? 1 : 0);
      Serial.print("floor is:");
      Serial.println(floor);
      digitalWrite(10 + floor, 1);
    }
    else{
      digitalWrite(LED1F, 1);
      digitalWrite(LED2F, 1);
      digitalWrite(LED3F, 1);
    }
    mode = (mode + 1) % 4;
    delay(1000);
  }
  delay(100);
}
