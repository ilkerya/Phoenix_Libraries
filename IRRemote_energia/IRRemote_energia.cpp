#include "IRRemote_energia.h"

//-------------------------------------------------------
//                                        _______________
//Lead Code 4.5ms pwm + 4.5ms mute                       |________________
//                                        ____
//Bit 1 code: 0.54ms pwm + 1.68ms mute        |________
//                                        ____    
//Bit 0 code: 0.54ms pwm + 0.54ms mute        |___
//                                       
//inter mute  5ms                         |__________________|
//                                         ____    
//end code    0.54ms pwm                  |    |
//
//A Frame data = Leadcode A +~A + B +~B + C + ~C + Endcode + InterMute + Leadcode + A +~A + B +~B + C + ~C +Endcode
//
//--description of public function
//
//IRRemoteSend::Begin()														//should be initialize in setup()
//
//IRRemoteSend::StartCommand(unsigned char AcType,unsigned char Command)	//when call this in mainloop, a command would be sent.
//                                               							//For example IRSend1.StartCommand(AC_ELUX,TURN_ON); 
//IRRemoteSend::ISRPrc()		//Since timer4 has been used for counting the width of each code, this fuction should run in interrupt service route of timer4
//
//IRRemoteSend::PwmOn()			//timer1 has been used for generating 38khz pwm 
//-------------------------------------------------------

//--------------------declaration
void InitTimerForIR();
void InitTimer3BNormal();
void InitTimer3BForIR();


//--------------------------------------------------------
IRRemoteSend::IRRemoteSend()			
{	
	//-----set the physical time
	
	SendBit = 0;	 
		
	LeadCodeHighWidth = LEAD_CODE_HIGH_WIDTH;
	LeadCodeLowWidth = LEAD_CODE_LOW_WIDTH;
	
	BitCodeHighWidth = BIT_CODE_HIGH_WIDTH;
	Bit1CodeLowWidth = BIT1_CODE_LOW_WIDTH;
	Bit0CodeLowWidth = BIT0_CODE_LOW_WIDTH;
	
	EndCodeWidth = END_CODE_WIDTH;
	
	InterMuteWidth = INTER_MUTE_WIDTH;
}
//--------------------------------------------------------
void IRRemoteSend::Begin()
{
	pinMode(IR_PWM_OUT_PIN, OUTPUT);
	InitTimerForIR();
	
}
//--------------------------------------------------------
void IRRemoteSend::StartCommand(unsigned char AcType,unsigned char Command)
{	
	if (SendStatus == 0)				//only start while there is no transmitting
	{
		IRsending = 1;
		
		
		//EnableTimer4Int();
		
		MaxSendBit = SetTxData(AcType,Command);		
	
		 
		InitTimer3BForIR();				//cll,changed 2017-02-11
		MaxCount = LeadCodeHighWidth;
		
		TickCount = 0;
		
		PwmOn();	 
	 
		SendStatus = LEAD_CODE_HIGH_SENDING;
	
		SendBit = 0;
		IsSecondFrame = 0;
		//Serial.println("leadcode high");  
	}
	
}
//--------------------------------------------------------
//-A frame Data: Lead + A +~A + B +~B + C + ~C + End + InterMute + Lead + A +~A + B +~B + C + ~C +End
//--------------------------------------------------------
void IRRemoteSend::ISRPrc()
{
	unsigned char m = 0;
	unsigned char n = 0;
	unsigned char p = 0;
	
	TickCount++;
	if (TickCount >= MaxCount)
	{
		TickCount = 0;
		
		if (SendStatus == LEAD_CODE_HIGH_SENDING)
		{		
			//TCNT4 = (255 - LeadCodeLowWidth);
			MaxCount = LeadCodeLowWidth;
		
			PwmOff();
		
			SendStatus = LEAD_CODE_LOW_SENDING;
		}
		else if (SendStatus == LEAD_CODE_LOW_SENDING)
		{
			//TCNT4 = (255 - BitCodeHighWidth);
			MaxCount = BitCodeHighWidth;
		
			PwmOn();
		
			SendStatus = DATA_BIT_HIGH_SENDING;
		}
		else if (SendStatus == DATA_BIT_HIGH_SENDING)
		{
			p = (SendBit >> 3);				// div 8
			n = SendBit & 0x07;							// get reminder
				
			if ((TxBuff[p] & (0x80 >> n)) != 0)
			{			
				//--is bit1
				//TCNT4 = (255 - Bit1CodeLowWidth);
				MaxCount = Bit1CodeLowWidth;
			
			}
			else
			{
				//--is bit0
				//TCNT4 = (255 - Bit0CodeLowWidth);
				MaxCount = Bit0CodeLowWidth;
			}
		
			PwmOff();
		
			//--set the low bit 		
			SendStatus = DATA_BIT_LOW_SENDING;
		}
		else if (SendStatus == DATA_BIT_LOW_SENDING)
		{		
			SendBit++;
			if (SendBit >=  MaxSendBit)					//next is end code
			{
				SendStatus = END_CODE_SENDING;
				//TCNT4 = (255 - EndCodeWidth);
				MaxCount = EndCodeWidth;
			}
			else
			{			
				SendStatus = DATA_BIT_HIGH_SENDING;
				//TCNT4 = (255 - BitCodeHighWidth);		
				MaxCount = BitCodeHighWidth;
			}
		
			PwmOn();
		}
		else if (SendStatus == END_CODE_SENDING)
		{
			SendStatus = INTER_MUTE_SENDING;
			//TCNT4 = (255 - INTER_MUTE_WIDTH);
			MaxCount = INTER_MUTE_WIDTH;
		
			PwmOff();
		}
		else if (SendStatus == INTER_MUTE_SENDING)
		{
			if (IsSecondFrame == 0)			//command only send half
			{
				SendStatus = LEAD_CODE_HIGH_SENDING;
		
				SendBit = 0;
				IsSecondFrame = 1;
			
				//TCNT4 = (255 - LeadCodeHighWidth);
				MaxCount = LeadCodeHighWidth;
				PwmOn();
			
			}
			else							//Command end
			{
				SendStatus = 0;			
			
				PwmOff();
			
				IRsending = 0;					//sending stop
				
				InitTimer3BNormal();					//cll,changed 2017-02-11
			}
		
		}
	}
	
	
}


