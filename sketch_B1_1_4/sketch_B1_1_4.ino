int ledPin = 7;      // LED connected to digital pin 9
//int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 0;         // variable to store the read value

void setup()
{
  pinMode(ledPin, OUTPUT);   // sets the pin as output
  Serial.begin(9600);
}

void loop()
{
  val= (val+8) %256;
  analogWrite(ledPin, val);
  delay(200);
  Serial.println(val);
  //Serial.print("\n");
}
