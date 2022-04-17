// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

void setup()
{  
  Serial.begin(9600);
  emon1.current(A1, 60);             //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000 (numero de espiras do transformador/38 = 52.63
}

void loop()
{
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  Serial.println(Irms);		       // Irms
}
