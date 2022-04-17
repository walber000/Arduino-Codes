const int pingPin = 4;
const int pingReceive = 5;

void setup() {
  Serial.begin(9600);

  pinMode(pingPin, OUTPUT);
  pinMode(pingReceive, INPUT);
}

void loop() {
  long duration, cm;

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  duration = pulseIn(pingReceive, HIGH);

  cm = duration / 29 / 2;

  Serial.print(cm);
  Serial.println(" cm");

  delay(200);
}
