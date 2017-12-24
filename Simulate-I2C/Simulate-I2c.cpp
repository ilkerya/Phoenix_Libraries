#include "Simulate-I2c.h"
#include "Energia.h"

#define		I2C_SDA_INPUT()			digitalRead(IO_SDA)
#define		I2C_SCL_INPUT()			digitalRead(IO_SCL)

#define		SetSdaOutput()			pinMode(IO_SDA,OUTPUT)
#define		SetSdaInput()			pinMode(IO_SDA,INPUT)

#define		SetSclOutput()			pinMode(IO_SCL,OUTPUT)
#define		SetSclInput()			pinMode(IO_SCL,INPUT)

#define		SetSDAHigh()			digitalWrite(IO_SDA,HIGH)
#define		SetSDALow()				digitalWrite(IO_SDA,LOW)

#define		SetSCLKHigh()			digitalWrite(IO_SCL,HIGH)
#define		SetSCLKLow()			digitalWrite(IO_SCL,LOW)


#define		I2C_DELAY()				delayMicroseconds(5)				//delay(1)   
#define		I2C_DELAY_LONG()		delayMicroseconds(5000)				//delay(10)		

#define		AT24C02_WR_COMMAND		(0xa5)		 
#define		AT24C02_RD_COMMAND		(0Xa1)		 

#define		FEED_DOG()			



//------------------------------ 
 

 

/*--------------------function declaration-------------------------------*/
SimulateIic::SimulateIic()
{
	
}


//------------------------------------------------------------------------
void SimulateIic::begin(void)
{
	 
}
/**************************************************************************
*    Prototype:static void I2cStart(void)
*    Function: I2C start
**************************************************************************/
void SimulateIic::I2cStart(void)
{
	SetSclOutput();		//add
	SetSdaOutput();
	I2C_DELAY();	
	SetSDAHigh();	
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSDALow();
	I2C_DELAY();
	SetSCLKLow();	
	I2C_DELAY();
}
/**************************************************************************
*    Prototype:void I2cStop(void)
*    Function:  
**************************************************************************/
void SimulateIic::I2cStop(void)
{
	SetSdaOutput();
	I2C_DELAY();	
	SetSDALow();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSDAHigh();
	I2C_DELAY();
}
/**************************************************************************
*    Prototype:static void SendAck(void)
*    Function: 
**************************************************************************/
void SimulateIic::SendAck(void)
{
	SetSdaOutput();;
	I2C_DELAY();
	SetSDALow();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSCLKLow();
	I2C_DELAY();
}
/**************************************************************************
*    Prototype:static void SendNoAck(void)
*    Function: 
**************************************************************************/
void SimulateIic::SendNoAck(void)
{
	SetSdaOutput();
	I2C_DELAY();
	SetSDAHigh();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSCLKLow();
	I2C_DELAY();
}
/**************************************************************************
*    Prototype:static void CheckAck(void)
*    Function: 
**************************************************************************/
void SimulateIic::CheckAck(void)
{
	unsigned char i = 0;
	SetSCLKLow();
	SetSDAHigh();
	SetSdaInput();
	I2C_DELAY();
	
	SetSCLKHigh();
	while((I2C_SDA_INPUT()) && (i < 20))			/*Á¬Ðø¶ÁÈ¡*/
	{
		i++;
	}
	
	SetSCLKLow();
	I2C_DELAY();	
}
/**************************************************************************
*    Prototype:static void I2cWrite(unsigned char WriteData)
*    Function:
**************************************************************************/
void SimulateIic::I2cWrite(unsigned char WriteByte)
{
	unsigned char i;	 
	
	SetSdaOutput();
	I2C_DELAY();
	
	for(i = 0;i < 8;i++)
	{
		SetSCLKLow();
		if((WriteByte & 0x80) != 0)
		{
			SetSDAHigh();
		}
		else 
		{
			SetSDALow();	
		}
					
		WriteByte <<= 1;
		
		SetSCLKHigh();
		I2C_DELAY();
		SetSCLKLow();
		I2C_DELAY();		
	}	
}
/**************************************************************************
*    Prototype:static unsigned char SimIic::I2cRead(void)
*    Function:Read 1 byte
**************************************************************************/
unsigned char SimulateIic::I2cRead(void)
{
	unsigned char i;
	unsigned char ReadByte = 0;
	
	unsigned int timeout = 0;
	
	SetSCLKLow();
	
	SetSdaInput();	
//---for reading IAQ-CORE, when IAQ-CORE is processing, it would make the scl bus low, so we have to check SCL until it became high.	
#ifdef	EN_SCL_INPUT
	SetSclInput();	
	
	while(I2C_SCL_INPUT()==0)
	{
		delayMicroseconds(1);
		timeout++;
		if(timeout > 1000)		//wait a max time
		{
			SetSclOutput();
			return 0;
		}
	}
	
	SetSclOutput();			
#endif	
	
	I2C_DELAY();
	for(i = 0;i < 8;i++)
	{
		I2C_DELAY();
		
		SetSCLKHigh();
		I2C_DELAY();
				
		ReadByte <<= 1;
		
		if (I2C_SDA_INPUT())
		{
			ReadByte |= 0x01;
		}
		
		
		SetSCLKLow();		
    }
	
	return(ReadByte);
}
 
/**************************************************************************
*    Prototype:void SimIic::I2cReadIAQNByte(unsigned int DeviceAddress,unsigned char *ReadData,unsigned char ReadByteNumber)
*    Function:ReadNbyte
**************************************************************************/
void SimulateIic::I2cReadIAQNByte(unsigned int DeviceAddress,unsigned char *ReadData,unsigned char ReadByteNumber)
{
	unsigned char i = 0;
	unsigned char LastByteCount = 0;
	
	I2cStart();
	
	I2cWrite(DeviceAddress);
	CheckAck();	

	
	//I2C_DELAY_LONG();
	LastByteCount = (unsigned char)(ReadByteNumber - 1);
	for(i = 0;i < ReadByteNumber;i++)
	{		
		*ReadData = I2cRead();
		if(i == LastByteCount)
		{
			SendNoAck();		/* NOACK*/
		}
		else	
		{
			SendAck();
		}
		ReadData++;
		I2C_DELAY();			
	}		
	I2C_DELAY();				
	I2cStop();
	I2C_DELAY_LONG();
}

/**************************************************************************/
SimulateIic Newiic1;











