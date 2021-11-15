
#include <Wire.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;


void setup() {
  Serial.begin(9600);
   Serial.print("test");

  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
     Serial.print("test");
    while (1);
    }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //Serial.print("y");
  //Serial.println(-(gy + 450)/200);
  //Serial.print("x");
  //Serial.println (((gx+800)/200));

  vx =  (gx+800)/200;
  vy = -(gy + 450)/200;
  
  Mouse.move(vx, vy);
  
  delay(20);
}
