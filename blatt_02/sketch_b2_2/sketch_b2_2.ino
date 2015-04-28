// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(32, 31, 44, 45, 46, 47);

int count = 0;

// PIN SetUp
int stBy = 5;
int ePWM = 2;
int eIn1 = 3;
int eIn2 = 4;

//1 = Engine powering up; 2 = powering down; 0 = Off
int power = 0;

//Direction 0 = CW, 1 = CCW
int dir = 0;

// Output
int val = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Power: ");
  lcd.setCursor(0,1);
  lcd.print("Direction: ");
  
  //Timer Setup
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);

  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC0, 0, 419999);
  
  //Enable RC Compare Interrupt and disable all others
  TC0->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC0_IRQn);
  
  TC_Start(TC0,0);
  
  //Activate H-Bridge
  pinMode(stBy, OUTPUT);
  digitalWrite(stBy, HIGH);
  
  //Set Engine PINs
  pinMode(ePWM, OUTPUT);
  pinMode(eIn1, OUTPUT);
  pinMode(eIn2, OUTPUT);
}

void loop() {
    if(power == 0) //first activation
  {
    power = 1;
    val = val + 5;
  }
  else if(power == 1)
  {
    if(val <= 250)
    {
      val = val + 5;
    }
    else
    {
      power = 2;
    }
  }
  else if(power ==2)
  {
    if(val >= 5)
    {
      val = val - 5;
    }
    else
    {
      power = 1;
      dir = !dir;
    }
  }
  
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
  
  analogWrite(ePWM, val);
  PrintVal();
  PrintDir();
  
  delay(100);
}

void TC0_Handler()
{
  TC_GetStatus(TC0, 0);
  

}

void PrintVal()
{
  lcd.setCursor(7, 0);
  lcd.print("        ");
  lcd.setCursor(7, 0);
  lcd.print(val/2.55);
  lcd.print(" %");
}

void PrintDir()
{
  lcd.setCursor(11, 1);
  if(dir == 0)
    lcd.print("CW ");
  else
    lcd.print("CCW");
}
