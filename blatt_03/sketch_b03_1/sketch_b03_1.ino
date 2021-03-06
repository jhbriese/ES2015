// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(32, 31, 44, 45, 46, 47);

//PIN Setup IXZ-500
int xVref=A0;
int xX=A1;
int xZ=A2;
int xAz=0;

//Gyro Axis
int valX = 0;
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
float calX = 0.0;
float calZ = 0.0;

//Counter for write delay
int wcount = 0;

void setup() {
  pinMode(xAz, OUTPUT);
  pinMode(xX, INPUT);
  pinMode(xZ, INPUT);
  
  digitalWrite(xAz, LOW);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("X: ");
  lcd.setCursor(0,1);
  lcd.print("Z: ");
  
  //Timer Setup
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);

  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC0, 0, 4199999);
  
  //Enable RC Compare Interrupt and disable all others
  TC0->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC0_IRQn);
  
  //get Gyro RefSignal
  valRef += analogRead(xVref);
  
  TC_Start(TC0,0);
}

void loop() {
  if(fAz == 1)
  {
    digitalWrite(xAz, HIGH);
    delayMicroseconds(1700);
    digitalWrite(xAz, LOW);
    fAz = 0;
  }
  
  if(fRead == 1)
  {
    fRead = 0;
    
    valX = analogRead(xX);       // read analog input pin 0
    valZ = analogRead(xZ);       // read analog input pin 1
    
    if(fCal == 1 && calCount <= 10)
    {
        calCount++;
        if(calX != 0 && calZ != 0)
        {
          calX = (calX + float(valX - valRef))/2.0;
          calZ = (calZ + float(valZ - valRef))/2.0;
        }
        else
        {
          calX = float(valX - valRef);
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
      if (wcount >= 5)
      {
        PrintX();
        PrintZ();
        wcount = 0;
      }
      else
      {
        wcount++;
      }
    }
  }  
}

 
void TC0_Handler()
{
  TC_GetStatus(TC0, 0);
  fRead = 1;  
}

void PrintX()
{
  lcd.setCursor(3, 0);
  lcd.print("                ");
  lcd.setCursor(3, 0);
  lcd.print(CalcDeg(float(valX)-calX));
  lcd.print(" Deg");
}

void PrintZ()
{
  lcd.setCursor(3, 1);
  lcd.print("                ");
  lcd.setCursor(3, 1);
  lcd.print(CalcDeg(float(valZ)-calZ));
  lcd.print(" Deg");
}

float CalcDeg(float val)
{
  return (val - float(valRef)) / 1.86368;
}
