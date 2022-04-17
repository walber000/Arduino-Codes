// teste motores de vibracao, com pwm controlado por infrared

const int motor1pin1 = 11;
const int motor1pin2 = 13;
const int enablepin1 = 10;

const int motor2pin1 = 8;
const int motor2pin2 = 7;
const int enablepin2 = 14;

const int IR1 = 5;
const int IR2 = 2;

const int led1 = 6;
const int led2 = 12;

int d1 = 0;
int d2 = 0;

void setup() {
  Serial.begin(9600);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(enablepin1, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enablepin2, OUTPUT);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(enablepin1, HIGH);
  analogWrite(enablepin1, 0;

  digitalWrite(enablepin2, HIGH);
  analogWrite(enablepin2, 0;
  delay(2000);

  analogWrite(enablepin1, 170);
  analogWrite(enablepin2, 170);
  delay(10);
}

void loop() {
  d1 = map(analogRead(IR1), 0, 1023, 255, 0);
  delay(10);
  d2 = map(analogRead(IR2), 0, 1023, 255, 0);

  Serial.print("d1: ");
  Serial.print(d1);
  Serial.print("  d2: ");
  Serial.println(d2);

  if(d1>120){
    analogWrite(enablepin1, 160);
    digitalWrite(led1, HIGH);
  }
  else{
    analogWrite(enablepin1, 70);
    digitalWrite(led1, LOW);
  }
  if(d2>120){
    analogWrite(enablepin2, 160);
    digitalWrite(led2, HIGH);
  }
  else{
    analogWrite(enablepin2, 70);
    digitalWrite(led2, LOW);
  }
  
  delay(200);
}
