int ledPin = 7;
int val = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  attachInterrupt(3, plus, RISING);
  attachInterrupt(5, minus, RISING);
  Serial.begin(9600);
}

void loop()
{
  analogWrite(ledPin, val);
  delay(200);
  Serial.println(val);
}

void plus()
{
  delayMicroseconds(10000);
  val = (val+8) %256;
}
void minus()
{
  delayMicroseconds(10000);
  val = (val-8) %256;
  if (val < 0)
    val = 255;
}
