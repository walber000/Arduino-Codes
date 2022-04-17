int msg,aux;
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  //Serial.print(aux);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
    msg = Serial.read();
/*
    if(msg==56);
    aux=4;
    if(msg==57)
    aux=3;
  */  
    if(msg==51)
    aux=8;
    if(msg==52)
    aux=9;
    
    Serial.print(aux);
    delay(100);
  }
  /*
  if(msg==56)
    digitalWrite(8, HIGH);
  if(msg==57)
    digitalWrite(8, LOW);
*/

  if(msg==51)
    digitalWrite(13, HIGH);
  if(msg==52)
    digitalWrite(13, LOW);

  delay(100);
}
