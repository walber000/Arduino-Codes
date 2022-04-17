//CODIGO FINAL ROBÔ MÓVEL
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

//VARIAVEIS
unsigned short int skipread = 0;
const int vel = 112; //128 = ponto central, velocidade nula
const int infrared = A0; //pino do infravermelho
const int echo1 = 3, echo2 = 5;
const int trig1 = 2, trig2 = 4;
int leitura1, leitura2, leitura3;
int x, y, aux;
long int time1, time2;

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {

  //RECEBER DADOS DO ACELEROMETRO
//  time1 = millis();
//  while (!Serial.available())
//  {
//    time2 = millis();
//    if (time2 - time1 > 700) {
//      x = 1;
//      skipread = 1;
//      break;
//    }
//  }
//  if (!skipread)
//    x = Serial.read();
//
//  while (!Serial.available())
//  {
//    time2 = millis();
//    if (time2 - time1 > 700) {
//      y = 4;
//      skipread = 1;
//      break;
//    }
//  }
//  if (!skipread)
//    y = Serial.read();
//
//  if (x > y) {
//    aux = x;
//    x = y;
//    y = aux;
//  }

  while (!Serial.available());
    x = Serial.read();
  while (!Serial.available());
    y = Serial.read();
  //MOVIMENTAÇAO DO ROBÔ
  if (x == '1') {
    if (y == '4')
      parar();
    if (y == '5')
      direita();
    if (y == '3')
      esquerda();
  }
  delay(1);

  if (x == '2') {
    if (y == '4')
      frente();
    if (y == '5')
      frentedireita();
    if (y == '3')
      frenteesquerda();
  }
  delay(1);

  if (x == '0') {
    if (y == '4')
      tras();
    if (y == '5')
      trasdireita();
    if (y == '3')
      trasesquerda();
  }
  delay(1);

  //LEITURA DOS SENSORES E ENVIO
  leitura1 = map(analogRead(infrared), 0, 600, 80, 0); //valormax = 558, max=80cm

  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig1, LOW);
  leitura2 = (pulseIn(echo1, HIGH)) / 58;

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2, LOW);
  leitura3 = (pulseIn(echo2, HIGH)) / 58;

  if (leitura1 > 25)
    leitura1 = 1;
  else if (leitura1 > 15)
    leitura1 = 2;
  else
    leitura1 = 3;

  if (leitura2 > 25)
    leitura2 = 4;
  else if (leitura2 > 15)
    leitura2 = 5;
  else
    leitura2 = 6;

  if (leitura3 > 20)
    leitura3 = 7;
  else if (leitura3 >= 15)
    leitura3 = 8;
  else
    leitura3 = 9;

  Serial.print(leitura1);
  delay(2);
  Serial.print(leitura2);
  delay(2);
  Serial.print(leitura3);
  delay(2);

  skipread = 0;
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
