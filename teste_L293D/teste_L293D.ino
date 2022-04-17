//const int enable1 = 8;
//const int enable2 = 9;

const int motor1pin = 3;
const int motor2pin = 5;
const int motor3pin = 6;

void setup() {
//  pinMode(enable1, OUTPUT);
//  pinMode(enable2, OUTPUT);
  pinMode(motor1pin, OUTPUT);
  pinMode(motor2pin, OUTPUT);
  pinMode(motor3pin, OUTPUT);

//  digitalWrite(enable1, HIGH);
//  digitalWrite(enable2, HIGH);
  
  analogWrite(motor1pin, 0);
  analogWrite(motor2pin, 0);
  analogWrite(motor3pin, 0);

  delay(1000);
}

void loop() {
  analogWrite(motor1pin, 140);
  analogWrite(motor2pin, 140);
  analogWrite(motor3pin, 140);
  delay(2000);
  analogWrite(motor1pin, 0);
  analogWrite(motor2pin, 0);
  analogWrite(motor3pin, 0);
  delay(2000);
    analogWrite(motor1pin, 220);
  analogWrite(motor2pin, 220);
  analogWrite(motor3pin, 220);
  delay(2000);
  analogWrite(motor1pin, 0);
  analogWrite(motor2pin, 0);
  analogWrite(motor3pin, 0);
  delay(2000);
    analogWrite(motor1pin, 255);
  analogWrite(motor2pin, 255);
  analogWrite(motor3pin, 255);
  delay(2000);
  analogWrite(motor1pin, 0);
  analogWrite(motor2pin, 0);
  analogWrite(motor3pin, 0);
  delay(2000);
}
