/*
  2017.26.03 ILKER
  		Provisioning by AP Mode and AP2STA STA2AP Modes add
  			http://www.ti.com/tool/wifistarterpro
		internal web server of CC3200 can store up to 10 profiles
		profiles are scannned by priority when any found connects to it
		profiles can be add by mobile app only.
		Pressing to SW2 at initilaize gets to AP Mode or either upside down detecting from Gsensor!
		There is 30 sec timeout for connecting to WIfI network and 30 sec timeout for getting IP
		tries to connect to a wifi profile in an endsless loop
  2017.28.03 ILKER
  		AP Mode Purple blink
  		STA Connecting to WIFI Blue Blink


*/

//http://www.ti.com/product/CC3200


//#define ACCESS_POINT_MODE
//#define HOMENETWORK
//#define ELUXNETWORK
//#define MOBILENETWORK
//#define TRIODORNETWORK



/*
#if (defined AP_MODE && defined SP_MODE)
//	#error if  both selected
#endif

#if (defined SP_MODE)
		#if (defined HOMENETWORK && defined WORKNETWORK)
			#error if   both selected
		#endif
		#if (defined HOMENETWORK && defined MOBILENETWORK)
			#error if   both selected
		#endif
		#if (defined WORKNETWORK && defined MOBILENETWORK)
			#error if   both selected
		#endif
#endif
*/

int status = WL_IDLE_STATUS;
int keyIndex = 0;

#define AP_MODE 0
#define STA_MODE 1
#include <udma_if.h>
uint8_t mode = 0;
uint8_t mode_init = 0;
const char ssid[] = "Phoenix";
const char pass[] = "password";//password


// + "_" + Device[USERID]

const char UDP_s[2] = "-";
char *token;

//String y = "";
char Rssid[100],Rpsk[100];

unsigned int UDP_Port =2390;
char UDP_packetBuffer[255];
//IPAddress Ip(255,255,255,255);
//char UDP_b[1024];
//int j=0;

WiFiUDP Udp;


// prototypes
void InitWifiDHCP(void);
bool InitWifi(void);
void printWifiStatus(void);
void CheckWifi(void);
void InfoLine(void);
void Update_Compiler_Info(void);
void CompilerInfo(void);
void GetReady4SendString(void);
void ParseString4Server(char *c);
void ApplianceUartPrc();
void GetOnlineAppliance();
void TestPrc();
void printRouterMAc(void);
void AP_Init(void);
void  AP_UDP(void);
void printMAcAddr(void);
// variables
  int Lost_Connection=0;
  int Re_Connection=0;
  int Lost_IP=0;
  int Re_IP = 0;
  byte LostConnectStatus=0;
bool AP_Mode;
bool SP_Mode_Once = 0;
byte  AP_Timer;
bool AP_PowerUp = 0;

/*
	#ifdef SERVER_APP
			String AppName = "******************************Server Application***************************";
			// port defined in main code!
	#endif
	#ifdef CLIENT_APP
			String AppName = "******************************Client Application***************************";
			int port = 5555;
	#endif
*/

