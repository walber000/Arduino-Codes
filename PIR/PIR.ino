const int PIR = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR);
  if(value == 1)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}
