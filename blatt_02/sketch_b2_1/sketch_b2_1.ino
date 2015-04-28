int ledPin = 7;
int minPin = 10;
int pluPin = 11;
int pressed = 0;
int button = 0; // 0 = plus, 1 = minus

int val = 0;

void setup() 
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);

  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC0, 0, 41999);
  
  //Enable RC Compare Interrupt and disable all others
  TC0->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC0_IRQn);

  pinMode(ledPin, OUTPUT);
  pinMode(minPin, INPUT);
  pinMode(pluPin, INPUT);

  
  Serial.begin(9600);
  
  TC_Start(TC0,0);

}

void loop() 
{
   //
}

void TC0_Handler()
{
  TC_GetStatus(TC0, 0);
  if (pressed == 0)
  {
    if (digitalRead(pluPin) == 0)
    {
      pressed = 1;
      button = 0;
    }
    if (digitalRead(minPin) == 0)
    {
      pressed = 1;
      button = 1;
    }
  }
  else if (pressed >= 31)
  {
     if(button == 0 && digitalRead(pluPin) == 0)
     {
       if(pressed == 31)
       {
         plus();
       }
       pressed++;
     }
     else if (button == 1 && digitalRead(minPin) == 0)
     {
       if(pressed == 31)
       {
         minus();
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
  analogWrite(ledPin, val);
  
}

void plus()
{
  val = val + 8;
    if (val > 255)
      val = 255;
  Serial.println(val);
}
void minus()
{
  val = val - 8;
  if (val < 0)
    val = 0;
  Serial.println(val);
}
