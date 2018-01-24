
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println(F(" lux"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  delay(500);
}


/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2591
*/
/**************************************************************************/
void configureSensor(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  // tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain

  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
  {
    case TSL2591_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((tsl.getTiming() + 1) * 100, DEC);
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

void simpleRead(void)
{
  // Simple data read example. Just read the infrared, fullspecrtrum diode
  // or 'visible' (difference between the two) channels.
  // This can take 100-600 milliseconds! Uncomment whichever of the following you want to read
 // uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
  uint16_t x = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
  //uint16_t x = tsl.getLuminosity(TSL2591_INFRARED);

  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("Luminosity: "));
  Serial.println(x, DEC);
}

/**************************************************************************/
/*
    Show how to read IR and Full Spectrum at once and convert to lux
*/
/**************************************************************************/
void advancedRead(void)
{
  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
  Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
  Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
  Serial.print(F("Lux: ")); Serial.println(tsl.calculateLux(full, ir));
}

/**************************************************************************/
/*
    Performs a read using the Adafruit Unified Sensor API.
*/
/**************************************************************************/
void unifiedSensorAPIRead(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  tsl.getEvent(&event);

  /* Display the results (light is measured in lux) */
  Serial.print(F("[ ")); Serial.print(event.timestamp); Serial.print(F(" ms ] "));
  if ((event.light == 0) |
      (event.light > 4294966000.0) |
      (event.light <-4294966000.0))
  {
    /* If event.light = 0 lux the sensor is probably saturated */
    /* and no reliable data could be generated! */
    /* if event.light is +/- 4294967040 there was a float over/underflow */
    Serial.println(F("Invalid data (adjust gain or timing)"));
  }
  else
  {
    Serial.print(event.light); Serial.println(F(" lux"));
  }
}

void IAQSensorApp(void)
{

#ifdef DEBUG_IAQ
	Serial.print("IAQ: ");
#endif
	if(!iaqcore.update())Serial.print("Update Failed!");
	for(uint8_t ii = 0; ii < 10; ii++)
	{
		// Serial.print(".");
		if(iaqcore.data[ii] < 16)
		{
			#ifdef DEBUG_IAQ
				Serial.print("0");
			#endif
		}
		#ifdef DEBUG_IAQ
			Serial.print(iaqcore.data[ii], HEX);
			Serial.print("-");
		#endif

		if(ii != 9)
		{
		// Serial.print(", ");
		}
	}

#ifdef DEBUG_IAQ

	Serial.print(" ");
#endif
	int Status = 44;
	int IAQ_CurrentStat = iaqcore.getStatus();


//#ifdef DEBUG_IAQ
	switch(IAQ_CurrentStat)
	{
		case AMS_IAQ_CORE_C_STATUS_BUSY:
						Status =  33; // sometimes we get busy better to follow previos value
			break;
		case AMS_IAQ_CORE_C_STATUS_OK:
						Status =  33;
				LedStatus.AMS_Ok = true;
			break;
		case AMS_IAQ_CORE_C_STATUS_ERROR:
			break;
		case AMS_IAQ_CORE_C_STATUS_WARMING_UP:
			break;
		default:
			break;
	}
	#ifndef LAB_TEST_DEVICE
	switch(IAQ_CurrentStat)
	{
		case AMS_IAQ_CORE_C_STATUS_BUSY:Serial.print("Busy ");
			break;
		case AMS_IAQ_CORE_C_STATUS_OK:Serial.print("OK ");
			break;
		case AMS_IAQ_CORE_C_STATUS_ERROR:Serial.print("Error ");
			break;
		case AMS_IAQ_CORE_C_STATUS_WARMING_UP:Serial.print("W.Up ");
			break;
		default:Serial.print("Undefined Code: ");
			break;
	}

	#endif
//#endif


	IAQ.Resistance = iaqcore.getResistanceOhms();
	IAQ.eCO2 = iaqcore.getCO2EquivalentPPM() ;   // base 450
	IAQ.TVOC = iaqcore.getTVOCEquivalentPPB() ; // base 125
	//    Serial.println("Resistance [ohms]: " + String(IAQ.Resistance));
	//    Serial.println("CO2 Equivalent [ppm]: " + String(IAQ.eCO2));
	//    Serial.println("TVOC Equivalent [ppb]: " +  String(IAQ.TVOC));
	//      Serial.println("Resistance [ohms]: CO2 Equivalent [ppm]: TVOC Equivalent [ppb]: ");

#ifdef DEBUG_IAQ
	Serial.print(String(IAQ.Resistance)+ "...." + String(IAQ.TVOC)+ "...."  +  String(IAQ.eCO2));
	Serial.println("  ->Always deafult values are send to mobile app unless data is ok");
#endif

	if(Status ==  44)
	{
		IAQ.eCO2 = CO2Base;
		IAQ.TVOC = VOCBase;
	}
}

unsigned int getValue_S8SenseAir(byte packet[])
{
/*
    int high = packet[3];                        //high byte for value is 4th byte in packet in the packet
    int low = packet[4];                         //low byte for value is 5th byte in the packet
    unsigned long val = high*256 + low;                //Combine high byte and low byte with this formula to get value
*/
 //    int high = packet[3];                        //high byte for value is 4th byte in packet in the packet
 //   int low = packet[4];  //low byte for value is 5th byte in the packet
    unsigned int val = packet[3]*256 + packet[4];                //Combine high byte and low byte with this formula to get value

	return val;
  //  return val* valMultiplier_S8SenseAir;
}


void sendRequest(byte packet[]) {
	    Serial1.begin(9600);
	    delay(10);
	  while(!Serial1.available())  //keep sending request until we start to get a response
	  {
	    Serial1.write(readCO2_S8SenseAir,7);
	    delay(50);
	//    TimeOutUart++; if(TimeOutUart > UART_WAIT){TimeOutUart=0; return 0;}
  }
    int timeout=0;  //set a timeoute counter
    while(Serial1.available() < 7 ) //Wait to get a 7 byte response
    {
      timeout++;
      if(timeout > 10)    //if it takes to long there was probably an error
        {
          while(Serial1.available())  //flush whatever we have
            Serial1.read();

            break;                        //exit and try again
        }
        delay(50);
//        TimeOutUart++; if(TimeOutUart > UART_WAIT){TimeOutUart=0; return 0;}
    }

    for (int i=0; i < 7; i++)
    {
      response_S8SenseAir[i] = Serial1.read();
    }
 //   return 1;
}
void readCO2SenseAir(void) {
//  if(sendRequest(readCO2_S8SenseAir) == 1) RawValue.CO2 = getValue_S8SenseAir(response_S8SenseAir);
	sendRequest(readCO2_S8SenseAir);
	RawValue.CO2 = getValue_S8SenseAir(response_S8SenseAir);
}


//--------------------------------
void readPMconc(void) {

    int j=0;
    int i=0;
    int checksum = 0;
//    Serial1.begin(9600); //dont do doesnt work!!
    delay(10);

    for (i=0; i<10; i++){
        data[i]=0;
    }
    start[0]=0;
    i=0;
    		#ifndef LAB_TEST_DEVICE
			Serial.print("a");
			#endif

	#define UART_WAIT 30

    while (Serial1.available()<=0 && i<UART_WAIT){ // code stuck here in while loop
        delay(1);
        i++;
        if(i > UART_WAIT) {
			UartError++;
			break;
		}
    }
        		#ifndef LAB_TEST_DEVICE
				Serial.print("b");
				#endif

    if (Serial1.available()){
        Serial1.readBytes(start,1);
        i=0;
        while (start[0]!=0xAA){
            Serial1.readBytes(start,1);
            delay(1);
            i++;
             if(i > UART_WAIT) {
				UartError++;
				break;
			}
        }
        Serial1.readBytes(data,9);
        checksum=(int)data[1]+(int)data[2]+(int)data[3]+(int)data[4]+(int)data[5]+(int)data[6];
    }
        		#ifndef LAB_TEST_DEVICE
				Serial.print("c");
				#endif

    if ((unsigned char)checksum==data[7]){             //chenll,has to change the type before comparing.
        RawValue.PM25=(((float)data[2])*256+(float)data[1])/10;
    //    PM10=(((float)data[4])*256+(float)data[3])/10;
        		#ifndef LAB_TEST_DEVICE
     			Serial.print(" PM Ok   ");
     			#endif

        PMSuccess++;
    }
    else{
        PMFail++;
   //     Serial.print(" PM Fail ");
    }




#ifdef DEBUG
    Serial.print("PM :");
    Serial.print(start[0],HEX);Serial.print(".");
    Serial.print(data[0],HEX);Serial.print(".");
    Serial.print(data[1],HEX);Serial.print(".");
    Serial.print(data[2],HEX);Serial.print(".");
    Serial.print(data[3],HEX);Serial.print(".");
    Serial.print(data[4],HEX);Serial.print(".");
    Serial.print(data[5],HEX);Serial.print(".");
    Serial.print(data[6],HEX);Serial.print(".");
    Serial.print(data[7],HEX);Serial.print(".");
    Serial.print(data[8],HEX);Serial.print(".");
    Serial.print("//");
    Serial.print(checksum,HEX);

    if(checksum == data[7]){
        Serial.print("==");
    }
    else{
        Serial.print("xx");
    }

    Serial.print(data[7],HEX);
    Serial.print("//");
#endif

}


//unsigned char NoiseSensCounter = 0;
//unsigned int NoiseSensAv = 0;
//float MaxNoise[6];



/*
void NoiseReset(){
	PrevNoiseRead = 0;
	Noise = 0;
//	Serial.print("PrevRead");Serial.print(PrevNoiseRead);Serial.print("Noise");Serial.println(Noise);
}

void NoiseRepRead(){
	float temp = noise.readNoise();
	if(temp > PrevNoiseRead) Noise = temp;
	PrevNoiseRead = temp;
//	Serial.print("Noise");Serial.println(Noise);
}
*/

void G_SensorRead(void){
	GSensor.begin();
	delay(10);
	Accx = GSensor.readXData()/65.0;
	delay(10);
 	Accy = GSensor.readYData()/65.0;
  	delay(10);
 	Accz = GSensor.readZData()/65.0;
 	delay(10);
   // Calculate pitch and roll. Find the maximum tilt angle.
  	AccPitch = atan(Accx / sqrt(Accy * Accy + Accz * Accz))*180;
  	AccRoll = atan(Accy / sqrt(Accx * Accx + Accz * Accz))*180;
  	AccmaxTilt = max(abs(AccRoll), abs(AccPitch)) / 3.14159;
}

void G_SensorPrint(void){

//  Accx = GSensor.readXData()/65.0;
  Serial.print("Accel X: ");
  Serial.print(Accx);

//  Accy = GSensor.readYData()/65.0;
  Serial.print(", Y: ");
  Serial.print(Accy);

//  Accz = GSensor.readZData()/65.0;
  Serial.print(", Z: ");
  Serial.print(Accz);
/*
  // Calculate pitch and roll. Find the maximum tilt angle.
  AccPitch = atan(Accx / sqrt(Accy * Accy + Accz * Accz))*180;
  AccRoll = atan(Accy / sqrt(Accx * Accx + Accz * Accz))*180;
  AccmaxTilt = max(abs(AccRoll), abs(AccPitch)) / 3.14159;
*/
  Serial.print("  pitch: ");
  Serial.print(AccPitch);
  Serial.print(" roll: ");
  Serial.print(AccRoll);
  Serial.print(" maxTilt: ");
  Serial.print(AccmaxTilt);
}

void GSensorActions(){
	#ifdef NO_SENSOR
			return;
  	#endif

	int i;
	G_SensorRead();
	Tilt.Current = (int)(AccmaxTilt);
	if(Tilt.Calibrated == false){
	//	Tilt.Moved = false;
		GSensorArr[Tilt.index] = Tilt.Current;
		Serial.print("   Tilt.index : ");Serial.print(Tilt.index);
		if((Tilt.index) == (GSENSORTASK_MAX)){
			PrintTiltUnsorted(GSENSORTASK_MAX);

			IntSortArray(&GSensorArr[0],GSENSORTASK_MAX);

			PrintTiltSorted(GSENSORTASK_MAX);

			Tilt.Average = IntGetAverageG(&GSensorArr[0],GSENSORTASK_MAX);
			Tilt.Positive = Tilt.Average - GSensorArr[0];
			Tilt.Negative  = GSensorArr[GSENSORTASK_MAX] - Tilt.Average;

			Serial.println();
			Serial.print("Average");
			Serial.print("  GSensor:");Serial.print(Tilt.Average);
			Serial.print("  GMax:");Serial.print(Tilt.Positive);
			Serial.print("  GMin:");Serial.print(Tilt.Negative);
			Serial.print("  Tresh:");Serial.print(CALIB_LIMITS);

			if((Tilt.Positive < CALIB_LIMITS) & (Tilt.Negative < CALIB_LIMITS))Tilt.Calibrated = true;
		}
		Tilt.index++;
		if(Tilt.index > GSENSORTASK_MAX) Tilt.index = 0;
	}
	else {
		int Diff = Tilt.Average - Tilt.Current;
		 Diff = abs(Diff);
		Serial.print("Diff: ");Serial.print(Diff);
		if(Diff >= MOVE_TRESHOLD){
			if(PushNotification.OnDemandTimer == 0){
				PushNotification.Tilt = true;
				PushNotification.OnDemandTimer = 1;
			}
		//	if(Tilt.TweetTimer==0)Tilt.TweetTimer = 1;
		//	else Tilt.TweetTimer = 30;
			Tilt.Moved = true;;
			SetBeepOn();delay(30);SetBeepOff();
			Tilt.index = 0;
			Tilt.Calibrated = false;
			Tilt.LedTimer = 4;
			LedStatus.Tilt = true;// set priority
		}
	}
	if(Tilt.Calibrated == true)Serial.print("       Calibration OK! : ");
	else Serial.print("   Non Calibrated! : ");

	Serial.print("    Move : ");Serial.print(Tilt.Current);// Serial.print("    Timer : ");Serial.print(Tilt.BlockTimer);

	if(Tilt.Moved== true){
		Tilt.Moved = false;
		Serial.print("          Move!");
	}
	Serial.println();

}

void Barometer_Measure(void){
	barometer.begin();
	BarometerApp();
	// https://www.britannica.com/science/atmospheric-pressure
	// drop 3.5mbar every 30 metres @ 100meters = 1000/30 = 33 times
	// 1000 metres 115.5 mbr drop
	// 101325 - 11550 = 89775 at 1000 mt
	#define MAX_PRESS_AT_SEALVL  105000    // 101300 sea level
	#define MIN_PRESS_ABV_SEALVL  98000 // @ 1000 meter height

//	http://www.theweatherprediction.com/habyhints2/410/

	if(RawValue.Pressure > MAX_PRESS_AT_SEALVL)RawValue.Pressure = MAX_PRESS_AT_SEALVL;
 	if(RawValue.Pressure < MIN_PRESS_ABV_SEALVL)RawValue.Pressure = MIN_PRESS_ABV_SEALVL;


  		#ifndef LAB_TEST_DEVICE
   		Serial.print("                                   Pressure.abs(hPa)(mbar)=");
  		Serial.print(RawValue.Pressure);
  		#endif
}

void SensorActions_OddTask(){
	#ifdef NO_SENSOR
		return;
  	#endif

  	Barometer_Measure();

}
void GSensorReset(){


//AccmaxTilt

}
  double sealevel(double P, double A)
// Given a pressure P (Pa) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
  return((P/100)/pow(1-(A/44330.0),5.255));
}


double altitude(double P, double P0)
// Given a pressure measurement P (Pa) and the pressure at a baseline P0 (Pa),
// return altitude (meters) above baseline.
{
  return(44330.0*(1-pow(P/P0,1/5.255)));
}
void BarometerApp(void){
  // Read temperature from the sensor in deg C. This operation takes about
  // 4.5ms to complete.
//  temperature_c = barometer.getTemperature(CELSIUS);

  // Read temperature from the sensor in deg F. This operation takes about
  // 4.5ms to complete. Converting to Fahrenheit is not internal to the sensor.
  // Additional math is done to convert a Celsius reading.
//  temperature_f = barometer.getTemperature(FAHRENHEIT);

  // Read pressure from the sensor in Pa. This operation takes about
  // 67ms to complete in ULTRA_MODE.  Other Modes are available for faster, yet
  // less precise measurements.
  // MODE_LOW      = 5 ms
  // MODE_STANDARD = 11 ms
  // MODE_HIGH     = 19 ms
  // MODE_ULTRA    = 67 ms

  //pressure_abs  = barometer.getPressure(MODE_ULTRA);
 /*
  PressureLong  = (long)barometer.getPressure(MODE_ULTRA);
  Serial.print(" Pressure.abs(hPa)(mbar)=");
  Serial.println(PressureLong);
*/

  RawValue.Pressure  = barometer.getPressure(MODE_ULTRA);


  // Let's do something interesting with our data.

  // Convert abs pressure with the help of altitude into relative pressure
  // This is used in Weather stations.



//  pressure_relative = sealevel(pressure_abs, base_altitude);

  // Taking our baseline pressure at the beginning we can find an approximate
  // change in altitude based on the differences in pressure.



//  altitude_delta = altitude(pressure_abs , pressure_baseline);

//    sealevel  = sealevel(pressure_abs, base_altitude);

  // Report values via UART
/*

  Serial.print("Temp.= ");
  Serial.print(temperature_c / 100);Serial.print("'C");


  Serial.print(" Pressure.abs(hPa)(mbar)=");
  Serial.print(pressure_abs);Serial.print("  ");
  Serial.print(pressure_abs/100,2);




  Serial.print("  Pressure relative (hPa)= ");
  Serial.print(pressure_relative,1);

  Serial.print("Altitude change (m) = ");
  Serial.println(altitude_delta,2);
*/


//  Serial.print(" Sea Level (m) = ");
//  Serial.println(altitude_delta,2);

}


void SensorsSetLimits(void){
 	if(RawValue.Temperature > MAX_Temperature)RawValue.Temperature = MAX_Temperature;
 	if(RawValue.Temperature < MIN_Temperature)RawValue.Temperature = MIN_Temperature;
 	if(RawValue.Humidity > MAX_Humidity)RawValue.Humidity = MAX_Humidity;
 	if(RawValue.Humidity < MIN_Humidity)RawValue.Humidity = MIN_Humidity;

 	if(IAQ.TVOC > MAX_TVOC)IAQ.TVOC = MAX_TVOC;
 	if(IAQ.eCO2 > MAX_CO2)IAQ.eCO2 = MAX_CO2;
 	if(RawValue.CO2 > MAX_CO2)RawValue.CO2 = MAX_CO2;


 	if(IAQ.TVOC < MIN_TVOC)IAQ.TVOC = MIN_TVOC;
 	if(IAQ.eCO2 < MIN_CO2)IAQ.eCO2 = MIN_CO2;
 	if(RawValue.CO2 <  MIN_CO2)RawValue.CO2 = MIN_CO2;

 	if(RawValue.PM25 > MAX_PM25)RawValue.PM25 = MAX_PM25;
 	if(RawValue.PM25 < MIN_PM25)RawValue.PM25 = MIN_PM25;

 	if(RawValue.Light > MAX_LIGHT)RawValue.Light = MAX_LIGHT;
 	if(RawValue.Light < MIN_LIGHT)RawValue.Light = MIN_LIGHT;

// 1013 mbar se level max

}
void SensorActions(){
		unsigned char i;
		unsigned char test;
	#ifdef NO_SENSOR
		return;
  	#endif




		#ifdef TSL2591_LIGHT_NEW
			tsl.begin(); // TSL2591
        #endif
		#ifdef TSL2561_LIGHT_OLD
        	al_sensor.begin(); //TSL2561
        #endif

        rh_sensor.begin();                    //note: need to initialize again

 //  SurfaceTemp= tmp006.readDieTempC();
					float Temp_ErrorCorection = 3.0;
        RawValue.Temperature = rh_sensor.readTemperature() - Temp_ErrorCorection;
			#ifndef LAB_TEST_DEVICE
        	Serial.print("Temp:");Serial.print(RawValue.Temperature);Serial.print("'C ");
  			#endif
  			#ifdef LAB_TEST_DEVICE
  			delay(10);

  			#endif

        RawValue.Humidity = rh_sensor.readHumidity();


			#ifndef LAB_TEST_DEVICE
        	Serial.print("Humd:%");Serial.print(RawValue.Humidity);Serial.print(" ");
  			#endif
  			#ifdef LAB_TEST_DEVICE
  			delay(10);

  			#endif


		#ifdef TSL2591_LIGHT_NEW
			RawValue.Light = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
        #endif
		#ifdef TSL2561_LIGHT_OLD

        	RawValue.Light = al_sensor.readVisAndIR();// TSL2561 //Serial.print("Light:" + String(RawValue.Light)+" Lux ");  //get data from TSL2561 sensor
        #endif

			#ifndef LAB_TEST_DEVICE
        	Serial.print("Light:"); Serial.print(RawValue.Light);Serial.print("Lux ");
  			#endif
  			#ifdef LAB_TEST_DEVICE
  			delay(10);

  			#endif


        IAQSensorApp();//Serial.print("TVOC:" + String(IAQ.TVOC)+ "ppb eCO2:"+  String(IAQ.eCO2)+ "ppm ");



			#ifndef LAB_TEST_DEVICE
			Serial.print("TVOC:");
			Serial.print(IAQ.TVOC);Serial.print("ppb eCO2:");
			Serial.print(IAQ.eCO2);Serial.print("ppm ");
  			#endif
  			#ifdef LAB_TEST_DEVICE
  			delay(10);

			#endif



  	#ifndef SENSEAIR_CO2_INSTALLED
           readPMconc();
 	#endif

 	#ifdef SENSEAIR_CO2_INSTALLED
        readCO2SenseAir();
 	#endif


 			#ifndef LAB_TEST_DEVICE
 				Serial.print(RawValue.PM25);  Serial.print("ug/m3 ");              //chenll,fordebug
 		//		Serial.print("C02:");Serial.print(RawValue.CO2);Serial.print("ppm ");
  			#endif
  			#ifdef LAB_TEST_DEVICE
  			delay(10);

  			#endif
//////////  <MutichannelGasSensor.h>
    delay(10);
    gas.begin(0x04);//the default I2C address of the slave is 0x04
 //   gas.powerOn();
	 delay(10);
    RawValue.Ammonia = gas.measure_NH3();

  //  RawValue.CO = gas.measure_CO();

  //      Serial.print("Firmware Version = ");
 //       Serial.println(gas.getVersion());

 //  		Serial.print("    Surf. Temp: ");Serial.print(SurfaceTemp);

		float temp = noise.readNoise();	//Serial.print("Noise:" + String(temp)+ "dB ");

		#ifndef LAB_TEST_DEVICE
		Serial.print("Noise:");Serial.print(temp);Serial.print("dB ");
 		#endif

		if(temp > Noise) Noise = temp;
		if(Task == 0) Noise = 0;

		#ifndef LAB_TEST_DEVICE
		    Serial.print(" Err:");Serial.print(UartError);
		    Serial.print(" Fail:");Serial.print(PMFail);
			Serial.print(" OK:");Serial.print(PMSuccess);
		#endif


		SensorsSetLimits();


#ifndef LAB_TEST_DEVICE
		Serial.println();
		Serial.print(" Name:");
		Serial.print(Device[DEVICEID]);
		Serial.print(" Temp:");
		Serial.print(RawValue.Temperature);
		Serial.print(" Humid:");
		Serial.print(RawValue.Humidity);
		Serial.print(" Light:");
		Serial.print(RawValue.Light);
		Serial.print(" TVOC:");
		Serial.print(IAQ.TVOC);
		Serial.print(" CO2:");
		Serial.print(IAQ.eCO2);
		Serial.print(" PM25:");
		Serial.print(RawValue.PM25);
		Serial.print(" Noise:");
		Serial.print(Noise);
		Serial.print(" Pressure:");
		Serial.print(RawValue.Pressure);
    	Serial.print(" Ammonia(NH3):"); //  Main Sensor1 1-500 ppm
		Serial.print(RawValue.Ammonia);
    	Serial.print(" CO:"); //  // Main Sensor2 //RED 1-1000 ppm
		Serial.print(RawValue.CO);

#endif

 // 	String username = "mobile0";
 // 	String password = "mobile0pass";
  	char Separator = ','; // put at the end of any updated value
				// Trend Up:1 Stable:0 Down:-1
  //	String data ="{\"username\":\""+username+"\",\"password\":\""+password+"\",\"data\":{";

  //	String data ="\"data\":{";
  	String data ="{";
		data += "\"a\":";data += String(IAQ.TVOC);	 data += Separator;
  		data += "\"b\":";data += Float2Str_OneDigExp(RawValue.Temperature);data +=Separator;
  		data += "\"c\":";data += Float2Str_OneDigExp(RawValue.Humidity);data +=Separator;
#ifndef SENSEAIR_CO2_INSTALLED
		data += "\"d\":";data += String(IAQ.eCO2);data +=Separator;
#endif
#ifdef SENSEAIR_CO2_INSTALLED
		data += "\"d\":";data += String(Filtered.CO2_Absolute);data +=Separator;
#endif
  		data += "\"e\":";data += Float2Str_OneDigExp(RawValue.PM25);data +=Separator;
  		JsonCounter++;
  		data += "\"f\":";data += String(JsonCounter);data +=Separator;
  		data += "\"g\":";data += String(RawValue.Light);data +=Separator;
  		data += "\"h\":";data += Float2Str_OneDigExp(Noise);data +=Separator;
  		data += "\"i\":";data += Float2Str_OneDigExp(RawValue.Pressure/100);data +=Separator;
	//	data += "\"j\":";data += String(IAQ.CO2e);data +=Separator;
  		data += "\"device\":";
		data +="\""+String(Device[DEVICEID])+"\"";// device;
 // 		data += "}}\r\n\r\n";
  		data += "},\r\n";
  		Serial.print(data);



// Name:device1 Temp:23.5 Humid:45.3
		unsigned char SensorIndex = Task/2;
		// fill the array




		CO2_AbsoluteArr[SensorIndex] =  RawValue.CO2;
		TempArr[SensorIndex] = RawValue.Temperature;
		HumArr[SensorIndex] = RawValue.Humidity;
		PMArr[SensorIndex] = RawValue.PM25;
		VOCArr[SensorIndex] = IAQ.TVOC;
		CO2eArr[SensorIndex] = IAQ.eCO2;
		LightArr[SensorIndex] = RawValue.Light;
//		PressureArr[SensorIndex] = PressureLong;
		PressureArr[SensorIndex] = RawValue.Pressure;
		// if array is at max go for sorting and averging
		if((SensorIndex*2) == (TASK_MAX-1)){// 0,2.4. .... 58 total 30
			Filtered.Noise = Noise;
				#ifdef PRINT_SENSOR_TABLE
			PrintUnsortedValues(SensorIndex);
				#endif
			FloatSortArray(&TempArr[0],SensorIndex);
			FloatSortArray(&HumArr[0],SensorIndex);
			FloatSortArray(&PMArr[0],SensorIndex);
			IntSortArray(&VOCArr[0],SensorIndex);
			IntSortArray(&CO2eArr[0],SensorIndex);
			IntSortArray(&CO2_AbsoluteArr[0],SensorIndex);
			UintSortArray(&LightArr[0],SensorIndex);


//			LongSortArray(&PressureArr[0],SensorIndex);
			FloatSortArray(&PressureArr[0],SensorIndex);
				#ifdef PRINT_SENSOR_TABLE
			PrintSortedValues(SensorIndex);
				#endif
			Filtered.PrevTemperature = Filtered.Temperature;
			Filtered.PrevHumidity = Filtered.Humidity;
			Filtered.PrevPM25 = Filtered.PM25;
			Filtered.PrevTVOC = Filtered.TVOC;
			Filtered.PrevCO2e = Filtered.CO2e;
			Filtered.PrevCO2_Absolute = Filtered.CO2_Absolute;
			Filtered.PrevLight = Filtered.Light;
			Filtered.PrevPressure = Filtered.Pressure;



			Filtered.Temperature = FloatGetAverage(&TempArr[0],SensorIndex);
			Filtered.Humidity = FloatGetAverage(&HumArr[0],SensorIndex);
			Filtered.PM25 = FloatGetAverage(&PMArr[0],SensorIndex);
			Filtered.TVOC = IntGetAverage(&VOCArr[0],SensorIndex);
			Filtered.CO2e = IntGetAverage(&CO2eArr[0],SensorIndex);
			Filtered.CO2_Absolute = IntGetAverage(&CO2_AbsoluteArr[0],SensorIndex);
			Filtered.Light = UintGetAverage(LightArr,SensorIndex);
			Filtered.Pressure = FloatGetAverage(PressureArr,SensorIndex);

			String_Temperature = Float2Str_OneDigExp(Filtered.Temperature);
			String_Humidity    = String((unsigned char)Filtered.Humidity);
			String_Pressure    = String((unsigned int)(Filtered.Pressure/100));
			String_Light       = String(Filtered.Light);
			String_PM25		   = Float2Str_OneDigExp(Filtered.PM25);
			String_TVOC		   = String(Filtered.TVOC);
			String_CO2e		   = String(Filtered.CO2e);
			String_Noise       = Float2Str_OneDigExp(Filtered.Noise);
			SensorDataReady2Send = true; // release to send data 2 Cloud

					#ifdef PRINT_SENSOR_TABLE
			PrintIAQFinalLelevels();
					#endif
			IAQ_Level_Calculation();
					#ifdef PRINT_SENSOR_TABLE
			PrintIAQFinalLelevels();
					#endif
			IAQ_Trend_Calculation();
				#ifdef PRINT_SENSOR_TABLE
			PrintFilteredAverageValues();
				#endif
			LedStatus.IAQStatus = true;
	}
}
unsigned char Hum_Check(void){
	     if(Filtered.Humidity > HUMH_HAZARDOUS){SM_Warnings.Humidity = HIGH_EXT; return HAZARDOUS;}
	else if(Filtered.Humidity < HUML_HAZARDOUS){SM_Warnings.Humidity = LOW_EXT; return HAZARDOUS;}

	else if(Filtered.Humidity > HUMH_UNHEALTHY){SM_Warnings.Humidity = HIGH_VERY; return UNHEALTHY;}
	else if(Filtered.Humidity < HUML_UNHEALTHY){SM_Warnings.Humidity = LOW_VERY; return UNHEALTHY;}

	else if(Filtered.Humidity > HUMH_RISKY){SM_Warnings.Humidity = HIGH_TOO; return RISKY;}
	else if(Filtered.Humidity < HUML_RISKY){SM_Warnings.Humidity = LOW_TOO; return RISKY;}

	else if(Filtered.Humidity > HUMH_MODERATE){SM_Warnings.Humidity = HIGH_ABIT; return MODERATE;}
	else if(Filtered.Humidity < HUML_MODERATE){SM_Warnings.Humidity = LOW_ABIT; return MODERATE;}

	else SM_Warnings.Humidity = ITS_OK; return HEALTHY;
}
unsigned char Temp_Check(void){

		 if(Filtered.Temperature > TEMPH_HAZARDOUS){SM_Warnings.Temperature = HIGH_EXT;return HAZARDOUS;} //12
	else if(Filtered.Temperature < TEMPL_HAZARDOUS){SM_Warnings.Temperature = LOW_EXT;return HAZARDOUS;} //11

	else if(Filtered.Temperature > TEMPH_UNHEALTHY){SM_Warnings.Temperature = HIGH_VERY;return UNHEALTHY;}
	else if(Filtered.Temperature < TEMPL_UNHEALTHY){SM_Warnings.Temperature = LOW_VERY;return UNHEALTHY;}

	else if(Filtered.Temperature > TEMPH_RISKY){SM_Warnings.Temperature = HIGH_TOO;return RISKY;}
	else if(Filtered.Temperature < TEMPL_RISKY){SM_Warnings.Temperature = LOW_TOO;return RISKY;}

	else if(Filtered.Temperature > TEMPH_MODERATE){SM_Warnings.Temperature = HIGH_ABIT;return MODERATE;}
	else if(Filtered.Temperature < TEMPL_MODERATE){SM_Warnings.Temperature = LOW_ABIT;return MODERATE;}

	else SM_Warnings.Temperature = ITS_OK; return HEALTHY;
}
unsigned char PM25_Check(void){

	     if(Filtered.PM25 > PM25_HAZARDOUS)return HAZARDOUS;
	else if(Filtered.PM25 > (PM25_HAZARDOUS-PM25_HYST_HAZARDOUS)){if(IAQ_Health[QUE_PM25]==HAZARDOUS)return HAZARDOUS;}

	else if(Filtered.PM25 > PM25_UNHEALTHY)return UNHEALTHY;
	else if(Filtered.PM25 > (PM25_UNHEALTHY-PM25_HYST_UNHEALTH)){if(IAQ_Health[QUE_PM25]==UNHEALTHY)return UNHEALTHY;}

	else if(Filtered.PM25 > PM25_RISKY)return RISKY;
	else if(Filtered.PM25 > (PM25_RISKY-PM25_HYST_RISKY)){if(IAQ_Health[QUE_PM25]==RISKY)return RISKY;}

	else if(Filtered.PM25 > PM25_MODERATE)return MODERATE;
	else if(Filtered.PM25 > (PM25_MODERATE-PM25_HYST_MODERATE)){if(IAQ_Health[QUE_PM25]==MODERATE)return MODERATE;}
	else return HEALTHY;
}


//TVOC_Trend=DECREASE;
//TVOC_Trend=INCREASE;

unsigned char TVOC_Check(void){
	if(LedStatus.AMS_Ok == false)return HEALTHY;
	     if(Filtered.TVOC > TVOC_HAZARDOUS)return HAZARDOUS;
	else if(Filtered.TVOC > (TVOC_HAZARDOUS-TVOC_HYSTERESIZ)){if(IAQ_Health[QUE_VOC]==HAZARDOUS)return HAZARDOUS;}

	else if(Filtered.TVOC > TVOC_UNHEALTHY)return UNHEALTHY;
	else if(Filtered.TVOC > (TVOC_UNHEALTHY-TVOC_HYSTERESIZ)){if(IAQ_Health[QUE_VOC]==UNHEALTHY)return UNHEALTHY;}

	else if(Filtered.TVOC > TVOC_RISKY)return RISKY;
	else if(Filtered.TVOC > (TVOC_RISKY-TVOC_HYSTERESIZ)){if(IAQ_Health[QUE_VOC]==RISKY)return RISKY;}

	else if(Filtered.TVOC > TVOC_MODERATE)return MODERATE;
	else if(Filtered.TVOC > (TVOC_MODERATE-TVOC_HYSTERESIZ)){if(IAQ_Health[QUE_VOC]==MODERATE)return MODERATE;}
	else return HEALTHY;
}
unsigned char CO2_Check(int Value){
	if(LedStatus.AMS_Ok == false)return HEALTHY;
	     if(Value > CO2e_HAZARDOUS)return HAZARDOUS;
	else if(Value > (CO2e_HAZARDOUS-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==HAZARDOUS)return HAZARDOUS;}

	else if(Value > CO2e_UNHEALTHY)return UNHEALTHY;
	else if(Value > (CO2e_UNHEALTHY-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==UNHEALTHY)return UNHEALTHY;}

	else if(Value > CO2e_RISKY)return RISKY;
	else if(Value > (CO2e_RISKY-CO2e_HYSTERESIZ))   {if(IAQ_Health[QUE_CO2]==RISKY)return RISKY;}

	else if(Value > CO2e_MODERATE)return MODERATE;
	else if(Value > (CO2e_MODERATE-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==MODERATE)return MODERATE;}
	else return HEALTHY;
}
/*
char eCO2_TrendCheck(void){
	if(LedStatus.AMS_Ok == false)return HEALTHY;

	     if(Value > CO2e_HAZARDOUS)return HAZARDOUS;
	else if(Value > (CO2e_HAZARDOUS-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==HAZARDOUS)return HAZARDOUS;}

	else if(Value > CO2e_UNHEALTHY)return UNHEALTHY;
	else if(Value > (CO2e_UNHEALTHY-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==UNHEALTHY)return UNHEALTHY;}

	else if(Value > CO2e_RISKY)return RISKY;
	else if(Value > (CO2e_RISKY-CO2e_HYSTERESIZ))   {if(IAQ_Health[QUE_CO2]==RISKY)return RISKY;}

	else if(Value > CO2e_MODERATE)return MODERATE;
	else if(Value > (CO2e_MODERATE-CO2e_HYSTERESIZ)){if(IAQ_Health[QUE_CO2]==MODERATE)return MODERATE;}
	else return HEALTHY;
}´
*/
void IAQ_Level_Calculation(void){
	IAQ_Health[QUE_PM25] = PM25_Check();
	IAQ_Health[QUE_TEMP] = Temp_Check();
	IAQ_Health[QUE_HUMD] = Hum_Check();
	IAQ_Health[QUE_VOC] = TVOC_Check();

	switch(IAQ_Health[QUE_PM25]){
		case HEALTHY : SM_Warnings.Dust = HEALTHY;
		break;
		case MODERATE :SM_Warnings.Dust = HIGH_ABIT;
		break;
		case RISKY :SM_Warnings.Dust =    HIGH_TOO;
		break;
		case UNHEALTHY :SM_Warnings.Dust = HIGH_VERY;
		break;
		case HAZARDOUS :SM_Warnings.Dust = HIGH_EXT;
		break;
		default :SM_Warnings.Dust = ITS_OK;
		break;
	}
		#ifndef SENSEAIR_CO2_INSTALLED
			IAQ_Health[QUE_CO2] = CO2_Check(Filtered.CO2e);
		#endif
		#ifdef SENSEAIR_CO2_INSTALLED
			IAQ_Health[QUE_CO2] = CO2_Check(Filtered.CO2_Absolute);
		#endif
	SortChar(&IAQ_Health[0], 5);
	Filtered.IAQ = IAQ_Health[4];
	switch(Filtered.IAQ){
		case HEALTHY : IAQstr =  "Healthy :) ";
		break;
		case MODERATE :IAQstr = "Moderate :| ";
		break;
		case RISKY :IAQstr =    "Unpleasant :( ";
		break;
		case UNHEALTHY :IAQstr ="Unhealthy :( ";
		break;
		case HAZARDOUS :IAQstr ="Hazardous :o ";
		break;
		default :IAQstr = "What :-]";
		break;
	}

	switch(SM_WarningsCall()){
		case HIGH_EXT : SM_Problem = "Extreme High "; //13
			break;
		case LOW_EXT  : SM_Problem = "Extreme Low "; //12
			break;
		case HIGH_VERY :SM_Problem = "Very High "; //9
			break;
		case LOW_VERY  :SM_Problem = "Very Low "; //8
			break;
		case HIGH_TOO  :SM_Problem = "Too High "; //8
			break;
		case LOW_TOO   :SM_Problem = "Too Low "; //7
			break;
		case HIGH_ABIT :SM_Problem = "A Bit High "; //10
			break;
		case LOW_ABIT  :SM_Problem = "A Bit Low "; //9
			break;
		case ITS_OK   :SM_Problem = " "; //9
		break;
	}
	switch(SM_Warnings.Dominant){
		case DOM_NONE : 		SM_ProbType = " ";
			break;
		case DOM_TEMPERATURE : SM_ProbType = "Temperature is ";
			break;
		case DOM_HUMIDITY :  SM_ProbType =  "Humidity is ";
			break;
		case DOM_DUST :  SM_ProbType =  "Dust Level is ";
			break;
	}
}



void IAQ_Trend_Calculation(void){
	float Polf; int Poli;
	if(Filtered.TrendInit == false){
		Filtered.TrendInit = true;
		Filtered.PrevTemperature = Filtered.Temperature;
		Filtered.PrevHumidity = Filtered.Humidity;
		Filtered.PrevPM25 = Filtered.PM25;
		Filtered.PrevTVOC = Filtered.TVOC;
		Filtered.PrevCO2e = Filtered.CO2e;
		Filtered.PrevCO2_Absolute = Filtered.CO2_Absolute;
		Filtered.PrevLight = Filtered.Light;
		Filtered.PrevNoise = Filtered.Noise;
		Filtered.PrevPressure = Filtered.Pressure;
	}
	Polf = Filtered.Temperature - Filtered.PrevTemperature;
	if(abs(Polf)> TREND_TEMP_HYST){
		if(Filtered.Temperature > Filtered.PrevTemperature) Filtered.Temperature_Trend = INCREASE;
		else Filtered.Temperature_Trend = DECREASE;
	}
	else Filtered.Temperature_Trend = STABLE;

	Polf = Filtered.Humidity - Filtered.PrevHumidity;
	if(abs(Polf)> TREND_HUM_HYST){
		if(Filtered.Humidity > Filtered.PrevHumidity) Filtered.Humidity_Trend = INCREASE;
		else Filtered.Humidity_Trend = DECREASE;
	}
	else Filtered.Humidity_Trend = STABLE;

	Polf = Filtered.PM25 - Filtered.PrevPM25;
	if(abs(Polf)> TREND_PM25_HYST){
		if(Filtered.PM25 > Filtered.PrevPM25) Filtered.PM25_Trend = INCREASE;
		else Filtered.PM25_Trend = DECREASE;
	}
	else Filtered.PM25_Trend = STABLE;

	Poli = Filtered.TVOC - Filtered.PrevTVOC;
	if(abs(Poli)> TREND_VOC_HYST){
		if(Filtered.TVOC > Filtered.PrevTVOC) Filtered.TVOC_Trend = INCREASE;
		else Filtered.TVOC_Trend = DECREASE;
	}
	else Filtered.TVOC_Trend = STABLE;

	Poli =Filtered.CO2e - Filtered.PrevCO2e;
	if(abs(Poli)> TREND_ECO2_HYST){
		if(Filtered.CO2e > Filtered.PrevCO2e) Filtered.CO2e_Trend = INCREASE;
		else Filtered.CO2e_Trend = DECREASE;
	}
	else Filtered.CO2e_Trend = STABLE;

	Poli =Filtered.CO2_Absolute - Filtered.PrevCO2_Absolute;
	if(abs(Poli)> TREND_ECO2_HYST){
		if(Filtered.CO2_Absolute > Filtered.PrevCO2_Absolute) Filtered.CO2_Absolute_Trend = INCREASE;
		else Filtered.CO2_Absolute_Trend = DECREASE;
	}
	else Filtered.CO2_Absolute_Trend = STABLE;

	Poli =Filtered.Light - Filtered.PrevLight;
	if(abs(Poli)> TREND_LIGHT_HYST){
		if(Filtered.Light > Filtered.PrevLight) Filtered.Light_Trend = INCREASE;
		else Filtered.Light_Trend = DECREASE;
	}
	else Filtered.Light_Trend = STABLE;

	Polf = Filtered.Noise - Filtered.PrevNoise;
	if(abs(Polf)> TREND_NOISE_HYST){
		if(Filtered.Noise > Filtered.PrevNoise) Filtered.Noise_Trend = INCREASE;
		else Filtered.Noise_Trend = DECREASE;
	}
	else Filtered.Noise_Trend = STABLE;

	Poli = Filtered.Pressure - Filtered.PrevPressure;
	if(abs(Poli)> TREND_PRESSURE_HYST){
		if(Filtered.Pressure > Filtered.PrevPressure) Filtered.Pressure_Trend = INCREASE;
		else Filtered.Pressure_Trend = DECREASE;
	}
	else Filtered.Pressure_Trend = STABLE;

//	PrintIAQ_TrendValues();

}
unsigned char SM_WarningsCall(void){

		if(SM_Warnings.Dust == HIGH_EXT)       {SM_Warnings.Dominant = DOM_DUST;  SM_Advice = " Evacuate! I dont wanna miss u ";return HIGH_EXT;}
		if(SM_Warnings.Dust == HIGH_VERY)      {SM_Warnings.Dominant = DOM_DUST;  SM_Advice = " Get out your lung matters! ";return HIGH_VERY;}
		if(SM_Warnings.Dust == HIGH_TOO)       {SM_Warnings.Dominant = DOM_DUST;  SM_Advice = " Do something I care you! ";return HIGH_TOO;}


		if(SM_Warnings.Temperature == HIGH_EXT) {SM_Warnings.Dominant = DOM_TEMPERATURE; SM_Advice = " Hey this is not a Sauna! "; return HIGH_EXT;}
		if(SM_Warnings.Humidity    == HIGH_EXT) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " Extreme Humid Any Window! ";return HIGH_EXT;}

		if(SM_Warnings.Temperature == LOW_EXT) {SM_Warnings.Dominant = DOM_TEMPERATURE; SM_Advice = " Freezing to death U sure? "; return LOW_EXT;}
		if(SM_Warnings.Humidity    == LOW_EXT) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " Dont you swell ? ";return LOW_EXT;}


		if(SM_Warnings.Temperature == HIGH_VERY) {SM_Warnings.Dominant = DOM_TEMPERATURE;SM_Advice = " You enjoy sweating! "; return HIGH_VERY;}
		if(SM_Warnings.Humidity    == HIGH_VERY) {SM_Warnings.Dominant = DOM_HUMIDITY;   SM_Advice = " "; return HIGH_VERY;}

		if(SM_Warnings.Temperature == LOW_VERY) {SM_Warnings.Dominant = DOM_TEMPERATURE;  SM_Advice = " Cool Hope u are exercising! ";return LOW_VERY;}
		if(SM_Warnings.Humidity    == LOW_VERY) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " Getting dry You have a window? ";return LOW_VERY;}


		if(SM_Warnings.Temperature == HIGH_TOO) {SM_Warnings.Dominant = DOM_TEMPERATURE; SM_Advice = " Dont U Think It's Hot! ";return HIGH_TOO;}
		if(SM_Warnings.Humidity    == HIGH_TOO) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " ";return HIGH_TOO;}


		if(SM_Warnings.Temperature == LOW_TOO) {SM_Warnings.Dominant = DOM_TEMPERATURE; SM_Advice = " You Wanna Get Sick? "; return LOW_TOO;}
		if(SM_Warnings.Humidity    == LOW_TOO) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " It's dry You have a window? ";return LOW_TOO;}

		if(SM_Warnings.Dust == HIGH_ABIT)        {SM_Warnings.Dominant = DOM_DUST;  SM_Advice = " Did U Clean The Room? ";return HIGH_ABIT;}

		if(SM_Warnings.Temperature == HIGH_ABIT) {SM_Warnings.Dominant = DOM_TEMPERATURE; SM_Advice = " It's time turn on the AC! ";return HIGH_ABIT;}
		if(SM_Warnings.Humidity    == HIGH_ABIT) {SM_Warnings.Dominant = DOM_HUMIDITY; SM_Advice = " It's a bit Humid!"; return HIGH_ABIT;}

		if(SM_Warnings.Temperature == LOW_ABIT) {SM_Warnings.Dominant = DOM_TEMPERATURE;  SM_Advice = " You are northerner! ";return LOW_ABIT;}
		if(SM_Warnings.Humidity    == LOW_ABIT) {SM_Warnings.Dominant = DOM_HUMIDITY;  SM_Advice = " Abit dry Like It? "; return LOW_ABIT;}

		SM_Warnings.Dominant = DOM_NONE;
		SM_Advice = " ";
		return ITS_OK;
}



/*
//-------------------
 void KeyPrc(void){
    KeyBuff = TouchKey1.ReadKey();

    if (KeyBuff != 0){         //has key
        if (KeyBuff != LastKeyBuff) {
            LastKeyBuff = KeyBuff;
            Timer.Buzzer = 1200;
            Timer.Fan = 15000;

            Test++;
            if ((Test&0x01) == 0) {
                IRSend1.StartCommand(AC_ELUX,TURN_ON);   //send a turn on command of Electrolux split AC
            }
            else {
                IRSend1.StartCommand(AC_ELUX,TURN_OFF);   //send a turn on command of Electrolux split AC
            }
        }
    }
    else{          //key free
        KeyBuff = 0;
        LastKeyBuff = 0;
    }
}

*/





