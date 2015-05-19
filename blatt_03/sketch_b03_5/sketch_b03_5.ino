#include <Servo.h> 
String inString = "";
int pinLED = 13;

Servo myservo;

void setup() 
{
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  myservo.attach(10);
  Serial.begin(9600);     
}

void loop() 
{
  // send data only when you receive data:
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    inString = Serial.readString();
    // say what you got:
    Serial.print("#I received: ");
    Serial.println(inString);
    parseString(inString);
    Serial.println("\n#End of Message");    
  }
}

void parseString(String string)
{
  int endNumber = 0;
  if(string.substring(0,7) == "moveTo(")
  {
    int endNumber = string.indexOf(")");
    int angle = 0;
    if(string.length() != endNumber + 1)
    {
      printError("Length error or ) missing");
    }
    else
    {
      angle = string.substring(7,endNumber).toInt();
      if(angle > 155 || angle < 25)
      {
        Serial.print("ANGLE OUT OF RANGE: RANGE = 25-155: ");
        Serial.println(angle);
      }
      else
      {
        myservo.write(angle);
      }
    }
  }
  else
  {
    printError("Invalid Function");
  }
}

void printError(String msg)
{
  Serial.print("Illigal Input detected: ");
  Serial.println(msg);
}
