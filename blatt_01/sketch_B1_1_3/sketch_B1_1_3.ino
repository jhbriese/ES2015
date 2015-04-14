int pin = 7;
volatile int state = HIGH;

void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(3, blink, RISING);
}

void loop()
{
  digitalWrite(pin, state);
}

void blink()
{
  state = !state;
}
