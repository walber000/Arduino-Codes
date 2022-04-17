short int x=2,y=2,led=13, aux;
int count1=0, count2=0;

void setup() {
  pinMode(led, OUTPUT); //led
  Serial.begin(9600);
  //Serial.println("Hello, world?");
}

void loop() {
  while(!Serial.available());
  x = Serial.read();
  while(!Serial.available());
  y = Serial.read();

  if(x>y){
    aux=x;
    x=y;
    y=aux;
  }
  
  Serial.print(x-48);
  Serial.print(y-48);
  //Serial.println("");

  delay(1);
  count1++;
  if(x!='1' || y!='4')
    count2++;

  if(count1==500){
    Serial.println("");
    Serial.println(count1);
    Serial.println(count2);
    delay(100000);
  }
}
