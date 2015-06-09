#include <SPI.h>

//LCD Parameter
int slaveSelectPin = 10;
int rstPin = 6;
int ledPin = 20;
int dcPin = 5;
int clkDivider = 84;

//LCD Buffer to transmit
byte pixBuffer[6][84];

void setup() 
{
  pinMode(rstPin, OUTPUT);
  digitalWrite(rstPin, LOW);
  delay(500);
  digitalWrite(rstPin, HIGH);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  pinMode(dcPin, OUTPUT);
  
  SPI.begin(slaveSelectPin);
  SPI.setClockDivider(slaveSelectPin, clkDivider);
  
  digitalWrite(dcPin, LOW);
  SPI.transfer(slaveSelectPin, 0x21);
  SPI.transfer(slaveSelectPin, 0x14);
  SPI.transfer(slaveSelectPin, 0xB0);
  SPI.transfer(slaveSelectPin, 0x20);
  SPI.transfer(slaveSelectPin, 0x0C);
  digitalWrite(dcPin, HIGH);
  
  setWhite();
}

void loop() 
{
  
  
}

void setPixel(int x, int y, int value)
{
  //ToDo
}

void setWhite()
{
  resetBuffer();
  transferBuffer();
}

void resetBuffer()
{
  for(int n=0;n<6;n++)
  {
    for(int m=0;m<84;m++)
    {
      pixBuffer[n][m] = 0x00;
    }
  }
}
void transferBuffer()
{
  //go to first RAM Adress (y=0, x=0)
  digitalWrite(dcPin, LOW);
  SPI.transfer(slaveSelectPin, 0x40);
  SPI.transfer(slaveSelectPin, 0x80);
  //write Buffer to Display
  digitalWrite(dcPin, HIGH);
  for(int n=0;n<6;n++)
  {
    for(int m=0;m<84;m++)
    {
      SPI.transfer(slaveSelectPin, pixBuffer[n][m]);
    }
  }
}
