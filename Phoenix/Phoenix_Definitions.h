
	//			#define LAB_TEST_DEVICE
	//			#define TEMP_CORRETION 2
				#define 	TESTCOLOR
#define TSL2591_LIGHT_NEW
//#define TSL2561_LIGHT_OLD

#define TASK_MAX 59
#define SENSOR_MAXTASK 29


//#define LAB_TEST_DEVICE // comment out if sensor is ot used
//#define SENSEAIR_CO2_INSTALLED // comment out if sensor is ot used

#define CO2Base 450 // 450 ppm normal base level
#define VOCBase 125 // 125 ppb normal base level


#define LED_CLOUD_SUCCESS 2
#define LED_INIT_ANIM 4





#define DARKMAGENTA   0x8b008b
#define  DARKVIOLET   0x9400d3
#define  FALAN   0x9434d3

#define  RED_PIN     31        //chenll,changed,CC3200 GPIO24,pin17
#define GREEN_PIN   29        //chenll,changed,CC3200 GPIO25,pin21
#define BLUE_PIN    13        //chenll,changed,CC3200 GPIO09,pin64

#define   FAN_PORT      5         //P61 GPIO_06
#define   BEEP_PORT     4         //P03 GPIO_12
//#define   TRY1_PORT     28         //works
//#define   TRY1_PORT     27         //works
//#define   TRY1_PORT     8     //works
//#define   TRY1_PORT     7   //works
//#define   TRY1_PORT     3 //works
//#define   TRY1_PORT     2  //works
//#define   TRY1_PORT     23  // olmadi
//#define   TRY1_PORT     24  // works
//#define   TRY1_PORT     25  //  olmadi
//#define   TRY1_PORT     26 //  olmadi

#define   TRY1_PORT     30 // works



#define   TRy1_High()           digitalWrite(TRY1_PORT,HIGH)
#define   TRy1_Low()           digitalWrite(TRY1_PORT,LOW)
#define   SetFanOn()           digitalWrite(FAN_PORT,HIGH)
#define   SetFanOff()          digitalWrite(FAN_PORT,LOW)
#define   SetBeepOn()          digitalWrite(BEEP_PORT,HIGH)
#define   SetBeepOff()         digitalWrite(BEEP_PORT,LOW)


#define MAX_Temperature 60 // 1C
#define MAX_Humidity 90   // 2
#define MAX_TVOC 1000
#define MAX_CO2 3000
#define MAX_PM25 300   // 2
#define MAX_LIGHT 40000 // 1C

#define MIN_Temperature -25 // 1C
#define MIN_Humidity 10   // 2
#define MIN_TVOC 100
#define MIN_CO2 250
#define MIN_PM25 0.1   // 2
#define MIN_LIGHT 0 // 1C

           // PRIORITIIES // o-> HIGH   4-> least
#define LED_AP_MODE 0
#define LED_WIFI_CONNECT 1
#define LED_TILT 2
#define LED_CLOUD_DATASENT 3
#define LED_IAQ_STATUS 4

#define HEALTHY 0
#define MODERATE 1
#define RISKY 2
#define UNHEALTHY 3
#define HAZARDOUS 4

#define QUE_PM25 0
#define QUE_TEMP 1
#define QUE_HUMD 2
#define QUE_VOC 3
#define QUE_CO2 4



#define PM25_HEALTHY 1
#define PM25_MODERATE 35
#define PM25_RISKY     75
#define PM25_UNHEALTHY 150
#define PM25_HAZARDOUS 250

#define PM25_HYST_MODERATE 2
#define PM25_HYST_RISKY 10
#define PM25_HYST_UNHEALTH 30
#define PM25_HYST_HAZARDOUS 50


#define TEMPL_HAZARDOUS 10.1
#define TEMPL_UNHEALTHY 13.1
#define TEMPL_RISKY     15.1
#define TEMPL_MODERATE  18.1

//#define TEMP_HEALTHY    20


#define TEMPH_MODERATE  23.6
#define TEMPH_RISKY     26.6
#define TEMPH_UNHEALTHY 29.6
#define TEMPH_HAZARDOUS 32.6

#define TEMP_HYSTERESIZ 0.5






#define HUML_HAZARDOUS  15
#define HUML_UNHEALTHY  25
#define HUML_RISKY      35
#define HUML_MODERATE   45


//#define HUM_HEALTHY    40 // not considered


#define HUMH_MODERATE   55
#define HUMH_RISKY      65
#define HUMH_UNHEALTHY  75
#define HUMH_HAZARDOUS  85

#define HUM_HYSTERESIZ  2

#define TVOC_HEALTHY   125 //VOCBase 125 ppb
#define TVOC_MODERATE  225
#define TVOC_RISKY      325
#define TVOC_UNHEALTHY  425
#define TVOC_HAZARDOUS  625
#define TVOC_HYSTERESIZ  5

#define CO2e_HEALTHY  400 // CO2Base 450 ppm
#define CO2e_MODERATE 750
#define CO2e_RISKY    900
#define CO2e_UNHEALTHY 1000
#define CO2e_HAZARDOUS 1600
#define CO2e_HYSTERESIZ  20


#define INCREASE  1
#define STABLE   0
#define DECREASE -1

/*
#define INCREASE  2
#define STABLE   1
#define DECREASE 0
*/

#define TREND_TEMP_HYST 0.5
#define TREND_HUM_HYST  3
#define TREND_PM25_HYST 2
#define TREND_VOC_HYST 15
#define TREND_ECO2_HYST 25
#define TREND_LIGHT_HYST 4
#define TREND_NOISE_HYST 1
#define TREND_PRESSURE_HYST 1

#define DEVICEID 0
#define USERID 1
#define AT2T_CLOUD_ID 2
#define AT2T_API_KEY 3

#define USER_EMAIL2SEND 0
#define SEND_EMAIL 1
#define SEND_TWEET 2
#define CLOUD_ELUX 3
#define GOOGLE_SEARCH 4

#define DOM_NONE  0

#define DOM_DUST  1
#define DOM_TEMPERATURE  2
#define DOM_HUMIDITY  3


#define HIGH_EXT  8
#define LOW_EXT  7

#define HIGH_VERY 6
#define LOW_VERY  5

#define HIGH_TOO  4
#define LOW_TOO   3

#define HIGH_ABIT 2
#define LOW_ABIT  1

#define ITS_OK   0

#define GSENSORTASK_MAX 29

#define CALIB_LIMITS 3
#define MOVE_TRESHOLD 3  // increae for less sensivity
//#define RELEASE_TRESHOLD 3

// definitions

//#define min(a,b) ((a)<(b)?(a):(b))
//#define max(a,b) ((a)>(b)?(a):(b))

//unsigned int TweetTimer=5; // 2.5 minutes
//HardwareSerial coiki();
//Serial mySerial(10, 11); // RX, TX

