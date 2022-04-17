#include <SoftwareSerial.h>
#include <Wire.h>

#define CMD                 (byte)0x00                        // Values of 0 eing sent using write have to be cast as a byte to stop them being misinterperted as NULL
// This is a but with arduino 1
#define MD25ADDRESS         0x58                              // Address of the MD25
#define SOFTWAREREG         0x0D                              // Byte to read the software version
#define SPEED1              (byte)0x00                        // Byte to send speed to first motor
#define SPEED2              0x01                              // Byte to send speed to second motor
#define ENCODERONE          0x02                              // Byte to read motor encoder 1
#define ENCODERTWO          0x06                              // Byte to read motor encoder 2
#define VOLTREAD            0x0A                              // Byte to read battery volts
#define RESETENCODERS       0x20

int x = 0;                                                  // int x stores a value to be used as speed data for the motors

void setup() {
  Wire.begin();
  Serial.begin(9600);                                       // Begin serial for LCD03
  delay(10);                                                // Wait for everything to power up
  Serial.print("MD25  Example   V:");
  byte softVer = getSoft();                                 // Gets the software version of MD25
  Serial.print(softVer, DEC);                               // Print software version to the screen
  encodeReset();                                            // Cals a function that resets the encoder values to 0
}

void loop() {
  int encoder1_cm = 0;
  x = 150;                                                   // Put a value of 255 in x, this will dive motors forward at full speed

  do {                                                       // Start loop to drive motors forward
    Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in x
    Wire.write(SPEED2);
    Wire.write(x);
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in x
    Wire.write(SPEED1);
    Wire.write(x);
    Wire.endTransmission();

    encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
    encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
    volts();                                                // Calls function that reads and displays battery volts
    encoder1_cm = encoder1() * 10 * 3.14159 / 360;
  } while (encoder1_cm < 50);                                // Loop untill encoder 1 is 5000 or more

  stopMotor();                                               // Calls function to stop motors
  delay(1000);

  x = 106;                                                     // Put a value of 0 in x, this will drive motors at full reverse speed

  do {                                                       // Start loop to drive motors reverse
    Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in x
    Wire.write(SPEED2);
    Wire.write(x);
    Wire.endTransmission();

    Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in x
    Wire.write(SPEED1);
    Wire.write(x);
    Wire.endTransmission();

    encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
    encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
    volts();                                                // Calls function that reads and displays battery volts
    encoder1_cm = encoder1() * 10 * 3.14159 / 360;
  } while (encoder1_cm > 0);                                  // Loop untill encoder 1 is 0 or less

  stopMotor();                                              // Calls function to stop motors
  delay(1000);
}

byte getSoft() {                                             // Function that gets the software version
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to read software version as a single byte
  Wire.write(SOFTWAREREG);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 1);                         // request 1 byte form MD25
  while (Wire.available() < 1);                             // Wait for it to arrive
  byte software = Wire.read();                            // Read it in

  return (software);
}

void encodeReset() {                                       // This function resets the encoder values to 0
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(CMD);
  Wire.write(0x20);                                         // Putting the value 0x20 to reset encoders
  Wire.endTransmission();
}

long encoder1() {                                           // Function to read and display value of encoder 1 as a long
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to get a reading from encoder 1
  Wire.write(ENCODERONE);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 4);                         // Request 4 bytes from MD25
  while (Wire.available() < 4);                             // Wait for 4 bytes to arrive
  long poss1 = Wire.read();                                 // First byte for encoder 1, HH.
  poss1 <<= 8;
  poss1 += Wire.read();                                     // Second byte for encoder 1, HL
  poss1 <<= 8;
  poss1 += Wire.read();                                     // Third byte for encoder 1, LH
  poss1 <<= 8;
  poss1  += Wire.read();                                    // Fourth byte for encoder 1, LL

  //  Serial.write(LCD03_SET_CUR);
  //  Serial.write(21);                                         // Move cursor to space 21
  Serial.print("Encoder 1 ");
  Serial.print(poss1, DEC);                                 // Print encoder 1 value to LCD03
  Serial.print("   ");                                      // Print some spaces to clear space after encoder value
  delay(50);                                                // Wait for everything to make sure everything is sent

  return (poss1);
}

long encoder2() {                                           // Function to read and display velue of encoder 2 as a long
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(ENCODERTWO);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 4);                         // Request 4 bytes from MD25
  while (Wire.available() < 4);                             // Wait for 4 bytes to become available
  long poss2 = Wire.read();
  poss2 <<= 8;
  poss2 += Wire.read();
  poss2 <<= 8;
  poss2 += Wire.read();
  poss2 <<= 8;
  poss2  += Wire.read();

  //  Serial.write(LCD03_SET_CUR);
  //  Serial.write(41);
  Serial.print("Encoder 2 ");
  Serial.print(poss2, DEC);
  Serial.print("   ");                                      // Print some spaces to clear space after encoder value
  delay(50);                                                // Wait to make sure everything is sent

  return (poss2);
}

void volts() {                                              // Function to read and display battery volts as a single byte
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to read volts
  Wire.write(VOLTREAD);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 1);
  while (Wire.available() < 1);
  int batteryVolts = Wire.read();

  //  Serial.write(LCD03_SET_CUR);
  //  Serial.write(61);
  Serial.print("Battery v = ");
  Serial.print(batteryVolts / 10, DEC);                     // Print batery volts / 10 to give you the number of whole volts
  Serial.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  Serial.print(batteryVolts % 10, DEC);                     // Prints Battery volts % 10 to give us the

  delay(50);                                                // Wait to make sure everything is sent
}

void stopMotor() {                                          // Function to stop motors
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(128);                                           // Sends a value of 128 to motor 2 this value stops the motor
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(128);
  Wire.endTransmission();
}
