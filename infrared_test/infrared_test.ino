int value;
const int pin = A0; //pino do infrared

void setup() {
  Serial.begin(9600);
}

void loop() {
  //analog read
  value=analogRead(pin);
  //Serial.print("valor mapeado: ");
  //value=map(value, 0, 1023, 1023, 0);
  Serial.println(value);
  delay(200);
}
