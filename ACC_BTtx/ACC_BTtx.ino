#include <Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ;
short int x,y;

void setup() {
  //Wire.setModule(0);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  //PWR_MGMT_1 register
  Wire.write(0);  //set to zero (wakes up the MPU-6050)
  Wire.endTransmission();
  
  Serial.begin(9600);
  delay(5000);
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); //ACCEL_XOUT_H
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU_addr, 4, true);
  AcX = Wire.read()<<8|Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read()<<8|Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  if(AcX>=6000)
    x=2;
  if(AcX<6000&&AcX>-6000)
    x=1;
  if(AcX<=-6000)
    x=0;

  if(AcY>=6000)
    y=5;
  if(AcY<6000&&AcY>-6000)
    y=4;
  if(AcY<=-6000)
    y=3;
    
  Serial.print(x);
  delay(2);
  Serial.print(y);
  delay(2);

  while(!Serial.available());
  x = Serial.read();
  while(!Serial.available());
  y = Serial.read();
}
