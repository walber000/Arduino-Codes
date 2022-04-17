#include <Ultrasonic.h>
//#include <Servo.h>
#include <LiquidCrystal.h>
#include <VirtualWire.h>

LiquidCrystal lcd(8,9,4,5,6,7);
//Servo myservo;
int pos = 0;
void setup() {
  Serial.begin(9600);
  //myservo.attach(3);
  vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_rx_pin(7);         // Arduino pin to connect the receiver data pin
    vw_rx_start();           // Start the receiver
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  int res;
  if (vw_get_message(buf, &buflen))      // We check if we have received data
  {
    

    res = (((int)buf[1]) << 8) | buf[0];
    // Message with proper check    
    Serial.println(res);
   
  }
  res = map(res, 0, 1024, 0, 180);
  //myservo.write(res);
  
  lcd.print(getRanging(A3,A4));
  
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }  */
  //delay(300);
}


int getRanging(byte trig, byte echo){
  Ultrasonic ultrasonic(trig,echo);
  return ultrasonic.Ranging(CM);
}


