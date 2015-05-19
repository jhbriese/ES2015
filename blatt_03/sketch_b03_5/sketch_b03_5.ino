#include <Servo.h> 
int inInt = 0;
Servo myservo;

void setup() 
{
  myservo.attach(22);
  Serial.begin(9600);     
}

void loop() 
{
  // send data only when you receive data:
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    inInt = Serial.parseInt();
    // say what you got:
    Serial.print("#I received: ");
    Serial.println(inInt);
    moveTo(inInt);
    Serial.println("#End of Message\n");    
  }
}

void moveTo(int angle)
{
  if(angle < 20 || angle > 160)
  {
    Serial.println("ANGLE OUT OF RANGE ERROR! Pleas select angle between 20 and 160 degree!");
  }
  else
  {
    Serial.print("Moving to: ");
    Serial.print(angle);
    Serial.println(" degree");
    myservo.write(angle);
  }
}
