#include "Inova.h"

INOVA::INOVA(unsigned long module):InovaPort(module) 					//chenll,change from INOVA::INOVA(int rx, int tx):InovaPort(rx, tx).  
{
	 
}

INOVA::~INOVA() {}

bool INOVA::begin(void)
{
    InovaPort.begin(9600);
}
void INOVA::listen(void)
{
    //InovaPort.listen();					//chenll,del
}
bool INOVA::isListening(void)
{
    //InovaPort.isListening();				//chenll,del
}


void INOVA::readPMconc(void) {
  j=0;
  i=0;


  for (i=0; i<10; i++)
  {
    data[i]=0;
  }
  start[0]=0;
  i=0;
  while (InovaPort.available()<=0 && i<1000)
  {
      delay(1);
      i++;
  }
  if (InovaPort.available())
  {
    InovaPort.readBytes(start,1);
    while (start[0]!=0xAA)
    {
      InovaPort.readBytes(start,1);
      delay(1);
    }
    InovaPort.readBytes(data,9);
    checksum=(int)data[1]+(int)data[2]+(int)data[3]+(int)data[4]+(int)data[5]+(int)data[6];
    MeasurementCount++;
  }

  if (checksum==(int)data[7])
  {
//	PM25=(((double)data[2])*256+(double)data[1])/10;
//    PM10=(((double)data[4])*256+(double)data[3])/10;
	PM25=(((float)data[2])*256+(float)data[1])/10;
    PM10=(((float)data[4])*256+(float)data[3])/10;
  }
  else
  {
		WrongCheckSum++;
  }

  	#ifdef DEBUG
 		Serial.print("PM :");
 		Serial.print(start[0],HEX);Serial.print(".");
  		Serial.print(data[0],HEX);Serial.print(".");Serial.print(data[1],HEX);Serial.print(".");
  		Serial.print(data[2],HEX);Serial.print(".");Serial.print(data[3],HEX);Serial.print(".");
  		Serial.print(data[4],HEX);Serial.print(".");Serial.print(data[5],HEX);Serial.print(".");
  		Serial.print(data[6],HEX);Serial.print(".");Serial.print(data[7],HEX);Serial.print(".");
  		Serial.print(data[8],HEX);Serial.print(".");Serial.print("//");
  		Serial.print(checksum,HEX);
  		if(checksum == data[7])Serial.print("==");
  		else Serial.print("xx");
  		Serial.print(data[7],HEX);Serial.print("//");
  		Serial.print(MeasurementCount);Serial.print(".");Serial.println(WrongCheckSum);


	#endif
	//return(PM25);
}
/*
double INOVA::readPM10conc(void) {
  j=0;
  i=0;


  for (i=0; i<10; i++)
  {
    data[i]=0;
  }
  start[0]=0;
  i=0;
  while (InovaPort.available()<=0 && i<1000)
  {
      delay(1);
      i++;
  }
  if (InovaPort.available())
  {
    InovaPort.readBytes(start,1);
    while (start[0]!=0xAA)
    {
      InovaPort.readBytes(start,1);
      delay(1);

    }

    InovaPort.readBytes(data,9);
    checksum=(int)data[1]+(int)data[2]+(int)data[3]+(int)data[4]-29;
    //PM25=(((double)data[2])*256+(double)data[1])/10;
    PM10=(((double)data[4])*256+(double)data[3])/10;
    //PM[0]=PM25;
    //PM[1]=PM10;
  }
  if (checksum==(int)data[7])
  {

  }
  else
  {
      PM10=99.0;
      //PM[0]=99.0;
      //PM[1]=99.0;
  }
	return(PM10);
}

*/