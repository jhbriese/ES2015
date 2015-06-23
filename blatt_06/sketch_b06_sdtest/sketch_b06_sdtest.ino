#include <SPI.h>
#include <SD.h>

//SD Parameter
int slaveSelectSD = 4;
File sdFile;

void setup() 
{    
  Serial.begin(115200);

  SD.begin(slaveSelectSD);

  readTextFile("text1.txt");
}

void loop() 
{
  //
}

/* ###################
 * # SD Function Set # 
 * ###################
 */

int checkFileSD(char *fileName)
{
  Serial.print("Checking file: ");
  Serial.println(fileName);
  
  if(SD.exists(fileName) == true)
  {
    //File exists
    Serial.println("Found file!");
    sdFile = SD.open(fileName);
    if(sdFile.available() > 0)
    {
      Serial.print("File has: ");
      Serial.print(sdFile.available());
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
  Serial.print("Read Textfile: ");
  Serial.println(fileName);
  
  int error = checkFileSD(fileName);
  int tmpError = 0;
  if(error == 0)
  {
    Serial.println("File check: OK");
    
    int writeX = 0;
    while(sdFile.available()) 
    {
      Serial.print(sdFile.read());
      writeX+=6;
      Serial.println(writeX);
    }
    sdFile.close();
  }
  else
  {
    Serial.print("File check: Error: ");
    Serial.println(error);
    
  }
}

