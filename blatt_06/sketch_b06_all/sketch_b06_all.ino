#include <SPI.h>
#include <SD.h>

//ASCII fontset
unsigned char font[95][6] =
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // space
  { 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, // !
  { 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, // "
  { 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, // #
  { 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, // $
  { 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, // %
  { 0x36, 0x49, 0x55, 0x22, 0x50, 0x00 }, // &
  { 0x00, 0x00, 0x07, 0x00, 0x00, 0x00 }, // '
  { 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, // (
  { 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, // )
  { 0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00 }, // *
  { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, // +
  { 0x00, 0x50, 0x30, 0x00, 0x00, 0x00 }, // ,
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, // -
  { 0x00, 0x60, 0x60, 0x00, 0x00, 0x00 }, // .
  { 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, // slash
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1
  { 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2
  { 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3
  { 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, // 4
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5
  { 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6
  { 0x03, 0x71, 0x09, 0x05, 0x03, 0x00 }, // 7
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8
  { 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9
  { 0x00, 0x36, 0x36, 0x00, 0x00, 0x00 }, // :
  { 0x00, 0x56, 0x36, 0x00, 0x00, 0x00 }, // ;
  { 0x08, 0x14, 0x22, 0x41, 0x00, 0x00 }, // <
  { 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, // =
  { 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, // >
  { 0x02, 0x01, 0x51, 0x09, 0x06, 0x00 }, // ?
  { 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00 }, // @
  { 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00 }, // A
  { 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // B
  { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, // C
  { 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // D
  { 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // E
  { 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // F
  { 0x3E, 0x41, 0x41, 0x49, 0x7A, 0x00 }, // G
  { 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, // H
  { 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, // I
  { 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, // J
  { 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // K
  { 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // L
  { 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00 }, // M
  { 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // N
  { 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // O
  { 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // P
  { 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, // Q
  { 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // R
  { 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, // S
  { 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00 }, // T
  { 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // U
  { 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // V
  { 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // W
  { 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // X
  { 0x07, 0x08, 0x70, 0x08, 0x07, 0x00 }, // Y
  { 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // Z
  { 0x00, 0x7F, 0x41, 0x41, 0x00, 0x00 }, // [
  { 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, // backslash
  { 0x00, 0x41, 0x41, 0x7F, 0x00, 0x00 }, // ]
  { 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, // ^
  { 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, // _
  { 0x00, 0x01, 0x02, 0x04, 0x00, 0x00 }, // `
  { 0x20, 0x54, 0x54, 0x54, 0x78, 0x00 }, // a
  { 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00 }, // b
  { 0x38, 0x44, 0x44, 0x44, 0x20, 0x00 }, // c
  { 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00 }, // d
  { 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, // e
  { 0x08, 0x7E, 0x09, 0x01, 0x02, 0x00 }, // f
  { 0x08, 0x54, 0x54, 0x54, 0x3C, 0x00 }, // g
  { 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, // h
  { 0x00, 0x48, 0x7D, 0x40, 0x00, 0x00 }, // i
  { 0x20, 0x40, 0x44, 0x3D, 0x00, 0x00 }, // j
  { 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, // k
  { 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, // l
  { 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 }, // m
  { 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, // n
  { 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, // o
  { 0x7C, 0x14, 0x14, 0x14, 0x08, 0x00 }, // p
  { 0x08, 0x14, 0x14, 0x18, 0x7C, 0x00 }, // q
  { 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, // r
  { 0x48, 0x54, 0x54, 0x54, 0x20, 0x00 }, // s
  { 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00 }, // t
  { 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, // u
  { 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, // v
  { 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, // w
  { 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, // x
  { 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00 }, // y
  { 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, // z
  { 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, // {
  { 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00 }, // |
  { 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, // }
  { 0x10, 0x08, 0x08, 0x10, 0x08, 0x00 } // ~
};

//LCD Parameter
int slaveSelectLCD = 10;
int rstPin = 6;
int ledPin = 2;
int dcPin = 5;
int clkDivider = 84;

//SD Parameter
int slaveSelectSD = 4;
File sdFile;
String inString = "";

//LCD Buffer to transmit
byte pixBuffer[6][84];

int testValue=0;

void setup() 
{
  pinMode(rstPin, OUTPUT);
  digitalWrite(rstPin, LOW);
  delay(500);
  digitalWrite(rstPin, HIGH);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  pinMode(dcPin, OUTPUT);
  
  Serial.begin(115200);

  SD.begin(slaveSelectSD);
  
  SPI.begin(slaveSelectLCD);
  SPI.setClockDivider(slaveSelectLCD, clkDivider);
  
  digitalWrite(dcPin, LOW);
  SPI.transfer(slaveSelectLCD, 0x21);
  SPI.transfer(slaveSelectLCD, 0x14);
  SPI.transfer(slaveSelectLCD, 0xB0);
  SPI.transfer(slaveSelectLCD, 0x20);
  SPI.transfer(slaveSelectLCD, 0x0C);
  digitalWrite(dcPin, HIGH);
  
  setWhite();

  Serial.print("Enter next File to read: ");
  //readTextFile("text2.txt");
  //readPicFile("smile1.img");
}

void loop() 
{
  
  // send data only when you receive data:
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    inString = Serial.readString();
    // say what you got:
    char filename[sizeof(inString)];
    inString.toCharArray(filename, sizeof(inString));
    switch(parseFileExtension(inString))
    {
      case 1:
        Serial.print("Openning Image File: ");
        Serial.print(filename);
        Serial.print("\n\n\n");
        readPicFile(filename);
        break;
      case 2:
        Serial.print("Openning Text File: ");
        Serial.print(filename);
        Serial.print("\n\n\n");
        readTextFile(filename);
        break;
      default:
        Serial.println("ERROR parsing FileExtension\n\n\n\n");
        break;
    }
    Serial.print("Enter next File to read: ");   
  }
}

int parseFileExtension(String string)
{
  String extension = string.substring(string.length()-3,string.length());
  if(extension == "img")
  {
    Serial.println("Detected Image file");
    return 1;
  }
  else if(extension == "txt")
  {
    Serial.println("Detected Text file");
    return 2;
  }
  else
  {
    Serial.println("No known Fileformat detected");
    return 0;
  }
}

/* ####################
 * # LCD Function Set # 
 * ####################
 */
int setPixel(int x, int y, int value)
{
  if(x > 83 || x < 0 || y > 47 || y < 0)
    return 1;                           //index out of range Error
  
  int yBank = (y/8);
  int yBit = y % 8;
  
  pixBuffer[yBank][x] ^= (-value ^ pixBuffer[yBank][x]) & (1 << yBit); 
  
  return 0;                             //Well done
}

int setChar(int x, int y, char asciiChar)
{
  int error;
  if(x > 78 || x < 0 || y > 40 || y < 0)
    return 1;                           //index out of range Error
  
  byte tmpRow;
  int tmpBit;
  
  for(int xOff=0; xOff<6; xOff++)
  {
    tmpRow = font[asciiChar-32][xOff];
    for(int yOff=0; yOff<8; yOff++)
    {
      tmpBit = (tmpRow>>yOff)&1;
      error = setPixel(x+xOff, y+yOff, tmpBit);
    }
  }
  transferBuffer();
  
  return error;
}


void setWhite()
{
  resetBuffer();
  transferBuffer();
}

void resetBuffer()
{
  for(int n=0;n<6;n++)
  {
    for(int m=0;m<84;m++)
    {
      pixBuffer[n][m] = 0x00;
    }
  }
}
void transferBuffer()
{
  //go to first RAM Adress (y=0, x=0)
  digitalWrite(dcPin, LOW);
  SPI.transfer(slaveSelectLCD, 0x40);
  SPI.transfer(slaveSelectLCD, 0x80);
  //write Buffer to Display
  digitalWrite(dcPin, HIGH);
  for(int n=0;n<6;n++)
  {
    for(int m=0;m<84;m++)
    {
      SPI.transfer(slaveSelectLCD, pixBuffer[n][m]);
    }
  }
}

/* ###################
 * # SD Function Set # 
 * ###################
 */

int checkFileSD(char *fileName)
{
  Serial.print("Checking file: ");
  Serial.println(fileName);
  
  if(SD.exists(fileName))
  {
    //File exists
    Serial.println("Found file!");
    sdFile = SD.open(fileName);
    if(sdFile.available() > 0)
    {
      Serial.print("File has: ");
      //Serial.print(sdFile.available());
      Serial.println(" Bytes");
      return 0; //File exists with content
    }
    else
    {
      Serial.println("File is empty!");
      return 1; //File exists without content
    }
  }
  else
  {
    Serial.println("File not found!");
    return 2; //File not found
  }
}

int readTextFile(char *fileName)
{
  setWhite();
  Serial.print("Read Textfile: ");
  Serial.println(fileName);
  
  int error = checkFileSD(fileName);
  int tmpError = 0;
  if(error == 0)
  {
    Serial.println("File check: OK");
    
    int writeX = 0;
    int writeY = 0;
    while(sdFile.available()) 
    {
      tmpError += setChar(writeX, writeY, sdFile.read());
      
      writeX+=6;
      if(writeX > 83)
      {
        writeY+=8;
        writeX=0;
      }
    }
    sdFile.close();
  }
  else
  {
    Serial.print("File check: Error: ");
    Serial.println(error);
    
    tmpError += setChar(0, 0, 'F');
    tmpError += setChar(6, 0, 'i');
    tmpError += setChar(12, 0, 'l');
    tmpError += setChar(18, 0, 'e');
    tmpError += setChar(24, 0, ' ');
    tmpError += setChar(30, 0, 'E');
    tmpError += setChar(36, 0, 'r');
    tmpError += setChar(42, 0, 'r');
    tmpError += setChar(48, 0, 'o');
    tmpError += setChar(54, 0, 'r');
    tmpError += setChar(60, 0, ':');
    tmpError += setChar(66, 0, ' ');
    tmpError += setChar(72, 0, (char)error+48);
  }
}

int readPicFile(char *fileName)
{
  setWhite();
  Serial.print("Read Imagefile: ");
  Serial.println(fileName);
  
  int error = checkFileSD(fileName);
  int tmpError = 0;
  if(error == 0)
  {
    Serial.println("File check: OK");
    
    int lineNo = 0;
    int detCom = 0;
    int dimX = 0;
    String tmpX = "";
    int dimY = 0;
    String tmpY = "";
    char tmpCh;
    String pixels = "";
    int startX = 0;
    int startY = 0;    
    
    while(sdFile.available()) 
    {
      tmpCh = sdFile.read();
      if(lineNo == 0)
      {
        if(tmpCh == '\n')
        {
          lineNo++;
          detCom = 0;
        }
        if(tmpCh == ',')
        {
          detCom = 1;
        }
        else
        {
          if(detCom == 0)
          {
            tmpX += tmpCh;
          }
          else
          {
            tmpY += tmpCh;
          }
        }
      }
      else
      {
        if(tmpCh != ',' && tmpCh != '\n')
          pixels += tmpCh;
      }
    }
    
    sdFile.close();

    dimX = tmpX.toInt();
    dimY = tmpY.toInt();

    startX = ((84 / 2) - (dimX / 2));
    startY = ((48 / 2) - (dimY / 2));

    Serial.println("Pixels for x,y:");
    int i = 0;
    for(int row = 0; row < dimY; row++)
    {
      for(int col = 0; col < dimX; col++)
      {
        setPixel(startX + col, startY + row, int(pixels.charAt(i))-48);
        i++;
      }
    }
    transferBuffer();
  }
  else
  {
    Serial.print("File check: Error: ");
    Serial.println(error);
    
    tmpError += setChar(0, 0, 'F');
    tmpError += setChar(6, 0, 'i');
    tmpError += setChar(12, 0, 'l');
    tmpError += setChar(18, 0, 'e');
    tmpError += setChar(24, 0, ' ');
    tmpError += setChar(30, 0, 'E');
    tmpError += setChar(36, 0, 'r');
    tmpError += setChar(42, 0, 'r');
    tmpError += setChar(48, 0, 'o');
    tmpError += setChar(54, 0, 'r');
    tmpError += setChar(60, 0, ':');
    tmpError += setChar(66, 0, ' ');
    tmpError += setChar(72, 0, (char)error+48);
  }
}

