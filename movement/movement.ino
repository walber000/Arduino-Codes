#include <Wire.h>

//REGISTRADORES
#define MD25ADDRESS         0x58                              // Address of the MD25
#define SPEED1              (byte)0x00                        // Byte to send speed to first motor
#define SPEED2              0x01                              // Byte to send speed to second motor

//PROTOTIPOS
void frente();
void parar();
void direita();
void esquerda();
void tras();
void frentedireita();
void frenteesquerda();
void trasdireita();
void trasesquerda();

unsigned short int vel = 116; //128 = ponto central, velocidade nula
long int time1, time2;
short int skipread=0;
int x, y, aux;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  
  time1=millis();
  while (!Serial.available())
  {
    time2=millis();
    if(time2-time1>700){
      x=1;
      skipread=1;
      break;
    }
  }
  if(!skipread)
    x = Serial.read();

  while (!Serial.available())
  {
    time2=millis();
    if(time2-time1>700){
      y=4;
      skipread=1;
      break;
    }
  }
  if(!skipread)
    y = Serial.read();

  if (x > y) {
    aux = x;
    x = y;
    y = aux;
  }

  if (x == '1') {
    if (y == '4')
      parar();
    if (y == '5')
      direita();
    if (y == '3')
      esquerda();
  }

  if (x == '2') {
    if (y == '4')
      frente();
    if (y == '5')
      frentedireita();
    if (y == '3')
      frenteesquerda();
  }

  if (x == '0') {
    if (y == '4')
      tras();
    if (y == '5')
      trasdireita();
    if (y == '3')
      trasesquerda();
  }

  Serial.print(x - 48);
  delay(2);
  Serial.print(y - 48);
  delay(2);

  skipread=0;
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

void frentedireita() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write((vel + 128) / 2);
  Wire.endTransmission();
}

void frenteesquerda() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write((vel + 128) / 2);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(vel);
  Wire.endTransmission();
}

void trasdireita() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write(256 - vel);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write((vel + 128) / 2);
  Wire.endTransmission();
}

void trasesquerda() {
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in vel
  Wire.write(SPEED2);
  Wire.write((vel + 128) / 2);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in vel
  Wire.write(SPEED1);
  Wire.write(256 - vel);
  Wire.endTransmission();
}
