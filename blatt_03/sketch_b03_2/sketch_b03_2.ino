#include <Servo.h> 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(32, 31, 44, 45, 46, 47);
 
Servo myservo;   
 
int pos = 90;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(22);  // attaches the servo on pin 9 to the servo object 
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Pos: "); 
} 
 
 
void loop() 
{ 
  for(pos = 0; pos <= 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);    // tell servo to go to position in variable 'pos' 
    printLCD(pos);
    delay(1);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);    // tell servo to go to position in variable 'pos' 
    printLCD(pos);
    delay(1);                       // waits 15ms for the servo to reach the position 
  } 
}

void printLCD(int val)
{
  lcd.setCursor(5, 0);
  lcd.print("   ");
  lcd.setCursor(5, 0);
  lcd.print(myservo.read());
}
