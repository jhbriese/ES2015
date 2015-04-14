int ledPin = 7;      // LED connected to digital pin 9
int minPin = 5;
int pluPin = 3;
int val = 0;         // variable to store the read value

void setup()
{
  pinMode(ledPin, OUTPUT);   // sets the pin as output
  pinMode(minPin, INPUT);
  pinMode(pluPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(pluPin) == 0)
  {
    val = (val+8) %256;
  }
  if (digitalRead(minPin) == 0)
  {
    val = (val-8) %256;
    if (val < 0)
      val = 255;
  }
  
  analogWrite(ledPin, val);
  delay(200);
  Serial.println(val);
}
