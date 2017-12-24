

/*
String PushNotification_Data(void){
		String data= IAQstr;
		data += "  Temp:";
		data += Float2String(Filtered.Temperature);//f
		//data +="°C Humidity:%";      //12
		data +=" 'C Hum:%";      //12
		data += Float2String(Filtered.Humidity);//f
		data +=" PM2.5:";            //7
		data += Float2String(Filtered.PM25);
		data +=" TVOC:"; 		     //5
		data += String(Filtered.TVOC);
		data +="ppb CO2e:"; 	         //8
		data += String(Filtered.CO2e);
		data +="ppm Press:";      //13
		data += Float2String(Filtered.Pressure/100);
		data +="mBar Light:";         //11
		data += String(Filtered.Light);
		data +="Lux Noise:";          //10
		data += Float2String(Filtered.Noise);
		data +="dB ";
		data += String("Id:");
		data += String(Device[USERID]);
	//	data += AddData;		         //2
		return data;
}
*/
String PushNotification_Data140(void){
		String data= IAQstr;
		data += Float2String(Filtered.Temperature);//f
		data +="'C %";      //12
		data += Float2String(Filtered.Humidity);//f
		data +="Rh PM25:";            //8
		data += Float2String(Filtered.PM25);
		data +=" VOC"; 		     //5
		data += String(Filtered.TVOC);
		data +="ppb CO2:"; 	         //8
		data += String(Filtered.CO2e);
		data +="ppm ";      //13
		data += Float2String(Filtered.Pressure/100);
		data +="mbar Light";         //11
		data += String(Filtered.Light);
		data +="Lux Noise";          //10
		data += Float2String(Filtered.Noise); //
		data +="dB ";
	//	data += String("_");
		data += String(Device[USERID]);
	//	data += AddData;		         //2
		return data;
}


String PushNotification_Data280(void){
		String data= "The Air Quality In The Room is " + IAQstr; //18+ 13

		data += SM_ProbType + SM_Problem;
		data += SM_Advice;
		//data += " ";	//5
		data += Float2String(Filtered.Temperature);//4
		data +="'C %";      //13
		data += String((int)Filtered.Humidity);//4
		data +="Rh PM2.5:";            //11
		data += Float2String(Filtered.PM25);//4
		data +="ug/m3 CO2:"; 		     //4
		data += String(Filtered.CO2e); //4
		data +="ppm VOC:";
		data += String(Filtered.TVOC);  //4
		data +="ppb Pressure:"; 	         //12
		data += String((int)(Filtered.Pressure/100)); //4
		data +="mbar Light:";         //10
		data += String(Filtered.Light); //3
		data +="Lux Noise:";          //9
		data += Float2String(Filtered.Noise); //4
		data +="dB DeviceId:";    //3
	//	data += String("_");
		data += String(Device[USERID]); //4
	//	data += AddData;
		return data;
}

String PushNotification_Data4Arduino(void){
		String data= PushNotification_Data280();
		data += " #OpenAir_IAQ #OpenAir_Eco  #IndoorAirQuality";
		return data;
}


void ChoerosTwitter (String AddData){

			// http://playground.arduino.cc/Code/UTF-8
			// https://dev.twitter.com/basics/counting-characters °
    TembooChoreo StatusesUpdateChoreo(client);

    // Invoke the Temboo client
    StatusesUpdateChoreo.begin();

    // Set Temboo account credentials
    StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
    StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
        // tweet from @IoT_IAQ_Device
  //  String StatusUpdateValue = data;
   //   String StatusUpdateValue = PushNotification_Data140() + AddData;

    String StatusUpdateValue = PushNotification_Data280() + AddData;
    StatusesUpdateChoreo.addInput("StatusUpdate", StatusUpdateValue);
    String ConsumerKeyValue = CONSUMERKEYVALUE;
    StatusesUpdateChoreo.addInput("ConsumerKey", ConsumerKeyValue);
    String AccessTokenValue = ACCESSTOKENVALUE;
    StatusesUpdateChoreo.addInput("AccessToken", AccessTokenValue);
    String ConsumerSecretValue = CONSUMERSECRETVALUE;
    StatusesUpdateChoreo.addInput("ConsumerSecret", ConsumerSecretValue);
    String AccessTokenSecretValue = ACCESSTOKENSECRETVALUE;
    StatusesUpdateChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);

    // Identify the Choreo to run

    StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");


    // Run the Choreo; when results are available, print them to serial
    // 901 time to wait for a Choreo response. Can be edited as needed
    // USE_SSL input to tell library to use HTTPS
    StatusesUpdateChoreo.run(901, USE_SSL);

    while(StatusesUpdateChoreo.available()) {
      char c = StatusesUpdateChoreo.read();
      Serial.print(c);
    }
    StatusesUpdateChoreo.close();

