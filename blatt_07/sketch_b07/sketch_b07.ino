int rxCount = 0;

void setup() 
{
  // Enable Serial3 (18,19) to get NEMA-Data
  Serial1.begin(9600);
  // Enable Serial console fpr debugging
  Serial.begin(9600);
  
}

void loop() 
{
  if (Serial1.available() > 0) 
  {
    String msg = Serial1.readStringUntil('\n');
    String gga = "";
    // We only need the $GPGGA Data
    if(msg.substring(0,6) == "$GPGGA")
    {
      gga = String(rxCount) + ": " + msg;
      Serial.println(gga);
      rxCount++;
    }
  }
}
/*
 * ggaPaser Funtion
 * @return Returns Error Code (0=Success, 1=Invalid Checksum 
 */
int ggaParser(String gga)
{
  char *tmp;
  String timeFormated = "";
  int lat;
  int lon;
  int fixQ;
  int satNum;
  byte checksum;
  int i = 0;
  tmp = strtok(gga, ",");
  while (tmp) {
     switch(i)
     {
      case 0:
        //$GGA String -> do nothing
        break;
      case 1:
        timeFormated = tmp.substr(0,2) + ":" + tmp.substr(2,4) + ":" + tmp.substr(4,6);
        break;
      case 2:
        lat = atoi(tmp);
        break;
      case 3:
        lon = atoi(tmp);
        break;
      case 4:
        fixQ = atoi(tmp);
        break;
      case 5:
        satNum = atoi(tmp);
        break;
      case 6:
        checksum = (byte)String("0x"+ tmp.substring(1,3));
        break;
     }
     tmp = strtok(NULL, ",");
     i++;
  }
}

