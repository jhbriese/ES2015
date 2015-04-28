int count = 0;

// PIN SetUp
int stBy = 5;
int ePWM = 2;
int eIn1 = 3;
int eIn2 = 4;
int pwPIN = 10;
int dirPIN = 11;

int pressed = 0;
int button = 0; // 0 = power, 1 = direction

//0 = Engine powering up; 1 = powering down;
int power = 0;

//Direction 0 = CW, 1 = CCW
int dir = 0;
int changeD = 0;

// Output
int val = 0;
int oldVal = 0;

void setup() {
  
  
  //Timer Setup
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC8);

  TC_Configure(TC2, 2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC2, 2, 41999);
  
  //Enable RC Compare Interrupt and disable all others
  TC2->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC8_IRQn);
  NVIC_EnableIRQ(TC8_IRQn);
  
  //Activate H-Bridge
  pinMode(stBy, OUTPUT);
  
  //Set Engine PINs
  pinMode(ePWM, OUTPUT);
  pinMode(eIn1, OUTPUT);
  pinMode(eIn2, OUTPUT);
  
  //Set Button PINs
  pinMode(pwPIN, INPUT);
  pinMode(dirPIN, INPUT);
  
  Serial.begin(9600);
  
  //enable H-Bridge
  digitalWrite(stBy, HIGH);
  
  //Set Engine to CW
  digitalWrite(eIn2, LOW);
  digitalWrite(eIn1, HIGH);
  
  TC_Start(TC2,2);
}

void loop() {
  Serial.println(val);
  analogWrite(ePWM,val);
  if(changeD == 1)
  {
    changeDir();
    changeD = 0;
  }
  delay(10);
}

void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  if (pressed == 0)
  {
    if (digitalRead(pwPIN) == 0)
    {
      pressed = 1;
      button = 0;
    }
    if (digitalRead(dirPIN) == 0)
    {
      pressed = 1;
      button = 1;
    }
  }
  else if (pressed >= 31)
  {
     if(button == 0 && digitalRead(pwPIN) == 0)
     {
       if(count==10)
       {
         if(power == 0)
           plus();
         else
           minus();
         count=0;
       }
       else
       {
         count++;
       }
       pressed++;
     }
     else if (button == 1 && digitalRead(dirPIN) == 0)
     {
       if(pressed == 31)
       {
         changeD = 1;
       }
       pressed++;
     }
     else
     {
       if(button == 0)
         {
           power=!power;
           count = 0;
         }
       pressed = 0;
     }
  }
  else
  {
    pressed++;
  }
  
}


void plus()
{
  val++;
    if (val > 255)
      val = 255;
}
void minus()
{
  val--;
  if (val < 0)
    val = 0;
}

void changeDir()
{
  if(val == 0 && val != oldVal)
  {
     dir = !dir;
     switch(dir)
      {
        case 0:
          digitalWrite(eIn2, LOW);
          digitalWrite(eIn1, HIGH);
          break;
        case 1:
          digitalWrite(eIn1, LOW);
          digitalWrite(eIn2, HIGH);
          break;
        default:
          digitalWrite(eIn1, LOW);
          digitalWrite(eIn2, LOW);
          break;
      }
     while(val != oldVal)
     {
       val++;
       analogWrite(ePWM,val);
       delay(10);
     }
  }
  else
  {
     oldVal = val;
     while(val != 0)
     {
       val--;
       analogWrite(ePWM,val);
       delay(10);
     }
  } 
}