//  }
}


void ChoerosEmail(String AddData){

 //   Serial.println("Running SendAnEmail...");

    TembooChoreo SendEmailChoreo(client);

    // invoke the Temboo client
    // NOTE that the client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    SendEmailChoreo.begin();

    // set Temboo account credentials
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // identify the Temboo Library Choreo to run (Google > Gmail > SendEmail)
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");

    // set the required Choreo inputs
    // see https://www.temboo.com/library/Library/Google/Gmail/SendEmail/
    // for complete details about the inputs for this Choreo



    // the first input is your Gmail email address
    SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
    // next is your application specific password
    SendEmailChoreo.addInput("Password", GMAIL_APP_PASSWORD);
    // next is who to send the email to

    SendEmailChoreo.addInput("ToAddress", USER_EMAIL2RECEIVE);

    // then a subject line
    SendEmailChoreo.addInput("Subject", "IAQ Sensorbox");

    // next comes the message body, the main content of the email

//    SendEmailChoreo.addInput("MessageBody", data);
//  SendEmailChoreo.addInput("MessageBody", PushNotification_Data140() + AddData);
    SendEmailChoreo.addInput("MessageBody", PushNotification_Data280() + AddData);

    // tell the Choreo to run and wait for the results. The
    // return code (returnCode) will tell us whether the Temboo client
    // was able to send our request to the Temboo servers
    unsigned int returnCode = SendEmailChoreo.run();

    // a return code of zero (0) means everything worked
    if (returnCode == 0) {
        Serial.println("Success! Email sent!");
    } else {
      // a non-zero return code means there was an error
      // read and print the error message
      while (SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }
    }
    SendEmailChoreo.close();

}
#define PUSH_REGULARTIME 300 // 60*5 5 hours
#define PUSH_ONDEMANDTIME 30 // 30 minutes

void PushNotificationCheck(void){
	if(PushNotification.OnDemandTimer){
		PushNotification.OnDemandTimer--;
		if(PushNotification.OnDemandTimer == 0){
			PushNotification.OnDemandTimer=PUSH_ONDEMANDTIME;
			if(PushNotification.Tilt == true){
				PushNotification.Tilt = false;
				PushNotification.Tweet = 1;
				PushNotification.Email = 1; // on demand 1
				PushNotification.RegularTimer=PUSH_REGULARTIME; // 5 hours
                      //  ChoerosTwitter(" On Demand!");
			}
		}
	}
	else{
		if(PushNotification.RegularTimer==0){
			PushNotification.RegularTimer=PUSH_REGULARTIME; // 5 hours
			PushNotification.Tweet = 2;
			PushNotification.Email = 2; // regular 2
		}
		else PushNotification.RegularTimer--;
	}
	Serial.print(".OnDemandTimer: ");Serial.print(PushNotification.OnDemandTimer);
	Serial.print("  .RegularTimer: ");Serial.print(PushNotification.RegularTimer);
}

void PushNotificationTweet(void){
	/*
	if( Config[SEND_TWEET] == "1"){
		PushNotification.Tweet = false;
		return;
	}
	*/
	switch(PushNotification.Tweet){
		case 0:
	break;
		case 1: PushNotification.Tweet=false;
		//ChoerosTwitter(" #OpenAir_IAQ #OpenAir_Eco #IndoorAirQuality");

		TweetApp();
	break;
		case 2: PushNotification.Tweet=false;
		//ChoerosTwitter(" #OpenAir_IAQ #OpenAir_Eco #IndoorAirQuality");

		TweetApp();
		break;
	default:
		break;
	}

}
void PushNotificationEmail(void){

	/*
	if( Config[SEND_EMAIL] == "1"){
		PushNotification.Email = false;
		return;
	}

	*/
	switch(PushNotification.Email){
		case 0:
			break;
		case 1: PushNotification.Email=false;ChoerosEmail(" On Demand!  #OpenAir_IAQ #OpenAir_Eco");
			break;
		case 2: PushNotification.Email=false;ChoerosEmail(" Regular!  #OpenAir_IAQ #OpenAir_Eco");
			break;
		default:
			break;
	}
}