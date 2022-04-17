#include <Wire.h>

//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(3, 4);

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ;
short int x = -20000, y = -20000, a = 20000, b = 20000, count = 0;

void setup() {
  //Wire.setModule(0);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  //PWR_MGMT_1 register
  Wire.write(0);  //set to zero (wakes up the MPU-6050)
  Wire.endTransmission();

  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); //ACCEL_XOUT_H
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_addr, 6, true);
  AcX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Serial.print("AcX = ");
  Serial.print(AcX);
  Serial.print(" AcY = ");
  Serial.print(AcY);
  Serial.print(" AcZ = ");
  Serial.println(AcZ);

  if (x < AcX)
    x = AcX;
  if (y < AcY)
    y = AcY;

  if (a > AcX)
    a = AcX;
  if (b > AcY)
    b = AcY;

  count++;
  if (count == 500) {
    Serial.print("AcX MIN = ");
    Serial.print(a);
    Serial.print(" AcX MAX = ");
    Serial.println(x);
    Serial.print("AcY MIN = ");
    Serial.print(b);
    Serial.print(" AcY MAX = ");
    Serial.println(y);
    delay(100000);
  }

  if (AcX > 5000)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);

  delay(10);
}
