#include <Servo.h>
#include <Wire.h>
#include <stdint.h>  

Servo myservo; 
float pos = 90.0;
float rate = 0.0;

int led=51;
char rcv[10];

//Read flag
int fRead = 0;

//Request Flag (0 = valZ, 1 = 
int fReq = 0;

void setup() 
{
  myservo.attach(10);
  
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
  Wire.begin();
  
  digitalWrite(led, LOW);
  
  TC_Start(TC2,2);
}

void loop() 
{
  if(fRead == 1)
  {
    char rcv[sizeof(float)];
    float rate;
    int i = 0;
    //Serial.print("Request pos: ");
    Wire.requestFrom(9, sizeof(float));
    while(Wire.available())
    { 
      rcv[i] = Wire.read();
      i++;      
    }
    charToFloat(&rcv[0], &rate);
    i = 0;
    Serial.print("Rate Value: ");
    Serial.print(rate); 
    Serial.print("  char Values 0: ");
    Serial.print(rcv[0]);
    Serial.print("  1: ");
    Serial.print(rcv[1]);
    Serial.print("  2: ");
    Serial.print(rcv[2]);
    Serial.print("  3: ");
    Serial.println(rcv[3]);
    
    rotate(rate);
  }  
}

void charToFloat(char* input, float* output)
{
  char* tmpChar = (char*) output;

  for(int i=0; i<sizeof(float); i++)
  {
      tmpChar[i] = input[i]; 
  }
}

 
void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  fRead = 1; 
}

void rotate(float rate)
{
  if(pos+(rate/10) > 160 || pos+(rate/10) < 20)
  {
    blinkLED();
  }
  else
  {
    pos=pos+(rate/10);
    myservo.write(pos);
  }
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
