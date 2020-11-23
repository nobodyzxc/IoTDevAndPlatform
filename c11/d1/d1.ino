#include "pitches.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#define rPIN 3
#define gPIN 5
#define bPIN 6
#define SpeakerPIN 10

MPU6050 accelgyro;
HMC5883L mag;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

int state = 0, task = -1;
unsigned long curms, prems, count500ms = 0;

void rgb(int r, int g, int b){
  analogWrite(rPIN, r);
  analogWrite(gPIN, g);
  analogWrite(bPIN, b);
}

void set_shaking(){
  // empty
}

double calacc(float x, float y, float z){
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

int check_shaking(){
  float x = (float)ax / 16384,
        y = (float)ay / 16384,
        z = (float)az / 16384;
  double acc = calacc(x, y, z);
  Serial.print("|a| (must > 2) = ");
  Serial.println(acc);
  return acc >= 2;
}

int pgx, pgy, pgz;
void set_rotating(){
  pgx = gx, pgy = gy, pgz = gz;
}

int check_rotating(){
  int ro =
    abs(gx - pgx) +
    abs(gy - pgy) +
    abs(gz - pgz);

  Serial.print("|r| (must > 10000) = ");
  Serial.println(ro);
  return ro > 10000;
}

char task_names[][30] = {
  "Shaking the board",
  "Rotate more than 20 degrees",
};

void (*task_sets[])(void) = {
  set_shaking, set_rotating
};

int (*task_checks[])(void) = {
  check_shaking, check_rotating
};

#define rgboff() rgb(LOW, LOW, LOW)

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
  pinMode(rPIN, OUTPUT);
  pinMode(gPIN, OUTPUT);
  pinMode(bPIN, OUTPUT);
  prems = millis();
  rgb(255, 255, 255);
}

void show_info(){
  Serial.println("======== info ========\t");
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
}

void loop(){

  mag.getHeading(&mx, &my, &mz);
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // set task
  if(task < 0){
    task = random(sizeof(task_names) / sizeof(task_names[0]));
    Serial.print("\n\n\nTask Dispatch: ");
    Serial.println(task_names[task]);
    Serial.print("\n\n");
  }
  else{
    if(count500ms < 10){
      if(task_checks[task]()){
        task = -1;
        Serial.println("\n\n\nTask Done!\n\n\n");
        state = 0;
        count500ms = 0;
      }
      else if(curms - prems > 500){
        Serial.print("Task: ");
        Serial.println(task_names[task]);     
      }
    }
  }

  curms = millis();
  if(curms - prems > 500){
//    show_info();

    count500ms++;
    prems = curms;

    state = count500ms >= 6;

    if(count500ms < 10)
      noTone(SpeakerPIN);
    else Serial.println("Mission Failed!");

    if(state){
      rgb(255, 0, 0);
      tone(SpeakerPIN, NOTE_C4, 500);
    }
    else{
      rgb(0, 255, 0);
    }
  }

  delay(150);
}
