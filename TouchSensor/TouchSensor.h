
#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
 

#define TOUCH_KEY_PIN  3			 //PIN_04,GPIO13    
 
class TouchSensor {

public:
  TouchSensor();

  //Public Functions
  
  unsigned char ReadKey(void);
  
  //Public Variables

private:
  //Private Functions
  static unsigned char KeyCnt;
  
  //Private Variables

};