void  AP_UDP(void){
	LedStatus.AP_Mode = true;

    AP_Timer++;
    if(AP_Timer < 20)ColorSet(PURPLE);
    else if(AP_Timer < 40)ColorSet(WHITE);
    if(AP_Timer > 40)AP_Timer = 0;
	if(AP_Timer ==  0)Serial.print("&");
  	Udp.begin(UDP_Port);
	int packetSize = Udp.parsePacket();
	if (packetSize){
		int len = Udp.read(UDP_packetBuffer, 255);
		if (len > 0)UDP_packetBuffer[len] = 0;
		//unit=atoi(packetBuffer);
		Serial.println(UDP_packetBuffer);

		/* get the first token */
		token = strtok(UDP_packetBuffer, UDP_s);
		int w = 0;

		while( token != NULL ) {
			if(w == 0){
				strcpy(Rssid,token);
				Serial.println(Rssid);
				w++;
			}
			else if(w == 1){
				strcpy(Rpsk,token);
				Serial.println(Rpsk);
			}
			token = strtok(NULL, UDP_s);
		}

		UDMAInit();
		sl_Start(NULL, NULL, NULL);
		sl_WlanDisconnect();
		sl_NetAppMDNSUnRegisterService(0, 0);
		sl_WlanRxStatStart();
		sl_WlanSetMode(ROLE_STA);
		// Restart Network processor
		sl_Stop(30);
		sl_Start(NULL, NULL, NULL);

		WiFi._initialized = false;
		WiFi._connecting = false;
		// attempt to connect to Wifi network:
		Serial.print("Attempting to connect to Network named: ");
		delay(1000);
		// print the network name (SSID);
		Serial.println(Rssid);
		//WiFi._initialized = false;
		//WiFi._connecting = false;
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		WiFi.begin(Rssid, Rpsk);
		while ( WiFi.status() != WL_CONNECTED) {
			// print dots while we wait to connect
			Serial.print(".");
			delay(300);
		}
		Serial.println("\nYou're connected to the network");
		Serial.println("Waiting for an ip address");
		while (WiFi.localIP() == INADDR_NONE){
			// print dots while we wait for an ip addresss
			Serial.print(".");
			delay(300);
		}
		Serial.println("\nIP Address obtained");
		// you're connected now, so print out the status
		printWifiStatus();
		mode=STA_MODE;
	}
}

void AP_Init(void){
    mode = AP_MODE;
	Serial.println("Starting AP Mode");

	Serial.print("Setting up Access Point named: ");
	Serial.println(ssid);  // + String(Device[USERID])
	Serial.print("AP uses WPA and password is: ");
	Serial.println(pass);

	WiFi.beginNetwork((char *)ssid, (char *)pass);

	while (WiFi.localIP() == INADDR_NONE)
	{
	// print dots while we wait for the AP config to complete
	Serial.print('.');
	delay(300);
	}
	Serial.println();
	Serial.println("AP active.");
	printWifiStatus();
//	digitalWrite(RED_LED,HIGH);
	// Your AP mode setup code goes here..

}

void InfoLine(void) {
	/*
    Serial.println("");Serial.println(AppName);
    printWifiStatus();
    CheckWifi();
    Serial.println();
    */
}

void Leds_INIT(void) {
//   delay(100);
/*
    pinMode(RED_LED, OUTPUT);delay(1);
    pinMode(YELLOW_LED, OUTPUT); delay(1);
    pinMode(GREEN_LED, OUTPUT);  delay(1);

      digitalWrite(RED_LED, LOW);  delay(1);
     digitalWrite(YELLOW_LED, LOW);delay(1);
     digitalWrite(GREEN_LED, LOW);     delay(1);
*/
  //  pinMode(GPIO_22, INPUT);delay(10); // SW2 on launcpad
 //   pinMode(GPIO_13 , INPUT);delay(10);// SW3 on launcpad

    pinMode(PUSH1, INPUT);delay(10);// SW3 on launcpad
    pinMode(PUSH2, INPUT);delay(10);// SW2 on launcpad
/*
     digitalWrite(GREEN_LED, LOW);  delay(10);
     digitalWrite(YELLOW_LED, LOW);delay(10);
     digitalWrite(RED_LED, LOW);     delay(10);
*/
}
void Leds_Release4Uart(void) {

    pinMode(YELLOW_LED, INPUT); delay(10);
    pinMode(GREEN_LED, INPUT);  delay(10);
}

