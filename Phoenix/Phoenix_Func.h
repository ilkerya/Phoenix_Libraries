
//#define DEBUG_IAQ

//#include <SoftwareSerial.h>				//chenll,del


String Float2String(float Val){
	  int temp= (int)(Val * 10);
    int Decimal =abs(temp);
    Decimal %= 10;
    return(String((int)Val) + '.' + String(Decimal));
  }
/*
    String Float2StringNoDecimal(float Val){
  	  int temp= (int)Val;
      int Decimal =abs(temp);
      Decimal %= 10;
      return(String((int)Val) + '.' + String(Decimal));
  }
*/
void PrintCharArray(char *p, int n){
  for (int i=0; i< n ; i++){
  		Serial.print(p[i]);// to console
	}
}

bool TimeoutFunc(int Val) {
     if(!Timer.TimoeutStart){
        Timer.TimoeutStart = 1;
        Timer.TimoeutFollower = Val;
     }
      else Timer.TimoeutFollower--;
      if(!Timer.TimoeutFollower){
        Serial.println("Timeout: " + String(Val,DEC)+ "mSec");
          Timer.TimoeutStart = 0;
          return 1;
      }
      else return 0;
}


float FloatGetAverage(float *p,unsigned char Length){
	int i;
	float f=0;
	for (i=3; i<=(Length-3);i++){
		f += p[i];
	}
	return f/(Length-5);
}

unsigned int UintGetAverage(unsigned int *p,unsigned char Length){
	unsigned int i;
	long r=0;
	for (i=3; i<=(Length-3);i++){// 3-26 //total 24
		r += p[i];
	}
	return (unsigned int)(r/(Length-5));
}

int IntGetAverage(int *p,unsigned char Length){
	int i;
	long r=0;
	for (i=3; i<=(Length-3);i++){// 3-26 //total 24
		r += p[i];
	}
	return int(r/(Length-5));
}

long LongGetAverage(long *p,unsigned char Length){
	int i;
	long r=0;
	for (i=3; i<=(Length-3);i++){// 3-26 //total 24
		r += p[i];
	}
	return int(r/(Length-5));
}

int IntGetAverageG(int *p,unsigned char Length){
	int i;
	long r=0;
	for (i=0; i<=Length;i++){// 3-26 //total 24
		r += p[i];
	}
	return int(r/(Length+1));
}

void LongSortArray(long *p, unsigned char Length){
	unsigned char i, j;
	unsigned int temp;
	for(j = Length;	j !=  0; j--){
		for(i = 0; i != j; i++){
			if(p[i] > p[i + 1]){
				temp = p[i + 1];
				p[i+ 1] = p[i];
				p[i] = temp;
			}
		}
	}
}

void UintSortArray(unsigned int *p, unsigned char Length){
	unsigned char i, j;
	unsigned int temp;
	for(j = Length;	j !=  0; j--){
		for(i = 0; i != j; i++){
			if(p[i] > p[i + 1]){
				temp = p[i + 1];
				p[i+ 1] = p[i];
				p[i] = temp;
			}
		}
	}
}



void IntSortArray(int *p, unsigned char Length){
	unsigned char i, j;
	unsigned int temp;
	for(j = Length;	j !=  0; j--){
		for(i = 0; i != j; i++){
			if(p[i] > p[i + 1]){
				temp = p[i + 1];
				p[i+ 1] = p[i];
				p[i] = temp;
			}
		}
	}
}

void FloatSortArray(float *p, unsigned char Length){
	unsigned char i, j;
	float temp;
	for(j = Length;	j !=  0; j--){
		for(i = 0; i != j; i++){
			if(p[i] > p[i + 1]){
				temp = p[i + 1];
				p[i+ 1] = p[i];
				p[i] = temp;
			}
		}
	}
}

unsigned char PrevStatusCheck(unsigned char *p, unsigned char Status ){
	if(*p == Status) return Status;
	else return 128;
}




void SortChar(unsigned char *p, unsigned char Length){
	unsigned char i, j, temp;
	for(j = Length;	j !=  0; j--){
		for(i = 0; i != j; i++){
			if(p[i] > p[i + 1]){
				temp = p[i + 1];
				p[i+ 1] = p[i];
				p[i] = temp;
			}
		}
	}
}


