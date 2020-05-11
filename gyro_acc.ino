#include"Wire.h"
#include"I2Cdev.h"
#include"MPU6050.h"
#include "math.h"

MPU6050 mpu;

int16_t gyroX, accY, accZ;
volatile int gyroRate;
volatile float accAngle, gyroAngle=0, gyroangle=0, currentAngle, prevAngle=0;
unsigned long currTime, prevTime=0, loopTime;

void setup() {  
  mpu.initialize();
  Serial.begin(9600);
}

void loop() {

  accZ = mpu.getAccelerationZ();
  accY = mpu.getAccelerationY();
  gyroX = mpu.getRotationX();

  currTime = millis();
  loopTime = currTime - prevTime;
  prevTime = currTime;
  
  accAngle = atan2(accY, accZ)*RAD_TO_DEG;
  gyroRate = map(gyroX, -32768, 32767, -250, 250);
  gyroAngle = gyroangle + (float)gyroRate*loopTime/1000;
  currentAngle = 0.9934*(prevAngle + gyroAngle) + 0.0066*(accAngle);
  

  
 Serial.println(currentAngle);
  delay(1000);
  
}
