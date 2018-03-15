#include <aJSON.h>
/* TEMBOO */
#include <Temboo.h>

/* AT2T */
#define PhoenixSensorBox
// #define AirPurifier
#define ENERGIA_PLATFORM
#include "M2XStreamClient.h"


#define TRIODOR_CLOUD

#ifdef AT2T_CLOUD
#include <atof.h>
#define ENERGIA_PLATFORM
#include <m2x-energia.h>
#include <M2XStreamClient.h>
#include <M2XStreamClient_template.h>
#include <NullPrint.h>
#endif

#include <aJSON.h>
#include "Energia.h"

#include <SLFS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
//#include <MutichannelGasSensor.h>
#include <BMA222.h>  // https://github.com/energia/Energia/blob/master/hardware/cc3200/libraries/BMA222/BMA222.cpp
#include <Adafruit_TMP006.h>  //http://www.ti.com/product/TMP006/description
// http://www.ti.com/product/CC3200
// http://www.ti.com/lsds/ti/microcontrollers_16-bit_32-bit/wireless_mcus/simplelink_cc3x/overview.page
#include <SparkFunT5403.h>
#include "SIm7013.h"
#include "ReadNoise.h"
#include "TSL2561.h"

#include "IRRemote_energia.h"
//#include "TouchSensor.h"
#include "AMS_IAQ_CORE_C.h"
#include <RGBDriving.h>
#include <Appliance.h>

#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
      

// objects
//UartPrc Uart1;
SI7013 rh_sensor;               //initiate an object of SI7013 class
NoiseRead noise;                // object to read data from the GTC noise sensor
TSL2561 al_sensor;              // initiate an object of TSL2561 class (ambient light sensor)
AMS_IAQ_CORE_C iaqcore;
BMA222 GSensor;
Adafruit_TMP006 tmp006(0x41);
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)
T5403 barometer(MODE_I2C);
IRRemoteSend      IRSend1;
RGBDrv            RGBLed1;

#include "Phoenix_Definitions.h"
#include "C:\Projects\Energia\Keys\Phoenix_Accounts.h" // comment out instead use below file Phoenix_Keys.h
//#include "Phoenix_Keys.h" // Contains Cloud Keys account information

#include "Phoenix_Variables.h"
WiFiClient client;
M2XStreamClient m2xClient(&client, Device[AT2T_API_KEY]);

// #define NO_SENSOR_INIT
//#define NO_SENSOR

#include "Phoenix_Debug.h"
#include "Phoenix_Func.h"
#include "Phoenix_Sensor.h"

#include "Phoenix_PushNotf.h"  // Contains Twitter  account information
#include "Phoenix_Cloud.h"
#include "Phoenix_WIFI.h"



#include "Phoenix_TaskLoop.h"


//#include "Phoenix_CloudDebug.h"


void setup()
{
  Phoenix_StartUp();
}

void loop() {
  Phoenix_Loop();

} //end of loop