//--------------------------------------------------------
void IRRemoteSend::PwmOn()	//timer1 has been used for generating IR 38kHz pwm
{
	pinMode(IR_PWM_OUT_PIN, OUTPUT);
	
    TimerEnable(TIMERA3_BASE,TIMER_A);
}
//--------------------------------------------------------
void IRRemoteSend::PwmOff()
{
		
	TimerDisable(TIMERA3_BASE,TIMER_A);
	
	PwmOutput = 0;
	digitalWrite(IR_PWM_OUT_PIN, LOW);
}


//--------------------------------------------------------
unsigned char IRRemoteSend::SetTxData(unsigned char AcType,unsigned char ACCommand)
{
	unsigned Txbitcnt = 0;
	
	if (AcType == AC_ELUX)
	{
		if (ACCommand == TURN_ON)
		{
			TxBuff[0] = 0xb2;
			TxBuff[1] = ~(TxBuff[0]);
			TxBuff[2] = 0xBF;
			TxBuff[3] = ~(TxBuff[2]);	
			TxBuff[4] = 0x2C;
			TxBuff[5] = ~(TxBuff[4]);						
			
			Txbitcnt = 8 * 6;
			
		}
		else if (ACCommand == TURN_OFF)
		{
			TxBuff[0] = 0xb2;
			TxBuff[1] = ~(TxBuff[0]);
			TxBuff[2] = 0x7b;
			TxBuff[3] = ~(TxBuff[2]);	
			TxBuff[4] = 0xe0;
			TxBuff[5] = ~(TxBuff[4]);	
					
			
			Txbitcnt = 8 * 6;
		}
	}
	else
	{
		MaxSendBit = 0;
	}
	
	return(Txbitcnt);
}
//--------------------------------------------------------
void InitTimer3BNormal()
{
	/*
	TCCR4A = 0;             //disconnect pin
	TCCR4B = 0x0a;          //div = 512  1 clock = 32us
	TCCR4D = 0;             //normal mode
  
	OCR4C = 0xff;			  //8.192ms
  
	TIMSK4 = 0x04;*/
  
  TimerPrescaleSet(TIMERA3_BASE,TIMER_B,PRESCALE_100);			  //prescale is div 100
}
//--------------------------------------------------------
void InitTimer3BForIR()
{
	/*
	//TCCR4A = 0;             //disconnect pin
	TCCR4B = 0x03;          //div = 4  1 clock = 0.25us
	// TCCR4D = 0;             //normal mode
  
	OCR4C = 255;			  //64us for 1 tick 255*0.25   //tips: OCR4C should be max make sure higher than the Blue Led pwm duty value .otherwise the pwm will not generate.
  
	//TIMSK4 = 0x04;*/
  
  TimerPrescaleSet(TIMERA3_BASE,TIMER_B,PRESCALE_1);			  //prescale is div 1
}
//--------------------------------------------------------

