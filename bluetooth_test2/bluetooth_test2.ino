// Teste Bluetooth HC-05 (receptor)

short int msg, led=13;

void setup() {
  pinMode(led, OUTPUT); //led
  Serial.begin(9600);
}

void loop() {
  //espera por mensagem
  while(!Serial.available());
  
  msg = Serial.read();
  if(msg=='1'){
     digitalWrite(led, HIGH);
     Serial.println("ON!");
  }
  if(msg=='0'){
     digitalWrite(led, LOW);
     Serial.println("OFF!");
  }
  delay(500);
}
