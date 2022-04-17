//Programa : Teste modulo Joystick  
 //Autor : Arduino e Cia  
  #include <VirtualWire.h>
   
 int valorx = 0; //Armazena o valor lido do potenciometro - Eixo X  
 int valory = 0; //Armazena o valor lido do potenciometro - Eixo Y  
 int valorz = 0; //Armazena o valor lido do botão - Eixo Z  
 int pinoledesquerda = 2; //Pino Led Esquerdo  
 int pinoledsuperior = 3; //Pino Led Superior  
 int pinoleddireita = 4;  //Pino Led Direito  
 int pinoledinferior = 5; //Pino Led Inferior  
 int pinoledz = 10;    //Pino Led Eixo Z  
   
 void setup() 
 {  
    vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_tx_pin(3);         // Arduino pin to connect the receiver data pin
  
 pinMode(7, INPUT);  //Pino Eixo Z  
 Serial.begin(9600);  

 }  
   
 void loop() 
 {  
   
 //Le o valor do potenciometro ligado à porta analogica A0 - Eixo X  
 valorx = analogRead(A0);   

   uint8_t test = (uint8_t)(valorx&0xFF);
   uint8_t test2 = (uint8_t)((valorx>>8)&0xFF);
   uint8_t aux[2];
   aux[0] = test;
   aux[1] = test2;
   
   vw_send((uint8_t *)aux, 2);
   Serial.println((((int)aux[1])<<8|aux[0]));
   //Serial.println(aux[0]);
   //Serial.println(aux[1]);
   vw_wait_tx();        // We wait to finish sending the message
   delay(200);         // We wait to send the message again   
}  