void Leds_WIFI_On(void) {
	//RGBLed1.DispColor(BLUE);
	ColorSet(BLUE);delay(150);
//	digitalWrite(GREEN_LED, HIGH); delay(50);
//	digitalWrite(YELLOW_LED, HIGH);delay(50);
//    digitalWrite(RED_LED, HIGH);   delay(50);



}
void Leds_WIFI_Off(void) {
//	RGBLed1.DispColor(NOCOLOR);
	//ColorSet(WHITE);

//	if(ConnectTimerLeds == 1)SetLeds4_IAQ_Level();
//	else
	ColorSet(NOCOLOR);
	delay(150);


//	digitalWrite(GREEN_LED, LOW); delay(50);
//	digitalWrite(YELLOW_LED, LOW);delay(50);
//    digitalWrite(RED_LED, LOW);   delay(50);


}

void Leds_IP_On(void) {
//	RGBLed1.DispColor(BLUE);
	ColorSet(BLUE);delay(150);
//	digitalWrite(RED_LED, HIGH); delay(50);
//	digitalWrite(YELLOW_LED, HIGH);delay(50);
//    digitalWrite(GREEN_LED, HIGH);   delay(50);


}
void Leds_IP_Off(void) {
//	RGBLed1.DispColor(NOCOLOR);
	ColorSet(NOCOLOR);delay(150);
//	digitalWrite(RED_LED, LOW); delay(50);
//	digitalWrite(YELLOW_LED, LOW);delay(50);
 //   digitalWrite(GREEN_LED, LOW);  delay(50);

}
bool AP_Switch(void){
	if(digitalRead(PUSH2)){
		mode_init = AP_MODE;
		AP_Init();
		Serial.print("Couldnt get IP Switching To AP Mode");
		return 1;// return as AP
	}
	return 0;
}
bool G_Sensor_Switch(void){
//	if(AP_PowerUp)return 0;//do once on startup
//	AP_PowerUp = 1; //
	G_SensorRead();
	if(abs(Accx) < 0.1){
		if(Accy < -0.9){
			if(abs(Accz) < 0.1){
				mode_init = AP_MODE;
				AP_Init();
				Serial.print("Couldnt get IP Switching To AP Mode");
				G_SensorPrint();
				return 1;// return as AP
			}
		}
	}
	return 0;
}



bool j=1;
void printEncryptionType(int thisType) {
  // read the encryption type and print out the name
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.print("WEP");
      break;
 //   case ENC_TYPE_WPA_PSK:
    case ENC_TYPE_TKIP:
      Serial.print("WPA");
      break;
 //   case ENC_TYPE_WPA2_PSK:
    case ENC_TYPE_CCMP:
      Serial.print("WPA2");
      break;
    case ENC_TYPE_AUTO:
      Serial.print("Auto");
      break;
    case ENC_TYPE_NONE:
      Serial.print("None");
      break;
  }
  Serial.println(thisType);
  Serial.println();
}

void listNetworks()
{
  // scan for nearby networks
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
   // while (true);
  }

  // print the list of networks seen
  Serial.print("Number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
  //  printEncryptionType(WiFi.encryptionType(thisNet));
     switch (WiFi.encryptionType(thisNet)) {
    case ENC_TYPE_WEP:
      Serial.print("WEP");
      break;
 //   case ENC_TYPE_WPA_PSK:
    case ENC_TYPE_TKIP:
      Serial.print("WPA");
      break;
 //   case ENC_TYPE_WPA2_PSK:
    case ENC_TYPE_CCMP:
      Serial.print("WPA2");
      break;
    case ENC_TYPE_AUTO:
      Serial.print("Auto");
      break;
    case ENC_TYPE_NONE:
      Serial.print("None");
      break;
  }
   Serial.println();
  }
}





