#include <SoftwareSerial.h>
#include <Wire.h>

//REGISTRADORES
#define MD25ADDRESS         0x58                              // Address of the MD25
#define SPEED1              (byte)0x00                        // Byte to send speed to first motor
#define SPEED2              0x01                              // Byte to send speed to second motor

//PROTOTIPOS
byte getSoft();
void encodeReset();
long encoder1();
long encoder2();
void volts();
void frente();
void parar();
void direita();
void esquerda();
void tras();

unsigned short int vel = 140; //128 = ponto central, velocidade nula
int encoder1_cm, encoder2_cm;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  frente();
  delay(2000);
  parar();
  delay(200);
  
  direita();
  delay(2000);
  parar();
  delay(200);
  
  esquerda();
  delay(2000);
  parar();
  delay(200);
  
  tras();
  delay(2000);
  parar();
  delay(2200);
}

void frente() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(vel);
  Wire.endTransmission();
}

void parar() {                                          // Function to stop motors
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(128);                                           // Sends a value of 128 to motor 2 this value stops the motor
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(128);
  Wire.endTransmission();
}

void direita() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(256 - vel);
  Wire.endTransmission();
}

void esquerda() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(256 - vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(vel);
  Wire.endTransmission();
}

void tras() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(256 - vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(256 - vel);
  Wire.endTransmission();
}
