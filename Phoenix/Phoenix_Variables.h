


// prototypes
void readPMconc();
void IAQSensorApp(void);
void KeyPrc(void);
void IAQ_Level_Calculation(void);
void IAQ_Trend_Calculation(void);
void ColorSet(long val);
void IAQ_Level(void);
void SetLeds4_IAQ_Level(void);
void SetLeds4_Animation(unsigned char);
void BarometerApp(void);
unsigned char SM_WarningsCall(void);
void TweetApp(void);

//#define UART_WAIT 10
int TimeOutUart=0;


// TouchSensor       TouchKey1;


float PrevNoiseRead = 0;
float Accx,Accy,Accz,AccPitch, AccRoll, AccmaxTilt; // BMA222 Accelomater Values
bool DataSuccess = 0;
byte DataSuccessTimer = 0;

struct{
  bool AP_Mode;
  bool WIFIConnect;
  bool Tilt;
  bool CloudDataSent;
  bool IAQStatus;
  bool AMS_Ok;
  unsigned char Priority;
}LedStatus;


unsigned char start[1];
unsigned  char data[10];
unsigned char TimeCnt;
unsigned char KeyBuff;
unsigned char LastKeyBuff;
unsigned char Test;
    int color = 0;

unsigned  int Testtimer;
unsigned char FadeR,FadeG,FadeB;
unsigned char Timer500mSec,Timer1Sec,Timer5Sec,Timer10Sec;



unsigned char DataFailTimer=0;
unsigned  int TaskTimer;
unsigned char Task=0;



unsigned char ValueR,ValueG,ValueB;
bool Task100mSec,Task500mSec,Task1Sec,Task5Sec,Task10Sec;
struct {
  bool WIFIDisconnect;
  bool ServerDisconnect;
}Simulation;
unsigned int Disconnectiones=0;
unsigned int CloudFail=0;

float temperature_c, temperature_f;
long PressureLong;
float Pressure;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;
unsigned char RGBTimer;

    // Create Variable to store altitude in (m) for calculations;
    //double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)
double base_altitude = 32.8; // Altitude of SparkFun's HQ in Boulder, CO. in (m)





struct{
    uint16_t eCO2;
    uint8_t statu;
    int32_t Resistance;
    uint16_t TVOC;
}IAQ;



//bool ConnectTimerLeds = 0;

byte readCO2_S8SenseAir[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};  //Command packet to read Co2 (see app note)
byte response_S8SenseAir[] = {0,0,0,0,0,0,0};  //create an array to store the response
int valMultiplier_S8SenseAir = 1;

struct{
  bool TimoeutStart;
  int TimoeutFollower;// = TIMEOUT;
  unsigned int Buzzer;
  unsigned int Fan;
}Timer;


//AMS_IAQ_CORE_C iaqcore;

unsigned int UartError =0;
unsigned int PMFail =0;
unsigned int PMSuccess =0;



float Noise,PM10,SurfaceTemp;

struct{
	float Temperature;
	float Humidity;
	float PM25;
	unsigned int Light;
	float Pressure;
    int CO2;
    float Ammonia;
    float CO;
}RawValue;

struct{
	float Temperature;
	float Humidity;
	float PM25;
	int TVOC;
	int CO2e;
	int CO2_Absolute;
	unsigned int Light;
	float Noise;
	float Pressure;
	int IAQ;
	signed char Temperature_Trend;
	signed char Humidity_Trend;
	signed char PM25_Trend;
	signed char TVOC_Trend;
	signed char CO2e_Trend;
	signed char CO2_Absolute_Trend;
	signed char Light_Trend;
	signed char Noise_Trend;
	signed char Pressure_Trend;
	float PrevTemperature;
	float PrevHumidity;
	float PrevPM25;
	int PrevTVOC;
	int PrevCO2e;
	int PrevCO2_Absolute;
	unsigned int PrevLight;
	float PrevNoise;
	float PrevPressure;
	bool TrendInit;
}Filtered;


String Jsondata;
String String_Temperature ="";
String String_Humidity    ="";
String String_Pressure    = "";
String String_Light = "";
String String_PM25 = "";
String String_TVOC = "";
String String_CO2e = "";
String String_Noise  = "";


struct{
	bool Calibrated;
	bool Moved;
	bool Tweet;
	unsigned char  LedTimer;
	unsigned char  LedStatus;
	int index;
	 int Current;
	 int Average;
	 int Positive;
	 int Negative;
	// unsigned char PushNotifTimer;
}Tilt;

struct{
	unsigned char Tweet;
	unsigned char Email;
	bool Tilt;
	 unsigned int RegularTimer;
	 unsigned int OnDemandTimer;
}PushNotification;

int GSensorArr[GSENSORTASK_MAX+1];
float TempArr[SENSOR_MAXTASK+1];
float HumArr[SENSOR_MAXTASK+1];
float PMArr[SENSOR_MAXTASK+1];
int VOCArr[SENSOR_MAXTASK+1];
int CO2eArr[SENSOR_MAXTASK+1];
int CO2_AbsoluteArr[SENSOR_MAXTASK+1];
unsigned int LightArr[SENSOR_MAXTASK+1];
float PressureArr[SENSOR_MAXTASK+1];

bool SensorDataReady2Send = false;

String IAQstr="No Measurement";

// http://52.164.214.113/conf.html     to change
// http://52.164.214.113/mobileConf.txt   read
  //	 username = "mobile0";
  //	 password = "mobile0pass";

unsigned char IAQ_Health[5];



String SM_ProbType = "Temperature is "; //15
String SM_Problem = "Extreme High"; //13

//String SM_HumAdvice1="Humidity is OK        "; //22

String SM_Advice = "You are Freezing!"; //17

String SM_TempProblem = "Temperature is LOW  "; //20




struct{
	unsigned char Dominant; // 0-7
	unsigned char Temperature; // 0-8
	unsigned char  Humidity;
	unsigned char  Dust;
	unsigned char  Noise;
	unsigned char  Pressure;
    unsigned char  CO2;
	unsigned char  VOC;
}SM_Warnings;  // SM_Warnings.Temperature






