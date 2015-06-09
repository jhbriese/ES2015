int ledPin = 53;
int btPin = 5;

int fSend = 0;

int pressed = 0;

int inInt = 0;

void setup() 
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC8);

  TC_Configure(TC2, 2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC2, 2, 41999);
  
  //Enable RC Compare Interrupt and disable all others
  TC2->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC8_IRQn);
  NVIC_EnableIRQ(TC8_IRQn);

  pinMode(ledPin, OUTPUT);
  pinMode(btPin, INPUT);

  digitalWrite(ledPin, LOW);
  
  Serial1.begin(9600);
  Serial.begin(9600);
  
  TC_Start(TC2,2);

}

void loop() 
{
  if (Serial1.available() > 0) 
  {
    // read the incoming byte:
    inInt = Serial1.read();
    // say what you got:
    Serial.print("#I received: ");
    Serial.println(inInt, DEC);
    if(inInt == 1)
    {
      blinkLED(3);
    }
    Serial.println("\n#End of Message");    
  }
  
  if(fSend == 1)
  {
    Serial.println("#Send");
    Serial1.write(1);
    fSend = 0;
  }
}

void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  if (pressed == 0)
  {
    if (digitalRead(btPin) == 0)
    {
      pressed = 1;
    }
  }
  else if (pressed >= 31)
  {
     if(digitalRead(btPin) == 0)
     {
       if(pressed >= 31)
       {
         fSend = 1;
       }
       pressed++;
     }
     else
     {
       pressed = 0;
     }
  }
  else
  {
    pressed++;
  }
}

void blinkLED(int count)
{
  for(int i = 0; i<count; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}
