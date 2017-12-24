#ifndef	RGB_DRIVING_H
#define	RGB_DRIVING_H

#include <Arduino.h>


#define	RED_PIN			31				//chenll,changed,CC3200 GPIO24,pin17
#define GREEN_PIN		29				//chenll,changed,CC3200 GPIO25,pin21
#define BLUE_PIN 		13				//chenll,changed,CC3200 GPIO09,pin64

#define COLOR_1			0
#define COLOR_2			1
#define COLOR_3			2
#define COLOR_4			3
#define COLOR_5			4
#define COLOR_6			5
#define COLOR_7			6
#define COLOR_8			7
#define COLOR_9			8
#define COLOR_10		9
#define COLOR_11		10
/*
#define WHITE   0
#define RED   1
#define GREEN 2
#define BLUE  3
#define YELLOW 4
//#define  5
#define AQUA 6
//#define  7
#define PURPLE 8
//#define  9

*/
#define NOCOLOR  0x000000

// http://www.rapidtables.com/web/color/RGB_Color.htm
			// red/green/blue
			//   FF/FF/FF
   #define AQUA 0x00ffff
   #define AZURE 0xf0ffff
   #define BEIGE 0xf5f5dc
   #define BLACK 0x000000
   #define BLUE 0x0000ff
   #define BROWN 0xa52a2a
   #define CYAN 0x00ffff
   #define DARKBLUE 0x00008b
   #define DARKCYAN 0x008b8b
   #define DARKGREY 0xa9a9a9
   #define DARKGREEN 0x006400
   #define DARKKHAKI 0xbdb76b
   #define DARKMAGENTA 0x8b008b
   #define DARKOLIVEGREEN 0x556b2f
   #define DARKORANGE 0xff8c00
   #define DARKORCHID 0x9932cc
   #define DARKRED 0x8b0000
   #define DARKSALMON 0xe9967a
   #define DARKVIOLET 0x9400d3
   #define FUCHSIA 0xff00ff
   #define GOLD 0xffd700
   #define GREEN 0x008000
   #define KHAKI 0xf0e68c
   #define LIGHTBLUE 0xadd8e6
   #define LIGHTCYAN 0xe0ffff
   #define LIGHTGREEN 0x90ee90
   #define LIGHTGREY 0xd3d3d3
   #define LIGHTPINK 0xffb6c1
   #define LIGHTYELLOW 0xffffe0
   #define LIME 0x00ff00
   #define MAGENTA 0xff00ff
   #define MAROON 0x800000
   #define NAVY 0x000080
   #define OLIVE 0x808000
   #define ORANGE 0xffa500
   #define PINK 0xffc0cb
   #define PURPLE 0x800080
   #define VIOLET 0x800080
   #define RED 0xff0000
   #define SILVER 0xc0c0c0
   #define WHITE 0xffffff
 //  #define YELLOW 0xffff00
   #define YELLOW 0xf0f000
class RGBDrv
{
public:
	RGBDrv();

	void DispColor(unsigned char ColorNum);





private:
	unsigned char PinR;
	unsigned char PinG;
	unsigned char PinB;

};






 #endif

