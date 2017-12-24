
void Phoenix_StartUp(void){
    Serial.begin(115200);
    CompilerInfo();PrintDeviceInfo();
    Leds_INIT();
    ColorSet(NOCOLOR);
    delay(10);
///////////////////////////// TSL2591


    GSensor.begin();delay(10);
    uint8_t GSensorID = GSensor.chipID();
    delay(10);
    Serial.print("GSensorchipID: ");
    Serial.println(GSensorID);

    delay(100);
    Simulation.ServerDisconnect = false;
    Simulation.WIFIDisconnect = false;
    pinMode(PUSH1, INPUT);delay(10);// SW3 on launcpad
    pinMode(PUSH2, INPUT);delay(10);// SW2 on launcpad
    // InitWifiStatic();
#ifndef LAB_TEST_DEVICE
    while(!InitWifi());// as long as no wifi found loop or exit by button sw2
    if(mode==AP_MODE)AP_Init();
    while(mode==AP_MODE)AP_UDP();
#endif
    LedStatus.IAQStatus = false;

    tmp006.begin();
    tmp006.wake();
    delay(10);

    #ifdef TSL2591_LIGHT_NEW
      if (tsl.begin())
        Serial.println(F("Found a TSL2591 sensor"));
      else
        Serial.println(F("No TSL2591 found ... check your wiring?"));

      displaySensorDetails();
      /* Configure the sensor */
      configureSensor();

    #endif
    #ifdef TSL2561_LIGHT_OLD
        al_sensor.begin();
    #endif

    rh_sensor.begin();
    IRSend1.Begin();

     barometer.begin();
        // Grab a baseline pressure for delta altitude calculation.
    pressure_baseline = barometer.getPressure(MODE_ULTRA);

   //----
    pinMode(FAN_PORT,OUTPUT);
    pinMode(BEEP_PORT,OUTPUT);
    SetFanOn();                     //fan always on
    Serial.print("setupEnd ");
    SetBeepOn();
    delay(50);
    SetBeepOff();

    PushNotification.RegularTimer = 5;

    RawValue.CO2 = 450; // default
    Filtered.Pressure = 101300;
    Filtered.PrevPressure - Filtered.Pressure;

    PrintDeviceInfo();Serial.println();Serial.println();
    #ifdef LAB_TEST_DEVICE
        Serial.println("LAB TEST DEVICE!!");Serial.println("[");

     #endif

  //  Serial2.begin(9600);
     Serial1.begin(9600);

       pinMode(TRY1_PORT,OUTPUT);
        TRy1_High();


}