long JsonCounter;
// Name:device1 Temp:23.5 Humid:45.3
//#define PRINT_SENSOR_TABLE

  String Float2String4Json(float Val){
	  int temp= (int)(Val * 10);
    int Decimal =abs(temp);
    Decimal %= 10;
    return(String((int)Val) + '.' + String(Decimal));
  }




 void Leds_Run(void){
  unsigned char i;

  for(i=0; i<5;i++){
      if(i == LED_AP_MODE){
        if(LedStatus.AP_Mode){
          //isi yap
          return;
        }
      }
      if(i == LED_WIFI_CONNECT){
        if(LedStatus.WIFIConnect){
          //isi yap
          return;
        }
      }
      if(i == LED_TILT){
        if(LedStatus.Tilt){
			switch(Tilt.LedStatus){
				case 0:
            		if(Tilt.LedTimer){
                		Tilt.LedTimer--;
                		ColorSet(BLUE);
                		Tilt.LedTimer = 2;
                		Tilt.LedStatus++;
                		return;
            		}
				break;
				case 1:
            		if(Tilt.LedTimer){
                		Tilt.LedTimer--;
                		//ColorSet(NOCOLOR);
                		SetLeds4_IAQ_Level();
                		Tilt.LedTimer = 4;
                		Tilt.LedStatus++;
                		return;
            		}
				break;
				case 2:
            		if(Tilt.LedTimer){
                		Tilt.LedTimer--;
                		ColorSet(BLUE);
                		Tilt.LedTimer = 2;
                		Tilt.LedStatus++;
                		return;
            		}
				break;
				case 3:
            		if(Tilt.LedTimer){
                		Tilt.LedTimer--;
                		//ColorSet(NOCOLOR);
                		SetLeds4_IAQ_Level();
                		Tilt.LedTimer = 4;
                		Tilt.LedStatus=0;
                		LedStatus.Tilt = false;
                		return;
            		}
				break;
				default:
					LedStatus.Tilt = false;
					Tilt.LedStatus = 0;
            		return;
				break;
			}

         }
      }
      if(i == LED_CLOUD_DATASENT){
        if(LedStatus.CloudDataSent){
         //	LedStatus.CloudDataSent = false;
			if(DataSuccess)//SetLeds4_IAQ_Level();//ColorSet(NOCOLOR);
			SetLeds4_Animation(2); //LED_CLOUD_SUCCESS
			else //ColorSet(RED);
				ColorSet(BLUE);
          	return;
        }
      }
       if(i == LED_IAQ_STATUS){
		  // ConnectTimerLeds = On;
         if(LedStatus.IAQStatus)SetLeds4_IAQ_Level();
         else SetLeds4_Animation(4);// ColorSet(BLUE); LED_INIT_ANIM




         //SetLeds4_IAQ_Level();

         return;
 	}
  }// end of for
}// end of function


void ColorSet(long val){
  pinMode(RED_PIN, OUTPUT);//PinR = RED_PIN;
  pinMode(GREEN_PIN, OUTPUT);//PinG = GREEN_PIN;
  pinMode(BLUE_PIN, OUTPUT);//PinB = BLUE_PIN;
/*
	ValueR = (unsigned char)((val &  0x00FF0000) >> 0x10);
	ValueG = (unsigned char)((val &  0x0000FF00) >> 0x8);
	ValueB = (unsigned char) (val &  0x000000FF);
*/
  analogWrite(RED_PIN,(unsigned char)((val &  0x00FF0000) >> 0x10));delay(2);//PinR = RED_PIN;
  analogWrite(GREEN_PIN,(unsigned char)((val &  0x0000FF00) >> 0x8));delay(2);//PinG = GREEN_PIN;
  analogWrite(BLUE_PIN,(unsigned char) (val &  0x000000FF));//PinB = BLUE_PIN;
 // Serial.print("ValueR ");Serial.print(ValueR);Serial.print("ValueG ");Serial.print(ValueG);Serial.print("ValueB ");Serial.print(ValueB);
}


int TestColor;
int TestColorTimer;
bool SetInitColorAnim = 0;


void SetLeds4_IAQ_Level(void){
	if(SetInitColorAnim == 0)return;

	switch(Filtered.IAQ){
		case HEALTHY : ColorSet(GREEN);
		break;
		case MODERATE :ColorSet(YELLOW);
		break;
		case RISKY :ColorSet(DARKORANGE);
		break;
		case UNHEALTHY :ColorSet(MAGENTA);
		break;
		case HAZARDOUS :ColorSet(DARKRED);
		break;
		default :
		break;
	}
}


/*
int EndColorAnim  = 0;
void SetInitColorOnce(void){
	if(SetColorAnim == 1)return;
	SetColorAnim = 1;
	EndColorAnim = 0;
		switch(Filtered.IAQ){
			case HEALTHY : TestColor = 1;
			break;
			case MODERATE :TestColor = 2;
			break;
			case RISKY :TestColor = 3;
			break;
			case UNHEALTHY :TestColor = 4;
			break;
			case HAZARDOUS :TestColor = 0;
			break;
			default :
			break;
	}
}
*/
void SetLeds4_Animation(unsigned char ModeTimer){
	if(SetInitColorAnim == 0){
		SetInitColorAnim = 1;
		LedStatus.CloudDataSent = false;
		return;
	}


	TestColorTimer++;
	if(TestColorTimer < ModeTimer) return;
	TestColorTimer = 0;

	switch(TestColor){
		case 0 : ColorSet(GREEN);
		break;
		case 1 :ColorSet(YELLOW);
		break;
		case 2 :ColorSet(DARKORANGE);
		break;
		case 3 :ColorSet(MAGENTA);
		break;
		case 4 :ColorSet(DARKRED);
		break;
		case 5 :ColorSet(NOCOLOR); LedStatus.CloudDataSent = false;
		break;
		default :
		break;
	}
	TestColor++;
	if(TestColor > 5)TestColor=0;
/*
	EndColorAnim ++;
	if(EndColorAnim > 4){
		EndColorAnim = 0;

	}
*/
}

/*
	#endif
	#ifdef TESTCOLOR
	switch(TestColor){
		case 0 : ColorSet(GREEN);
		break;
		case 1 :ColorSet(YELLOW);
		break;
		case 2 :ColorSet(DARKORANGE);
		break;
		case 3 :ColorSet(MAGENTA);
		break;
		case 4 :ColorSet(DARKRED);
		break;
		default :
		break;
	}
	TestColor++;
	if(TestColor > 4)TestColor=0;

	#endif
*/








