String inString = "";
int pinLED = 13;

void setup() 
{
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
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
    stringToCode(inString);
    Serial.println("\n#End of Message");    
  }
}

void stringToCode(String string)
{
  int sLength = string.length();
  char chars[sLength + 1];
  string.toCharArray(chars, sLength +1);
  
  String code = "";
  
  for(int i = 0; i < sLength; i++)
  {
    //Serial.print("Convert: ");
    //Serial.println(chars[i]);
    switch(chars[i])
    {
      case 'a':
      case 'A':
        code += "123";
        break;
      case 'b':
      case 'B':
        code += "21113";
        break;
      case 'c':
      case 'C':
        code += "21213";
        break;
      case 'd':
      case 'D':
        code += "2113";
        break;
      case 'e':
      case 'E':
        code += "13";
        break;
      case 'f':
      case 'F':
        code += "11213";
        break;
      case 'g':
      case 'G':
        code += "2213";
        break;
      case 'h':
      case 'H':
        code += "11113";
        break;
      case 'i':
      case 'I':
        code += "113";
        break;
      case 'j':
      case 'J':
        code += "12223";
        break;
      case 'k':
      case 'K':
        code += "2123";
        break;
      case 'l':
      case 'L':
        code += "12113";
        break;
      case 'm':
      case 'M':
        code += "223";
        break;
      case 'n':
      case 'N':
        code += "213";
        break;
      case 'o':
      case 'O':
        code += "2223";
        break;
      case 'p':
      case 'P':
        code += "12213";
        break;
      case 'q':
      case 'Q':
        code += "22123";
        break;
      case 'r':
      case 'R':
        code += "1213";
        break;
      case 's':
      case 'S':
        code += "1113";
        break;
      case 't':
      case 'T':
        code += "23";
        break;
      case 'u':
      case 'U':
        code += "1123";
        break;
      case 'v':
      case 'V':
        code += "11123";
        break;
      case 'w':
      case 'W':
        code += "1223";
        break;
      case 'x':
      case 'X':
        code += "21123";
        break;
      case 'y':
      case 'Y':
        code += "21223";
        break;
      case 'z':
      case 'Z':
        code += "22113";
        break;
      case ' ':
        code += "4";
        break;
    }
    //Serial.print("code: ");
    //Serial.println(code);
  }
  parseCode(code);
}

void parseCode(String code)
{
  int sLength = code.length();
  String sign;
  for(int i = 0; i < sLength; i++)
  {
    sign = code.substring(i, i+1);
    //Serial.println(sign);
    blinkCode(sign.toInt());
  }
}

void blinkCode(int sign)
{
   switch(sign)
   {
      case 1: //Read dit (.)
        digitalWrite(pinLED, HIGH);
        Serial.print("dit ");
        delay(100);
        digitalWrite(pinLED, LOW);
        delay(100);
        break;
      case 2: //Read dat (-)
        digitalWrite(pinLED, HIGH);
        Serial.print("dat ");
        delay(300);
        digitalWrite(pinLED, LOW);
        delay(100);
        break;
      case 3: //Read break between chars
        Serial.print(" ");
        delay(300);
        break;
      case 4: //Read brak between words
        Serial.print("    ");
        delay(700);
        break;
   }
}