void Phoenix_Loop(void){
  //(mode==STA_MODE)
      if(digitalRead(PUSH2)) Simulation.ServerDisconnect = true;
      if(!digitalRead(PUSH1)) Simulation.WIFIDisconnect = true;

//      Task1Sec = true;
      if(Task1Sec){
       Task1Sec = false;

        // beginning  of  comment out sensor task loop

       #ifndef LAB_TEST_DEVICE
       Serial.print("TaskNo ");Serial.print(Task);Serial.print("      ");
        GSensorActions();
        #endif
       TaskTimer = 0;
        if(Task == 1) {
          SensorActions_OddTask();   // 400mSec
              TRy1_High();
        }
        if(Task == 0) {
          SensorActions();   // 400mSec
            TRy1_Low();
        }
        else{
          if(Task != 1) {
              if((Task%2) == 0) {
                SensorActions();   // 400mSec
                TRy1_Low();

              }
              else{
                SensorActions_OddTask();
                  TRy1_High();

              }
          }

        }

       // end of  comment out sensor task loop
   //    Colorinc();
 //      ColorSet(ORANGE);


        switch(Task){
            case 0:
            break;
            case 1:
                #ifndef LAB_TEST_DEVICE
                  //      SendJson2Elux();
                  if( Config[CLOUD_ELUX] == "1"){
                     //Elux_HTTP_Json(POST_AUTHENTICATE_USER);
                  }
                  else Serial.print("    No:Elux");
                      #endif
            break;
            case 2 :
						 JsonPrep();


            break;
           case 3:

                  #ifndef LAB_TEST_DEVICE
                    CheckDataFail();
                    #endif

            break;
            case 4:
                  #ifndef LAB_TEST_DEVICE
                    CheckWIFIFail();
                    #endif


            break;
            case 5:
                //   Elux_HTTP_Json(GET_CURENT_VERSION);
            break;

            case 6:

            break;
            case 7:
                  #ifndef LAB_TEST_DEVICE
                  if( Config[GOOGLE_SEARCH] == "1"){
                     SendJson2Google();
                  }
                  else Serial.print("   No:Google");
                  #endif

            break;
            case 8:

            break;
            case 9:
                  //  MEDI_HTTP_Json(MEDI_POST_VALUES);
            break;
             case 10: //CompilerInfo();//PrintDeviceInfo();

            break;
            case 11: //Serial.print("Device0");Serial.print(Device[0]); Serial.print("Device1");Serial.println(Device[1]);
                //    PrintDeviceInfo();
            case 12:

            break;
            case 13:

            break;
            case 14:
						ATT_CLOUD();
            break;
             case 15:

            break;
            case 16:
					//	TweetApp();
            		/*
							char* p;
							p =  TweetMessage();
            				Serial.println(*p);

            				Serial.println();
            				for( int i = 0; p[i] != NULL; i++){
								Serial.print(" ");Serial.print(i);Serial.print(":");
								Serial.print(p[i]);
							}

					*/


            break;
            case 17:

            break;
            case 18:

            break;
            case 19:
                    #ifndef LAB_TEST_DEVICE
                      PushNotificationCheck();
                      #endif
            break;
             case 20:
            break;
            case 21:
                    #ifndef LAB_TEST_DEVICE
              if( Config[SEND_TWEET] == "1"){
                PushNotificationTweet();



              }
              else Serial.print("   No:Tweet");
                    #endif
            break;
            case 22:

            break;
            case 23:
                      #ifndef LAB_TEST_DEVICE
              if( Config[SEND_EMAIL] == "1"){
                PushNotificationEmail();
                }
                else Serial.print("   No:Email");
                    #endif
            break;
            case 24:

            break;
             case 25:
                 //   ChoerosFacebook();
            break;
             case 26:

            break;
            case 27:
                //    ChoerosFitbit();
            break;
            case 28:

            break;
            case 59:
                            #ifndef LAB_TEST_DEVICE
                          #ifdef TRIODOR_CLOUD
								JsonPrep2Send();
                              Cloud_Triodor();  // update there is change

                              LedStatus.CloudDataSent = true;

                              Cloud_Kepware();  //
                          #endif
                          Serial.println();
                        printWifiStatus();
                          #endif

                          #ifndef LAB_TEST_DEVICE
                          Serial.println();
                          CompilerInfo();PrintDeviceInfo();
                     #endif
            break;

            default:
                // Serial.print("Default something wrong!: ");
            break;
          }
               Task++;
              if(Task > TASK_MAX) Task = 0; // Max Number of tasks
            //  #define TIMER_MAX 25  // Task TTimer 10= 1 sec 20= 2 sec
              #define TIMER_MAX 13  // Task TTimer 10= 1 sec 20= 2 sec
            #ifndef LAB_TEST_DEVICE
            Serial.println();Serial.print("                       PrevTaskProcessTime: ");Serial.print(TaskTimer);
            Serial.print("00mS    MaxTimeis: ");Serial.print(TIMER_MAX);Serial.print("00mS");Serial.print("  "+IAQstr);
            Serial.print(SM_ProbType +SM_Problem);
            Serial.print("D");Serial.print(SM_Warnings.Dust);
            Serial.print("T");Serial.print(SM_Warnings.Temperature);Serial.print("H");Serial.print(SM_Warnings.Humidity);
            Serial.println(" ");
              #endif
        }

      if(Task100mSec){
        Task100mSec = false;

      }



        //--test beep
//        SetBeepOn();
//        delay(1000);
//        SetBeepOff();



        //----IR command Test
        /*  IRSend1.StartCommand(AC_ELUX,TURN_ON);   //send a turn on command of Electrolux split AC
        delay(1000);
        IRSend1.StartCommand(AC_ELUX,TURN_OFF);   //send a turn on command of Electrolux split AC
        delay(1000);*/

}
