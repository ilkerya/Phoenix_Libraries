#include <Arduino.h>
#include "RGBDriving.h"

//--------------------------------------------------------
//R,G,B driving pin has been defined to pin11,pin5,pin6
//
//There are about 10 defined color, in mainloop call RGBDrv::DispColor(unsigned char ColorNum) can change to the defined color.
//                                        //for example,RGBLed1.DispColor(COLOR_1)
//color could be change by changing the pwm value of each driving pin.
//--------------------------------------------------------
//--------------------------------------------------------
RGBDrv::RGBDrv()
{
	PinR = RED_PIN;
	PinG = GREEN_PIN;
	PinB = BLUE_PIN;

	pinMode(PinR, OUTPUT);
	pinMode(PinG, OUTPUT);
	pinMode(PinB, OUTPUT);
}

//--------------------------------------------------------
void RGBFade(unsigned char ColorNum)
{

	unsigned char ValueR = 0;
	unsigned char ValueG = 0;
	unsigned char ValueB = 0;

	if (ColorNum == WHITE)
	{
		ValueR = 80;
		ValueG = 125;
		ValueB = 125;
	}
	else if (ColorNum == RED)
	{
		ValueR = 255; // red
		ValueG = 0;
		ValueB = 0;
	}
	else if (ColorNum == GREEN)
	{
		ValueR = 0;
		ValueG = 255; //green
		ValueB = 0;
	}
	else if (ColorNum == BLUE)
	{
		ValueR = 0;
		ValueG = 0;
		ValueB = 255;  //blue
	}
	else if (ColorNum == YELLOW)
	{
		ValueR = 125;
		ValueG = 125;
		ValueB = 0;
	}
	else if (ColorNum == 5) // PURPLE
	{
		ValueR = 125;
		ValueG = 0;
		ValueB = 125;
	}
	else if (ColorNum == AQUA)
	{
		ValueR = 0;
		ValueG = 125;
		ValueB = 55;
	}
	else if (ColorNum == 7)
	{
		ValueR = 0;
		ValueG = 80;
		ValueB = 80;
	}
	else if (ColorNum == PURPLE)
	{
		ValueR = 80;
		ValueG = 0;
		ValueB = 80;
	}
	else if (ColorNum == 9) // YELLOW
	{
		ValueR = 80;
		ValueG = 80;
		ValueB = 0;
	}
	else
	{
		ValueR = 0;
		ValueG = 0;
		ValueB = 0;
	}
/*
	analogWrite(PinG,ValueG);
	analogWrite(PinR,ValueR);
	analogWrite(PinB,ValueB);
	*/
}

//--------------------------------------------------------
void RGBDrv::DispColor(unsigned char ColorNum)
{

	unsigned char ValueR = 0;
	unsigned char ValueG = 0;
	unsigned char ValueB = 0;

	if (ColorNum == WHITE)
	{
		ValueR = 125;
		ValueG = 125;
		ValueB = 125;
	}
	else if (ColorNum == RED)
	{
		ValueR = 255; // red
		ValueG = 0;
		ValueB = 0;
	}
	else if (ColorNum == GREEN)
	{
		ValueR = 0;
		ValueG = 255; //green
		ValueB = 0;
	}
	else if (ColorNum == BLUE)
	{
		ValueR = 0;
		ValueG = 0;
		ValueB = 255;  //blue
	}
	else if (ColorNum == YELLOW)
	{
		ValueR = 125;
		ValueG = 125;
		ValueB = 0;
	}
	else if (ColorNum == 5) // PURPLE
	{
		ValueR = 125;
		ValueG = 0;
		ValueB = 125;
	}
	else if (ColorNum == AQUA)
	{
		ValueR = 0;
		ValueG = 125;
		ValueB = 55;
	}
	else if (ColorNum == 7)
	{
		ValueR = 0;
		ValueG = 80;
		ValueB = 80;
	}
	else if (ColorNum == PURPLE)
	{
		ValueR = 80;
		ValueG = 0;
		ValueB = 80;
	}
	else if (ColorNum == 9) // YELLOW
	{
		ValueR = 80;
		ValueG = 80;
		ValueB = 0;
	}
	else
	{
		ValueR = 0;
		ValueG = 0;
		ValueB = 0;
	}

	analogWrite(PinG,ValueG);
	analogWrite(PinR,ValueR);
	analogWrite(PinB,ValueB);
}
//--------------------------------------------------------

//--------------------------------------------------------