//------------------------------------
void InitTimerForIR(void)
{    
    
      PRCMPeripheralClkEnable(PRCM_TIMERA3,PRCM_RUN_MODE_CLK);

      PRCMPeripheralReset(PRCM_TIMERA3);

      TimerConfigure(TIMERA3_BASE,TIMER_CFG_A_PERIODIC|TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_PERIODIC);            //Timer3A,Time3B both periodic

      
      //---Timer3A for generating 38Khz pwm Signal
      TimerIntRegister(TIMERA3_BASE,TIMER_A,ISR_Timer3A);

      TimerIntEnable(TIMERA3_BASE,TIMER_TIMA_MATCH);       

      TimerPrescaleSet(TIMERA3_BASE,TIMER_A,PRESCALE_1);

      TimerMatchSet(TIMERA3_BASE,TIMER_A,1);

      TimerLoadSet(TIMERA3_BASE,TIMER_A,TIME3A_COUNTER_FOR_PWM);  

      TimerDisable(TIMERA3_BASE,TIMER_A);							//Init disable

	  
      //timer3B for counting the high or low output time for each bit of the sending bytes.
      TimerIntRegister(TIMERA3_BASE,TIMER_B,ISR_Timer3B);

      TimerIntEnable(TIMERA3_BASE,TIMER_TIMB_MATCH);      	 

      TimerPrescaleSet(TIMERA3_BASE,TIMER_B,PRESCALE_100);    		//Init prescale is div 100 for 6.4ms, when IR pwm on,it must change to div 1

      TimerMatchSet(TIMERA3_BASE,TIMER_B,1);

      TimerLoadSet(TIMERA3_BASE,TIMER_B,TIME3B_COUNTER);          	//Init Timer3B is 6.4ms

      TimerEnable(TIMERA3_BASE,TIMER_B);
  
}
//-------------------timer interrupt for generating 38Khz pwm 
void ISR_Timer3A(void)
{      
	  //static unsigned char PwmOutput;          //1 high output,0 low output
	  
	  //----for debug
      if (IRSend1.PwmOutput == 0)
      {
           IRSend1.PwmOutput = 1;
           digitalWrite(IR_PWM_OUT_PIN, LOW);
      }
      else
      {
           IRSend1.PwmOutput = 0;
           digitalWrite(IR_PWM_OUT_PIN, HIGH);        
      }           
      
	  //----
	   
	  
	  
	  
      // Clear the timer interrupt.
      MAP_TimerIntClear(TIMERA3_BASE, TIMER_TIMA_MATCH);
      
      MAP_TimerLoadSet(TIMERA3_BASE, TIMER_A, TIME3A_COUNTER_FOR_PWM);             // 38khz, high level 13us,low level 13us, 65535 = 0.819ms then 1040 = 13us
}
