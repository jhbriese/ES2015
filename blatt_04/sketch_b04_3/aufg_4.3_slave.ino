//############################################################

#include <Wire.h>




//PIN Setup IXZ-500
int xVref=A0;
int xZ=A1;
int xAz=5;
int led=13;

//Gyro Axis
int valZ = 0;
int valRef= 0;

//Read flag
int fRead = 0;

//AZ flag
int fAz = 1;

//Calibration Flag
int fCal = 1;

//Calibration Values
int calCount = 0;
float calZ = 0.0;

int slaveAdresse= 9;
char datpakIC[sizeof(float)];

void setup() {
 
  Wire.begin(slaveAdresse);
  Wire.onRequest(myHandlerRequest); 
 
  pinMode(xAz, OUTPUT);
  pinMode(xZ, INPUT);
  digitalWrite(xAz, LOW);

Serial.begin(9600);

}

void loop() {
  if(fAz == 1)
  {
    digitalWrite(xAz, HIGH);
    delayMicroseconds(1700);
    digitalWrite(xAz, LOW);
    fAz = 0;
  }
}

void myHandlerRequest()
{
  //get Gyro RefSignal
  valRef = analogRead(xVref);
  valZ = analogRead(xZ);
  if(fCal == 1 && calCount <= 10)
  {
    calCount++;
    if(calZ != 0)
    {
      calZ = (calZ + float(valZ - valRef))/2.0/4.9;
    }
    else
    {
      calZ = float(valZ - valRef);
    }
  }
 
  else if(calCount > 10)
  {
    calCount = 0;
    fCal = 0;
  }
 
  else
  {
    // Erste Möglichkeit
      float ergebnis=(CalcDeg(float(valZ)-calZ));
      Serial.println(ergebnis);
//      int anzahlDatenPak;
//      anzahlDatenPak = sprintf(datpakIC,"%f",ergebnis);
  
     
     
      // Master Code
      // Quelle: http://www.cplusplus.com/reference/cstdio/scanf/
      // mit der Funktion scanf müssen beim Master die Datenpakete in den datentyp Float umgewandelt werden (Denke ich)
      // 
      
      // Zweite Möglichkeit
     floatToChar(&ergebnis,&datpakIC[0]);
      Serial.println(datpakIC[0]);
      for(int i=0; i<sizeof(float); i++)
      {
        Wire.write(datpakIC[i]);
      }
     
  }
}

float CalcDeg(float val)
{
  return (val - float(valRef))/2.0/4.9;
}



void blinkLED()
{
  for(int i=0; i <= 2; i++)
  {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  }
}
 void floatToChar(float* input, char* output)
 {
   char* tmpChar = (char*) input;
   for(int i=0; i<sizeof(float);i++)
   {
     output[i] = tmpChar[i];
   }
 }
 
 
 

//##############################################################################
