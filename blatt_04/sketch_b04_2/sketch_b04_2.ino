#include <Wire.h>

int fSend = 0;
int transmission;

void setup() 
{
  // put your setup code here, to run once:
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC8);

  TC_Configure(TC2, 2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_SetRC(TC2, 2, 1312499);
  
  //Enable RC Compare Interrupt and disable all others
  TC2->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC8_IRQn);
  NVIC_EnableIRQ(TC8_IRQn);
  
  Serial.begin(9600);
  Wire.begin();
  
  TC_Start(TC2,2);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(fSend == 1)
  {
    fSend = 0;
    Wire.beginTransmission(9);
      Serial.print("SENDING CHANGE STATE: ");
      Wire.write(10);          //10 = Change LED State
    transmission = Wire.endTransmission();
    switch(transmission)
    {
      case 0:
        Serial.println("SUCCESS");
        break;
      case 1:
        Serial.println("DATA TO LONG");
        break;
      case 2:
        Serial.println("NACK ADDRESS");
        break;
      case 3:
        Serial.println("NACK DATA");
        break;
      case 4:
        Serial.println("GENERAL ERROR");
        break;
    }
    delay(100); //Wait for slave to change state
    Wire.requestFrom(9, 1);
    while(Wire.available())
    { 
      int rcv = Wire.read();
      switch(rcv)
      {
        case 0:
          Serial.println("================\nReceived LED OFF\n================\n");
          break;
        case 1:
          Serial.println("================\nReceived LED ON\n================\n");
          break;
      }
    }
  }
}

void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  fSend = 1;//Set Send Flag
}
