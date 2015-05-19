#include <Servo.h> 

Servo myservo; 
float pos = 90.0;

//PIN Setup IXZ-500
int xVref=A0;
int xZ=A1;
int xAz=2;
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

void setup() {
  myservo.attach(22);
  pinMode(xAz, OUTPUT);
  pinMode(xZ, INPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(xAz, LOW);
  
  //Timer Setup
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC8);

  TC_Configure(TC2, 2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_SetRC(TC2, 2, 4199999);
  
  //Enable RC Compare Interrupt and disable all others
  TC2->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
  TC2->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    
  NVIC_ClearPendingIRQ(TC8_IRQn);
  NVIC_EnableIRQ(TC8_IRQn);
  
  Serial.begin(9600);
  
  TC_Start(TC2,2);
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
    //get Gyro RefSignal
    valRef = analogRead(xVref);
    valZ = analogRead(xZ);
    
    if(fCal == 1 && calCount <= 10)
    {
        calCount++;
        if(calZ != 0)
        {
          calZ = (calZ + float(valZ - valRef))/2.0;
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
        rotate(CalcDeg(float(valZ)-calZ));
        /*Serial.print(pos);
        Serial.print("/");
        Serial.print(CalcDeg(float(valZ)-calZ));
        Serial.print("\n");*/
    }
  }  
}

 
void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  fRead = 1;  
}

float CalcDeg(float val)
{
  return (val - float(valRef))/2.0/4.9;
}

void rotate(float rate)
{
  pos=pos+(rate/10.0);
  myservo.write(pos);
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
