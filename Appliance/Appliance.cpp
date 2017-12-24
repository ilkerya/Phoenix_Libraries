#include "Appliance.h"
#include "HardwareSerial.h"


//-----------------------------------------------------
UartPrc::UartPrc()
{
	
}

//-----------------------------------------------------
void UartPrc::SendData(unsigned char *TxBuff,unsigned char TxNumber)
{
	unsigned char i = 0;
	unsigned char Temp = 0;
	
	
	//----cal checksum
	
	
	for (i = 0; i < TxNumber; i++)
	{		
		
		Serial1.write(*TxBuff);
				
		//------------for debugging,to show the data on terminate.		
		Temp = (*TxBuff & 0xf0);
		Temp >>= 4;
		if (Temp < 10)
		{
			Temp += 48;
		}
		else
		{
			Temp += 55;
		}
		Serial.write(Temp);
		
		Temp = (*TxBuff & 0x0f);
		if (Temp < 10)
		{
			Temp += 48;
		}
		else
		{
			Temp += 55;
		}
		Serial.write(Temp);		
		//--------------
		
		TxBuff++;
	}
	
	Serial.println();						//fordebug
}

//-----------------------------------------------------a general command to get devices status (every appliance will answer)
//--example:
//--Uart1.SetCmd(GET_APPLIANCE_STATUS);
//--
//-----------------------------------------------------
void UartPrc::SetCmd(unsigned char CmdType)				//this command is to get the general information of appliance. suitable to all appliance
{	
	CmdBuff[0] = 0xf5;
	CmdBuff[1] = 0xFF;
	CmdBuff[2] = 0x02;
	CmdBuff[3] = 0xF2;
	
	TxLength = CmdBuff[2] + 4;
	
	CmdBuff[TxLength - 2] = CheckSum();
    
	CmdBuff[TxLength - 1] = 0xFA;               		//set end code
	
	SendData(&CmdBuff[0],TxLength);
}
//----------------------------------------------------- get each appliance running information
//--for example
//--Uart1.SetCmd(GET_APPLIANCE_RUN_INF,DEV_HUMIDIFIER)			//get humidifier running information
//--Uart1.SetCmd(GET_APPLIANCE_RUN_INF,DEV_PURIFIER)			//get purifier running information
//--
//------------------------------------------------------
void UartPrc::SetCmd(unsigned char CmdType,unsigned char ApplianceName)
{
	if (ApplianceName == DEV_HUMIDIFIER)
	{		
		CmdBuff[0] = 0xf5;
		CmdBuff[1] = 0xFF;
		CmdBuff[2] = 0x02;
		CmdBuff[3] = 0xF1;
	}
	else if (ApplianceName == DEV_PURIFIER)
	{
		CmdBuff[0] = 0xf5;
		CmdBuff[1] = 0xFF;
		CmdBuff[2] = 0x02;
		CmdBuff[3] = 0xF1;
	}
	else if (ApplianceName == DEV_AC)
	{
		CmdBuff[0] = 0xf5;
		CmdBuff[1] = 0x55;
		CmdBuff[2] = 0x02;
		CmdBuff[3] = 0xF1;
	}
	else				//default
	{
		CmdBuff[0] = 0xf5;
		CmdBuff[1] = 0xFF;
		CmdBuff[2] = 0x02;
		CmdBuff[3] = 0xF1;
	}
	
	TxLength = CmdBuff[2] + 4;
	
	CmdBuff[TxLength - 2] = CheckSum();
    
	CmdBuff[TxLength - 1] = 0xFA;               		//set end code
	
	SendData(&CmdBuff[0],TxLength);
}
//-----------------------------------------------------
//--example:
//--Uart1.SetHumidifer(HUM_ONOFF_SETTING,HUM_ON);
//--Uart1.SetHumidifer(HUM_FAN_SETTING,HUM_LOW);				//Fan can be set only when Purifier is on
//--
//-----------------------------------------------------
void UartPrc::SetHumidifer(unsigned char SettingType,unsigned char SettingData)
{
	unsigned char CmdType = 0;				//A2 for mode; A4 for fan speed; 
	
	unsigned char Data = 0;		

	if (SettingType == HUM_ONOFF_SETTING)
	{
		CmdType = 0xA2;
		
		if (SettingData == 0)				//mode
		{
			Data = 0;
		}
		else
		{
			Data = 1;
		}
		
	}
	else if (SettingType == HUM_FAN_SETTING)
	{
		CmdType = 0xA4;
		
		if (SettingData <= 3)				//fan level
		{
			Data = SettingData;							 
		}
		else
		{
			Data = PUR_HIGH;
		}
	}
	else
	{
			// other setting is  mode off
			CmdType = 0xA2;
		
			Data = 0;
			
	}
	
	
	CmdBuff[0] = 0xf5;
	CmdBuff[1] = CMD_ID_HUMIDIFIER;
	CmdBuff[2] = 0x03;
	CmdBuff[3] = CmdType;
	CmdBuff[4] = Data;
	
	TxLength = CmdBuff[2] + 4;
	
	CmdBuff[TxLength - 2] = CheckSum();
    
	CmdBuff[TxLength - 1] = 0xFA;               		//set end code
	
	SendData(&CmdBuff[0],TxLength);
}
//-----------------------------------------------------
//--example:
//--Uart1.SetPurifier(PUR_ONOFF_SETTING,PUR_ON);
//--Uart1.SetPurifier(PUR_FAN_SETTING,PUR_LOW);				//Fan can be set only when Purifier is on
//--Uart1.SetPurifier(PUR_ION_SETTING,PUR_ION_OFF);			//ION can be set only when Purifier is on
//--
//-----------------------------------------------------
void UartPrc::SetPurifier(unsigned char SettingType,unsigned char SettingData)
{	
	unsigned char CmdType = 0;			//A2 for mode; A4 for fan speed; A5 for ION  
	
	unsigned char Data = 0;			 
	 
	
	if (SettingType == PUR_ONOFF_SETTING)
	{
		CmdType = 0xA2;
		
		if (SettingData == 0)				//mode
		{
			Data = 0;
		}
		else
		{
			Data = 1;
		}
		
	}
	else if (SettingType == PUR_FAN_SETTING)
	{
		CmdType = 0xA4;
		
		if (SettingData <= 3)				//fan level
		{
			Data = SettingData;							 
		}
		else
		{
			Data = PUR_HIGH;
		}
	}
	else if (SettingType == PUR_ION_SETTING)
	{
		CmdType = 0xA5;
		
		if (SettingData == 0)				//ion on or off
		{
			Data = 0;
		}
		else
		{
			Data = 1;
		}						
		
	}	
	else
	{
			// other setting is  mode off
			CmdType = 0xA2;
		
			Data = 0;
			
	}
	
	
	CmdBuff[0] = 0xf5;
	CmdBuff[1] = CMD_ID_PURIFIER;
	CmdBuff[2] = 0x03;
	CmdBuff[3] = CmdType;
	CmdBuff[4] = Data;
	
	TxLength = CmdBuff[2] + 4;
	
	CmdBuff[TxLength - 2] = CheckSum();
    
	CmdBuff[TxLength - 1] = 0xFA;               		//set end code
	
	SendData(&CmdBuff[0],TxLength);
}
//-----------------------------------------------------
//--example:
//--Uart1.SetAC(AC_ONOFF_SETTING,AC_OFF)
//--Uart1.SetAC(AC_MODE_SETTING,AC_COOL)
//--Uart1.SetAC(AC_TEMP_SETTING,20)					//set 20 celesuis
//--Uart1.SetAC(AC_TEMP_SETTING,95)					//set 95 Fahrenheit
//--Uart1.SetAC(AC_FAN_SETTING,AC_FAN_LOW)		
//--
//-----------------------------------------------------
void UartPrc::SetAC(unsigned char SettingType,unsigned char SettingData)
{
	unsigned char CmdType = 0;			//A0 Swing,A2 for mode;A3 temperature; A4 for fan speed;A5 airclean;A6 sleep
	
	unsigned char Data = 0;		
	
	if (SettingType == AC_ONOFF_SETTING)
	{
		CmdType = 0xA2;
		
		if (SettingData == AC_OFF)
		{
			Data = 0x00;
		}
		else  
		{
			Data = 0x05;
		}
	}	
	if (SettingType == AC_MODE_SETTING)
	{
		CmdType = 0xA2;
		
		if (SettingData == AC_OFF)
		{
			Data = 0x00;
		}
		else if (SettingData == AC_COOL)
		{
			Data = 0x01;
		}
		else if (SettingData == AC_HEAT)
		{
			Data = 0x02;
		}		
		else if (SettingData == AC_DEHUM)
		{
			Data = 0x06;
		}
		else if (SettingData == AC_AUTO)
		{
			Data = 0x07;
		}
		else
		{
			Data = 0x00;				//other setting
		}
	}
	else if (SettingType == AC_TEMP_SETTING)
	{
		CmdType = 0xA3;
		
		//---Celsius or Fahrenheit
		if (SettingData <= 32)			//usually Celsius temp will below 33,so if temperature higher than 32 it should be Fahrenheit 
		{
			Data |= 0x80;
			
			Data |= SettingData;
		}
		else
		{
			Data = 0;
			
			if (SettingData > 127)
			{
				SettingData = 127;
			}
			
			Data |= SettingData;
		}
		
	}
	else if (SettingType == AC_FAN_SETTING)
	{
		CmdType = 0xA4;
		
		if (SettingData == 0)
		{
			SettingData = AC_FAN_LOW;				// AC FAN would not be off
		}
		else if (SettingData == 1)
		{
			SettingData = AC_FAN_LOW;
		}
		else if (SettingData == 2)
		{
			SettingData = AC_FAN_MID;
		}
		else if (SettingData == 3)
		{
			SettingData = AC_FAN_HIGH;
		}
		else
		{
			SettingData = AC_FAN_LOW;				//others set to low
		}
		Data = SettingData;
	}
	else
	{
		//future use
	}
	
	CmdBuff[0] = 0xf5;
	CmdBuff[1] = CMD_ID_AC;
	CmdBuff[2] = 0x03;
	CmdBuff[3] = CmdType;
	CmdBuff[4] = Data;
	
	TxLength = CmdBuff[2] + 4;
	
	CmdBuff[TxLength - 2] = CheckSum();
    
	CmdBuff[TxLength - 1] = 0xFA;               		//set end code
	
	SendData(&CmdBuff[0],TxLength);
}
//-----------------------------------------------------
unsigned char UartPrc::CheckSum()	
{
	unsigned char i = 0;
	unsigned char Sum = 0;
	
	Sum = 0;                  		
	
	for (i = 0; i< (TxLength - 2); i++)
	{
		Sum += CmdBuff[i];
	}
	
	return(Sum);
}
//-----------------------------------------------------
//--for reading a ack command frame from the appliance 
//-----------------------------------------------------
void UartPrc::ReadData()
{
	unsigned char i = 0;
    unsigned char j = 0;
    unsigned char CheckSum = 0;

    unsigned char Buf = 0;
	unsigned char Temp = 0;

    
	//----read the answer   
	Serial.print("Receive:");				//fordebug    
	if (Serial1.available())
	{		 
        while (Buf != 0xFA)
        {
            Buf = Serial1.read();
            //Serial.println(Buf);			//fordebug			

            ReadBuff[i] = Buf;
			
			//------------for debugging,to show the data on terminate.		
			Temp = (Buf & 0xf0);
			Temp >>= 4;
			if (Temp < 10)
			{
				Temp += 48;
			}
			else
			{
				Temp += 55;
			}
			Serial.write(Temp);
		
			Temp = (Buf & 0x0f);
			if (Temp < 10)
			{
				Temp += 48;
			}
			else
			{
				Temp += 55;
			}
			Serial.write(Temp);		
		//--------------
			
            j = i;
            i++;

            if (i >= 100)
            {
                break;
            }
        }
		
		
         //-----count checksum
         for (i = 0; i <= j - 2; i++)
         {
             CheckSum += ReadBuff[i];
         }
          
         if (CheckSum == ReadBuff[j - 1])
         {
              RxOk = 1;
			  
              Serial.print("rxok-");
		 }    
		 
		 
	}
	
}
//-----------------------------------------------------
//--when first power on, check which appliance is connected
//-----------------------------------------------------
unsigned char UartPrc::GetOnlineAppliance()
{
	unsigned char i = 0;
	
	if (RxOk == 1)
    {
        RxOk = 0;
		
		//----save device type, only once
		if (OnlineAppliance == 0)
		{
			OnlineAppliance = ReadBuff[1];         
		}
		
		//----
        for (i = 0; i < 30;i++)    
        {
            ReadBuff[i] = 0;
        }
	}
	
	return(OnlineAppliance);
}
//-----------------------------------------------------
//--After send a command to check the appliance's running information, the appliance feedback it's running inf, then cc3200 decode the ack data.
//-----------------------------------------------------
void UartPrc::DecodeApplianceInf()
{
	unsigned char i = 0;
	
	if (RxOk == 1)
    {
        RxOk = 0;

                 
        //----
        if ((OnlineAppliance == CMD_ID_HUMIDIFIER) && (CmdBuff[3] == 0xf1))		
        {            
            Serial.println("got humidifier inf");
            //GetHumidifierStatus();            
        }    
        else if ((OnlineAppliance == CMD_ID_PURIFIER))
        { 
            Serial.println("got Purifier inf");
            //GetPurifierStatus();
        }
        else if ((OnlineAppliance == CMD_ID_AC) && (CmdBuff[3] == 0xf1))
        {
            Serial.println("got AC inf");
            //GetACStatus();
        }
        else
        {
            //do nothing
        }

        //----clear receiving buff
        for (i = 0; i < 30;i++)    
        {
            ReadBuff[i] = 0;
        }
    }
}
//-----------------------------------------------------
void UartPrc::GetAck()
{
	if (RxOk == 1)
    {
        RxOk = 0;
		Serial.println();				//fordebug
		
	}
}