bool InitWifi(void) {
	int i=0;
	LedStatus.WIFIConnect = true;
	if(j){
		j=0;
	}
	listNetworks();
	PrintDeviceInfo();

	mode_init = STA_MODE;
		// https://www.arduino.cc/en/Reference/WiFiStatus
//	if(WiFi.begin() == WL_CONNECT_FAILED) return 0;// fail

//	status = WiFi.begin(ssid, keyIndex, key);
	while(WiFi.begin() !=WL_CONNECT_FAILED){

	    Serial.print("Connecting to a stored profile: ");
	    Serial.println(WiFi.SSID());
	    while ( WiFi.status() != WL_CONNECTED) {

	      // print dots while we wait to connect
	        Serial.print("?");
	        i++; // put timeout if more than a certain time go into AP Mode or by a button! 30 sec timeout
	      	if(i> 100){
		//	  WiFi.disconnect();
			  Serial.println("\nConnection Problem!");
			  i=0;
			  return 0;
		  }
		  	if(AP_Switch() || G_Sensor_Switch())return 1;
	        Leds_WIFI_On();
			Leds_WIFI_Off();
	    }



	    Serial.println();
	    printWifiStatus();
	    i = 0;
	    while (WiFi.localIP() == INADDR_NONE) {
	      // print dots while we wait for an ip addresss
	       Serial.print("*");
	      i++; // put timeout if more than a certain time go into AP Mode or by a button! 30 sec timeout
	      if(i> 100){
			  WiFi.disconnect();
			  Serial.println("\nIP Address Problem!");
			  i=0;
			  return 0;
		  }
		  if(AP_Switch() || G_Sensor_Switch())return 1;
		  Leds_IP_On();
     	  Leds_IP_Off();
	    }
	      Serial.println("\nIP Address obtained");
	      Serial.print("IP Address: ");
	      Serial.println(WiFi.localIP());
	      Serial.println("STA Mode");
	      printWifiStatus();
		  Leds_WIFI_Off();
		  /*
		        SetBeepOn();
		          delay(1000);
         SetBeepOff();
         */
	      mode = STA_MODE;
	      /*
	      	digitalWrite(GREEN_LED, HIGH); delay(50);
		  	digitalWrite(YELLOW_LED, HIGH);delay(50);
    		digitalWrite(RED_LED, LOW);   delay(50);
    		*/
	      break;
  	}// end of if(WiFi.begin() !=WL_CONNECT_FAILED)
  	LedStatus.WIFIConnect = false; // turn off leds
 // 	ConnectTimerLeds = 1;
    return 1;
}


