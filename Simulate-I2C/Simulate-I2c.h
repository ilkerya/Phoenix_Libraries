#ifndef	IIC_H
#define	IIC_H



#define		IO_SCL		9				//GPIO 10 note:digitalWrite(num),num != GPIO_num
#define		IO_SDA		10     			//GPIO 11

 
#define		EN_SCL_INPUT				//for reading IAQ-CORE


 


class SimulateIic{

public:
	SimulateIic();
	void begin(void);
	void I2cReadIAQNByte(unsigned int DeviceAddress,unsigned char *ReadData,unsigned char ReadByteNumber); 
	 
	
	
	
private:

	void CheckAck(void);
	void I2cWrite(unsigned char WriteByte);
	unsigned char I2cRead(void);
	void Delayms(unsigned char Time);
	void I2cStart(void);
	void I2cStop(void);
	void SendAck(void);
	void SendNoAck(void);

};

//------------------------------
extern SimulateIic Newiic1;

 

#endif
