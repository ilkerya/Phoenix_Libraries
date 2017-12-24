#ifndef		APPLIANCE_H
#define		APPLIANCE_H



#define		MAX_CMD_LENGTH			10

#define		GET_APPLIANCE_STATUS	0
#define		GET_APPLIANCE_RUN_INF	1
#define		SET_APPLIANCE_RUN		2


#define		CMD_ID_HUMIDIFIER			0x59			//command ID
#define     CMD_ID_PURIFIER				0x58
#define     CMD_ID_AC					0x55

#define		DEV_HUMIDIFIER			CMD_ID_HUMIDIFIER
#define		DEV_PURIFIER			CMD_ID_PURIFIER
#define		DEV_AC					CMD_ID_AC

//------------------------------
#define		AC_ONOFF_SETTING		0
#define		AC_MODE_SETTING			1
#define		AC_TEMP_SETTING			2
#define		AC_FAN_SETTING			3

//----AC ONOFF
#define 	AC_OFF 			0
#define 	AC_ON 			1

//----AC MODE
//#define 	AC_OFF 			0
#define 	AC_COOL 		1
#define 	AC_HEAT 		2
#define 	AC_DEHUM 		3
#define 	AC_AUTO 		4  			// FUTURE USE

//----AC  FAN

#define 	AC_FAN_LOW 		0
#define 	AC_FAN_MID 		2
#define 	AC_FAN_HIGH		4

//------------------------------
#define		HUM_ONOFF_SETTING		0
#define		HUM_FAN_SETTING			1

//--HUM MODE
#define 	HUM_OFF 		0
#define 	HUM_ON 			1

//--HUM FAN
#define 	HUM_LOW 		1
#define 	HUM_MID 		2
#define 	HUM_HIGH 		3

//------------------------------purifier setting, Mode, Fan, Ion
#define		PUR_ONOFF_SETTING	0
#define		PUR_FAN_SETTING		1
#define		PUR_ION_SETTING		2

//-- PUR MODE
#define 	PUR_OFF 		0
#define 	PUR_ON 			1

//-- PUR FAN
#define 	PUR_LOW 		1
#define 	PUR_MID 		2
#define 	PUR_HIGH 		3

//--PUR ION
#define 	PUR_ION_OFF		0
#define 	PUR_ION_ON		1

//------------------------------
#define 	ROBOT_OFF 		0
#define 	ROBOT_ON 		1





class UartPrc
{ public:



	//---------------------------
	UartPrc();
	
	//--------------------------function overloading
	void SetCmd(unsigned char CmdType);
	void SetCmd(unsigned char CmdType,unsigned char ApplianceName);
	
	void SetHumidifer(unsigned char SettingType,unsigned char SettingData);
	void SetPurifier(unsigned char SettingType,unsigned char SettingData);
	void SetAC(unsigned char SettingType,unsigned char SettingData);
    
	void ReadData();
	unsigned char GetOnlineAppliance();				//read the appliance id
	void GetAck();									//Read the ack frame
	void DecodeApplianceInf();						
	
	
	
	unsigned char ReadBuff[30];
	
  private:
	unsigned char OnlineAppliance;
    unsigned char CmdBuff[MAX_CMD_LENGTH];
	unsigned char TxLength;
	unsigned char RxOk;
	
	//---------------------------
	void SendData(unsigned char *TxBuff,unsigned char TxNumber);
	unsigned char CheckSum();
	
  
};


#endif
