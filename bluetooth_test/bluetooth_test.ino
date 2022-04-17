// Teste Bluetooth HC-05 (transmissor)

short int msg;

void setup() {
  Serial.begin(9600);
}

void loop() {
  msg=1;
  Serial.println(msg);
  delay(1000);
  msg=0;
  Serial.println(msg);
  delay(1000);
}
