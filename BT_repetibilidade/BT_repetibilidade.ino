short int x, y, led = 13;

void setup() {
  pinMode(led, OUTPUT); //led
  Serial.begin(9600);
  delay(5000);

}

void loop() {
  Serial.print(3);
  delay(2);
  Serial.print(4);
  delay(2);

  while (!Serial.available()); //recebe 1
  x = Serial.read();
  while (!Serial.available()); //recebe 2
  y = Serial.read();
}