void printRouterMAc(void) {
    // print the MAC address of the router you're attached to:
  Serial.print("RouterMac: ");
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(mac[0], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[5], HEX);
}
void printMAcAddr(void) {
    // print the MAC address of the router you're attached to:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(" MACAdd:");
  Serial.print(mac[0], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[5], HEX);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void printWifiStatus(void) {
  // print the SSID of the network you're attached to:
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
    // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(" RSSI:");
  Serial.print(rssi);
  Serial.print(" dBm");
    // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print(" BSSID:");
  Serial.print(bssid[0], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[5], HEX);
  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print(" Encryption Type:");
  Serial.print(encryption, HEX);
  switch (encryption) {
    case ENC_TYPE_WEP:
      Serial.print("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.print("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.print("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.print("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.print("Auto");
      break;
       default:
      Serial.print("???");
      break;
  }
  Serial.println();
  IPAddress ip =WiFi.localIP();
  Serial.print("IPAddr:");
  Serial.print(ip);
  printMAcAddr();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print(" GATEWAY:");Serial.println(gateway);

	#ifdef SERVER_APP
		Serial.print(" Port:");Serial.println(port);
	#endif
	#ifdef CLIENT_APP
		//	Serial.print(" ServerSocket:");Serial.print(servername);Serial.print(":");Serial.println(port);
	#endif
}

void PrintZeros(char i){
	if(i<10) Serial.print("0");
	Serial.print(i);
}
/*

void DHCP_Check(void){
  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:
      //nothing happened
      break;

  }


}
*/
unsigned char Date[12] = __DATE__; // "Mmm dd yyyy"
unsigned char Time[9] = __TIME__; // "hh:mm:ss"

struct{
	unsigned char Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned int Year;
	unsigned char Date;
	unsigned char Month[3];
}Compile_Info;  // Compile_Info.Minute

void Update_Compiler_Info(void){
 	Compile_Info.Month[0] = Date[0];
 	Compile_Info.Month[1] = Date[1];
 	Compile_Info.Month[2] = Date[2];
	Compile_Info.Date = (Date[4]-48)*10 + (Date[5]-48);
 	Compile_Info.Year = (Date[7]-48)*1000 + (Date[8]-48)*100 + (Date[9]-48)*10 + (Date[10]-48) ;

  	Compile_Info.Hour =   (Time[0]-48)*10 + (Time[1]-48);
  	Compile_Info.Minute = (Time[3]-48)*10 + (Time[4]-48);
  	Compile_Info.Second = (Time[6]-48)*10 + (Time[7]-48);

/*
   	Compile_Info.Hour =   (Time[0])*10 + (Time[1]);
  	Compile_Info.Minute = (Time[3])*10 + (Time[4]);
  	Compile_Info.Second = (Time[6])*10 + (Time[7]);
  	*/
}
void CompilerInfo(void){
//	Serial.println(AppName);
	Update_Compiler_Info();
	Serial.print("Compile Time & Date :");

	Serial.print(Compile_Info.Hour);Serial.print(':');
	Serial.print(Compile_Info.Minute);Serial.print(':');
	Serial.print(Compile_Info.Second);

/*
	PrintZeros((char)Compile_Info.Hour);Serial.print(':');
	PrintZeros((char)Compile_Info.Minute);Serial.print(':');
	PrintZeros((char)Compile_Info.Second);
*/
	Serial.print("      ");

	PrintZeros((char)Date[4]);
	PrintZeros((char)Date[5]);
	Serial.print('.');
/*

	Serial.print((char)Date[4]);
	Serial.print((char)Date[5]);
	Serial.print('.');
*/
	Serial.print((char)Date[0]);
	Serial.print((char)Date[1]);
	Serial.print((char)Date[2]);Serial.print('.');


	Serial.print(Compile_Info.Year);
	//Serial.println();
	#ifdef CLIENT_APP
	 	//	Serial.print("Default ServerSocket:");Serial.print(servername);Serial.print(":");Serial.println(port);
	#endif

}

/*
      countClients = WiFi.getTotalDevices();
                 Serial.print("Client #");
                Serial.print(countClients);
                Serial.print(" at IP address = ");
                Serial.print(WiFi.deviceIpAddress(countClients));
                Serial.print(", MAC = ");
                Serial.println(WiFi.deviceMacAddress(countClients));
*/
/*
struct StrAppliance{
  byte ACMode;
  byte ACFanLevel;
  byte ACTemperature;  //  NUMERIC VALUE
  byte Humidifier;
  byte Purifier;
  byte Robot;
};

struct StrAppliance Appliance,ApplianceRunning;       //Appliance is the new setting data, ApplianceRunning is the old setting data
*/
// Appliance.ACMode
#define AC_OFF 0
#define AC_COOL 1
#define AC_HEAT 2
#define AC_DEHUM 3
#define AC_AUTO 4  // FUTURE USE

// Appliance.ACFanLevel
#define FAN_OFF 0
#define FAN_LOW 1
#define FAN_MID 2
#define FAN_HIGH 3

// Appliance.Humidifier
#define HUM_OFF 0
#define HUM_LOW 1
#define HUM_MID 2
#define HUM_HIGH 3

// Appliance.Purifier
#define PUR_OFF 0
#define PUR_LOW 1
#define PUR_MID 2
#define PUR_HIGH 3

// Appliance.Robot
#define ROBOT_OFF 0
#define ROBOT_ON 1

//---chenll,modifiy start
struct StrAppliance{
  byte ACMode;
  byte ACFanLevel;
  byte ACTemperature;  //  NUMERIC VALUE
  byte Humidifier;
  byte Purifier;
  byte Robot;
};

struct StrAppliance Appliance,ApplianceRunning;       //Appliance is the new setting data, ApplianceRunning is the old setting data
//---chenll,modifiy end


void ParseString4Server(char *c){
	String str="";
	byte i = 0;

              if(c[i] == 'j'){
                Appliance.ACMode = (byte)c[i+1] - '0'; // ascii2 number

               switch(Appliance.ACMode){
					default:
					case AC_OFF:str ="Off";
					break;
					case AC_COOL:str ="Cool";
					break;
					case AC_HEAT:str ="Heat";
					break;
					case AC_DEHUM:str ="Dehum";
					break;
					case AC_AUTO:str ="Auto";
					break;

				}
				Serial.print(" ACMode:");Serial.print(str);
              }

              if(c[i] == 'k'){
                Appliance.ACFanLevel = (byte)c[i+1] - '0'; // ascii2 number
                switch(Appliance.ACFanLevel){
					default:
					case FAN_OFF:str ="Off";
					break;
					case FAN_LOW:str ="Low";
					break;
					case FAN_MID:str ="Mid";
					break;
					case FAN_HIGH:str ="High";
					break;
				}
				Serial.print(" Fan:");Serial.print(str);

              }
              if(c[i] == 'l'){
                Appliance.ACTemperature = ((byte)c[i+1] - '0')*10 +( (byte)c[i+2] - '0');
         //       Appliance.ACTemperature += (byte)c[i+2] - '0';
                Serial.print(" Temp:");Serial.print(Appliance.ACTemperature);Serial.print("'C");
              }
              if(c[i] == 'm'){
                Appliance.Humidifier = (byte)c[i+1] - '0';// ascii2 number
                switch(Appliance.Humidifier){
					default:
					case HUM_OFF:str ="Off";
					break;
					case HUM_LOW:str ="Low";
					break;
					case HUM_MID:str ="Mid";
					break;
					case HUM_HIGH:str ="High";
					break;

				}
                Serial.print(" Humidifier:");Serial.print(str);
              }
              if(c[i] == 'n'){
                Appliance.Purifier = (byte)c[i+1] - '0';// ascii2 number
                switch(Appliance.Purifier){
					default:
					case PUR_OFF:str ="Off";
					break;
					case PUR_LOW:str ="Low";
					break;
					case PUR_MID:str ="Mid";
					break;
					case PUR_HIGH:str ="High";
					break;
				}
                Serial.print(" Purifier:");Serial.print(str);
              }
              if(c[i] == 'o'){
                Appliance.Robot = (byte)c[i+1] - '0';// ascii2 number
                Serial.print(" Robot:");Serial.print(Appliance.Robot);
              }



}

void CheckDataFail(void){
                  if(!DataSuccess){ // if data successfully send blink!
                        DataFailTimer++;
                        if(DataFailTimer > 10){ // if 10 times fail reset
                            DataFailTimer = 0;
                            Disconnectiones++;
                            // stop client  ?  client.stop();   // SendNodeJs2Triodor disconnect
                             while(!InitWifi());// as long as no wifi found loop or exit by button sw2
                             Task = TASK_MAX;
                        }
                  }
                 else  DataFailTimer=0;


}
void CheckWIFIFail(void){

                      if(Simulation.WIFIDisconnect){
                            Simulation.WIFIDisconnect = false;
                        //   WiFi.disconnect();
                        //    delay(10);
                         //   Serial.println("Wifi err");
                      }
                      if((WiFi.status() != WL_CONNECTED) || (WiFi.localIP() == INADDR_NONE) ){
                        // check if wifi lost and try to reconnect according to the profiles
                      //      Serial.print("Wifi Retry");
                            while(!InitWifi());// as long as no wifi found loop or exit by button sw2
                            Task = TASK_MAX;
                     }

}


