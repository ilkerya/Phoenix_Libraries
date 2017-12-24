/*
  2017.28.03 ILKER
  		Increase Decrease Trands add to data format
*/
//#define AT2T_CLOUD
//#define TRIODOR_CLOUD
//#define MICROSOFT_CLOUD
//#define MQTT
	//	#define ENERGIA_PLATFORM
	//	#define ARDUINO_PLATFORM


void ATT_CLOUD(void){
  int response1 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName1, IAQ.TVOC);
  int response2 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName2, RawValue.Pressure);
  int response3 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName3, RawValue.PM25);
  int response4 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName4, RawValue.Temperature);
  int response5 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName5, RawValue.Humidity);
  int response6 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName6, RawValue.Light);
  int response7 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName7, Filtered.Noise);
  int response8 = m2xClient.updateStreamValue(Device[AT2T_CLOUD_ID], streamName8, Device[USERID]);

  Serial.print("1:");Serial.print(response1);
  Serial.print(" 2:");Serial.print(response2);// responce 202 means ok
  Serial.print(" 3:");Serial.print(response3);
  Serial.print(" 4:");Serial.print(response4);
  Serial.print(" 5:");Serial.print(response5);
  Serial.print(" 6:");Serial.print(response6);
  Serial.print(" 7:");Serial.print(response7);
  Serial.print(" 8:");Serial.print(response8);
  Serial.println();

}






String Jsondata;
void JsonPrep2Send(void){
  	char Separator = ','; // put at the end of any updated value
				// Trend Up:1 Stable:0 Down:-1

  		Jsondata ="{\"username\":\""+Trio_username+"\",\"password\":\""+Trio_password+"\",\"data\":{";
  	//	Jsondata ="{\"username\":\""Trio_username"\",\"password\":\""Trio_password"\",\"data\":{";
		Jsondata += "\"a\":";Jsondata += String(Filtered.TVOC);	 Jsondata += Separator;
		Jsondata += "\"a_t\":";Jsondata += String(Filtered.TVOC_Trend);Jsondata +=Separator;

  		Jsondata += "\"b\":";Jsondata += Float2String(Filtered.Temperature);Jsondata +=Separator;
  		Jsondata += "\"b_t\":";Jsondata += String(Filtered.Temperature_Trend);Jsondata +=Separator;

  		Jsondata += "\"c\":";Jsondata += Float2String(Filtered.Humidity);Jsondata +=Separator;
  		Jsondata += "\"c_t\":";Jsondata += String(Filtered.Humidity_Trend);Jsondata +=Separator;

#ifndef SENSEAIR_CO2_INSTALLED
		Jsondata += "\"d\":";Jsondata += String(Filtered.CO2e);Jsondata +=Separator;
		Jsondata += "\"d_t\":";Jsondata += String(Filtered.CO2e_Trend);Jsondata +=Separator;
#endif
#ifdef SENSEAIR_CO2_INSTALLED
		Jsondata += "\"d\":";Jsondata += String(Filtered.CO2_Absolute);Jsondata +=Separator;
		Jsondata += "\"d_t\":";Jsondata += String(Filtered.CO2_Absolute_Trend);Jsondata +=Separator;
#endif

  		Jsondata += "\"e\":";Jsondata += Float2String(Filtered.PM25);Jsondata +=Separator;
  		Jsondata += "\"e_t\":";Jsondata += String(Filtered.PM25_Trend);Jsondata +=Separator;

  		Jsondata += "\"f\":";Jsondata += Float2String(AccmaxTilt);Jsondata +=Separator;
  //		Jsondata += "\"f_t\":";data += String(Filtered.);Jsondata +=Separator;
  		Jsondata += "\"f_t\":";Jsondata += "0";Jsondata +=Separator;

  		Jsondata += "\"g\":";Jsondata += String(Filtered.Light);Jsondata +=Separator;
 		Jsondata += "\"g_t\":";Jsondata += String(Filtered.Light_Trend);Jsondata +=Separator;

  		Jsondata += "\"h\":";Jsondata += Float2String(Filtered.Noise);Jsondata +=Separator;
  		Jsondata += "\"h_t\":";Jsondata += String(Filtered.Noise_Trend);Jsondata +=Separator;

  		Jsondata += "\"i\":";Jsondata += Float2String(Filtered.Pressure/100);Jsondata +=Separator;
  		Jsondata += "\"i_t\":";Jsondata +=String(Filtered.Pressure_Trend);Jsondata +=Separator;

		Jsondata += "\"j\":";Jsondata += String(Filtered.CO2e);Jsondata +=Separator;
  		Jsondata += "\"device\":";
		Jsondata +="\""+String(Device[DEVICEID])+"\"";// device;
  		Jsondata += "}}\r\n\r\n";

  		Serial.println("Data is ->");
  		Serial.print(Jsondata);   // to console

}







//String Message ="dfdjisojoishgoehg";
char* Str2CharArray(String Message){
	// converts str to char array returns the addr of array
	int i;

//	Message = &DATAR.charAt(0);
//String Starte ="dfdjisojoishgoehg";
//strcpy(Message, Starte);
//	Message = PushNotification_Data280();
	// string Message = PushNotification_Data280();
//	Message += '\0'; // add nul character to string

/*
	char length = strlen(Tweetbuf);
	Serial.println("length:");
	Serial.println(length);Serial.print(strlen(Tweetbuf));
*/

	int  StrLength = Message.length();
//	int  StrLength = Message.length();

	char Buffer[StrLength+1];
	for(i = 0; i < StrLength; i++){
		Buffer[i] = Message.charAt(i);
	//	Serial.print(" ");Serial.print(i);Serial.print(":");
	//	Serial.print(Buffer[i]);
	}
	Buffer[StrLength] = NULL;

	Serial.println();
	Serial.print("Sizeoff:");
	Serial.println(sizeof(Buffer));
	for( i = 0; Buffer[i] != NULL; i++){
		Serial.print(" ");Serial.print(i);Serial.print(":");
		Serial.print(Buffer[i]);
	}

	return Buffer;


/*

	Message.toCharArray(Tweetbuf, 75);

	for(int  i = 0; Tweetbuf[i] =! NULL; i++){
		Serial.print("  ");Serial.print(i);Serial.print(":");
		Serial.println(Tweetbuf[i]);
	}

*/

//	 unsigned int len = 300;
//	 Message.toCharArray(Tweetbuf, strlen(Tweetbuf));

	//string: a variable of type String
//	buf: the buffer to copy the characters into (char [])
//len: the size of the buffer (unsigned int)

}


// "arduino-tweet.appspot.com"
void TweetApp(void){
	int i;
#define LIB_DOMAIN "arduino-tweet.appspot.com"
	//	client.println("POST http://" LIB_DOMAIN "/update HTTP/1.0");
//char Tweetmsg[] = "Tweeting!";
//char Tweetmsg[280];


	int  StrLength = (PushNotification_Data4Arduino()).length();
	char Tweetmsg[StrLength+1];
	for(i = 0; i < StrLength; i++){
		Tweetmsg[i] = (PushNotification_Data4Arduino()).charAt(i);
		Serial.print(" ");Serial.print(i);Serial.print(":");
		Serial.print(Tweetmsg[i]);
	}
	Tweetmsg[StrLength] = NULL;

	Serial.println();
	for(i = 0; Tweetmsg[i] != NULL; i++){
		Serial.print(" ");Serial.print(i);Serial.print(":");
		Serial.print(Tweetmsg[i]);
	}

				// https://twitter.com/CleanAir_IoT
				// "arduino-tweet.appspot.com"



/*
  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
*/



	if (client.connect(LIB_DOMAIN, 80)) {
		client.println("POST http://" LIB_DOMAIN "/update HTTP/1.0");
		client.print("Content-Length: ");

		client.println(strlen(Tweetmsg)+strlen(TweetToken)+14);
		client.println();
		client.print("token=");
		client.print(TweetToken);
		client.print("&status=");
		client.println(Tweetmsg);


	//	client.println(Tweetmsg);
		Serial.print("Sent!");
		int i=0;
		while (!client.available()) {
		 	i++;
		 	if(i> 10000){Serial.print("Timeout");Serial.println(i);break;}
		}
		 while (client.available()) {
		     char c = client.read();
		     Serial.print(c);
    	}
	}
	else{
		Serial.print("Error!");
	}
	client.stop();   //

}



void Cloud_Kepware(){
	// https://www.kepware.com/en-us/
	int i;
	   	char  Kepware[]= "127.0.0.1:3000"; // 80
	   	char Cloud[sizeof(Kepware)];   // https://mobiledev.lely.com/apptests/ddn/electrolux.html

  	for(i = 0; i < sizeof(Kepware) ; i++){
	  	Cloud[i] = Kepware[i];
  	}


  if (client.connect(Cloud, 80)) {
  //  Serial.println("connected to server");

    client.println("POST http:// 127.0.0.1:3000 /update HTTP/1.1");
	client.print("Host: ");
	for(i=0; Cloud[i] != '\0';i++){
			client.print(Cloud[i]);
	}
	client.println();
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(Jsondata.length());
    client.println();
    client.print(Jsondata);

    Serial.print("Sent!");


	i=0;
    	while (!client.available()) {
 			i++;
 			if(i> 10000){Serial.print("Timeout");Serial.println(i);break;}
    	}
    	while (client.available()) {
      		char c = client.read();
     		Serial.print(c);
    	}
  }


  client.stop();   //

  Serial.print("\nAttempt To Send Data To Server:    ");// to console
  PrintCharArray(Cloud, sizeof(Cloud));
/*
  Serial.print("       ");// to console
  if(DataSuccess) Serial.print("Success :) :)  : ) :)");
  else Serial.print("Failed :( ");
  Serial.print("    Cloud Error:");Serial.println(CloudFail);
*/


}

void Cloud_Triodor(){
	char Cloud[sizeof(TriodorAddress)];   // https://mobiledev.lely.com/apptests/ddn/electrolux.html
	int i;
  	char  fakeserver[]= "fake server adress";

/*
	for(i=0; i< 5; i++){
	//	try += String(Phoenix[i]);
	}
*/

 // https://jsonformatter.curiousconcept.com/


  if(Simulation.ServerDisconnect){
	 Simulation.ServerDisconnect = false;
  	for(i = 0; i < sizeof(fakeserver) ; i++){
	  	Cloud[i] = fakeserver[i];
  	}
  }
  else {
  	for(i = 0; i < sizeof(TriodorAddress) ; i++){
	  	Cloud[i] = TriodorAddress[i];
  	}
  }

  DataSuccess = false;
  if (client.connect(Cloud, 80)) {
  //  Serial.println("connected to server");
    client.println("POST "TRIODOR_POST_MSG" HTTP/1.1");
	client.print("Host: ");
	for(i=0; Cloud[i] != '\0';i++){
			client.print(Cloud[i]);
	}
	client.println();
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(Jsondata.length());
    client.println();
    client.print(Jsondata);

    Serial.print("Sent!");

	DataSuccess = true;
	i=0;
    	while (!client.available()) {
 			i++;
 			if(i> 10000){Serial.print("Timeout");Serial.println(i);break;}
    	}
    	while (client.available()) {
      		char c = client.read();
     		Serial.print(c);
    	}
  }
  else CloudFail++;

  client.stop();   // SendNodeJs2Triodor disconnect

  Serial.print("\nAttempt To Send Data To Server:    ");// to console
  PrintCharArray(Cloud, sizeof(Cloud));
  Serial.print("       ");// to console
  if(DataSuccess) Serial.print("Success :) :)  : ) :)");
  else Serial.print("Failed :( ");
  Serial.print("    Cloud Error:");Serial.println(CloudFail);
//  Serial.print("Data is ->");
//  Serial.print(Jsondata);   // to console

}








void SendJson2Google(){
	int i;
	char Google[] = "www.google.com";
	if (client.sslConnect(Google, 443)){
    	Serial.println("Google Connected!");
			// Make a HTTP request:
		client.println("GET /search?q=Json HTTP/1.1");
	//	client.println("Host: www.google.com");
		client.print("Host: ");
		for(i=0; Google[i] != '\0';i++){
			client.print(Google[i]);
		}
		client.println();
		client.println("Connection: close");
		client.println();
		i=0;
		while (!client.available()) {
 			i++;
 			if(i> 10000){Serial.print("Timeout");Serial.println(i);break;}
		}
    	while (client.available()) {
      	char c = client.read();
      	Serial.write(c);
    	}
	}
	else  Serial.println("Error!");

     client.stop();   //
}




/*

char ch = 'c';
char *chptr = &ch;

int i = 20;
int *intptr = &i;

float f = 1.20000;
float *fptr = &f;

char *ptr = "I am a string";

printf("\n [%c], [%d], [%f], [%c], [%s]\n", *chptr, *intptr, *fptr, *ptr, ptr);

return 0;
*/
/*
https://jsonformatter.curiousconcept.com/

{
 "username": "",
 "password": "",
  "data":{
          "a":"voc",
          "a_t":"t",
          "b":"temp",
          "b_t":"t",
          "c":"hum",
          "c_t":"t",
          "d":"co",
          "d_t":"t",
          "e":"pm",
          "e_t":"t",
          "f":"tilt",
          "f_t":"t",
          "g":"light",
          "g_t":"t",
          "h":"noise",
          "h_t":"t",
          "i":"press",
          "i_t":"t",
          "j":"cof",
          "device":"DEVICEID"

}
}

*/
/*
const char RETRIEVING_NAME[] ="Retrieving name\n";
const char ERROR_RETRIEVING_NAME[] ="Error retrieving name\n";
const char SUCCESSFULLY_RETRIEVED_NAME[] ="Successfully retrieved Name:";
const char PARSING_OBJECT[] ="Parsing String\n";
const char ERROR_PARSING_OBJECT[] ="Error parsing Object\n";
const char SUCCESSFULLY_PARSED_OBJECT[] ="Successfully parsed Object\n";
const char DELETING_OBJECT_STRING[] = "Deleting the object\n";
const char FORMAT_FAILED_STRING[] = "Failed to create Format Object\n";
const char OUTPUT_STRING_ERROR[] = "Error creating output String\n";
const char RESULT_PRINTING_STRING[] = "Printing the result:\n";
const char ADDING_FRAMERATE_STRING[] = "Adding frame rate to the format\n";
const char ADDING_INTERLACE_STRING[] = "Adding interlace to the format\n";
const char ADDING_HEIGHT_STRING[] = "Adding height to the format\n";
const char ADDING_WIDTH_STRING[] = "Adding width to the format\n";
const char ADDING_TYPE_STRING[] = "Adding type to the format\n";
const char ADDING_FORMAT_STRING[] = "Adding format to the object\n";
const char ADDING_LENGTH_STRING[] = "Adding length to the object\n";
const char CREATING_FROMAT_STRING[] = "Creating format object\n";
const char ADDING_NAME_STRING[] = "Adding name to the object\n";
const char OBJECT_CREATION_FAILED_STRING[] = "Failed to create the object\n";
const char OBJECT_CREATE_STRING[] = "Created a Object\n";
const char HELLO_STRING[] = "********************\nTesting aJson\n*****************\n";
*/
void JsonPrep(void){

/*
	aJsonObject* root = aJson.createObject();
   if (root != NULL) {
    Serial.print( OBJECT_CREATE_STRING);
  }
  else {
    Serial.print( OBJECT_CREATION_FAILED_STRING);
    return;
  }
  Serial.print( ADDING_NAME_STRING);
  aJson.addItemToObject(root, "username", aJson.createItem(""));
  aJson.addItemToObject(root, "password", aJson.createItem(""));
  aJsonObject* data = aJson.createObject();

 // String ToInsert = String(Filtered.Light);
  if (data != NULL) {
    aJson.addItemToObject(root, "data", data);

    //aJson.addStringToObject(data, "a", "rect");
    //aJson.addNumberToObject(data, "b", 1920);
    //aJson.addNumberToObject(data, "c", 1080);
 	aJson.addNumberToObject(data, "a",   Filtered.TVOC);
 	aJson.addNumberToObject(data, "a_t", Filtered.TVOC_Trend);
 	aJson.addNumberToObject(data, "b",   Filtered.Temperature);
 	aJson.addNumberToObject(data, "b_t", Filtered.Temperature_Trend);
 	aJson.addNumberToObject(data, "c",   Filtered.Humidity);
  	aJson.addNumberToObject(data, "c_t", Filtered.Humidity_Trend);
  	aJson.addNumberToObject(data, "d",   Filtered.CO2e);
  	aJson.addNumberToObject(data, "d_t", Filtered.CO2e_Trend);
  	aJson.addNumberToObject(data, "e",   Filtered.PM25);
  	aJson.addNumberToObject(data, "e",   Filtered.PM25_Trend);
  	aJson.addNumberToObject(data, "f",   AccmaxTilt);
  	aJson.addNumberToObject(data, "f_t", 0);
  	aJson.addStringToObject(data, "g",   (const char*)Filtered.Light);
  	aJson.addNumberToObject(data, "g_t", Filtered.Light_Trend);
  	aJson.addNumberToObject(data, "h",   Filtered.Noise);
  	aJson.addNumberToObject(data, "h_t", Filtered.Noise_Trend);
   	aJson.addNumberToObject(data, "i",   Filtered.Pressure);
  	aJson.addNumberToObject(data, "i_t", Filtered.Pressure_Trend);
//  	aJson.addNumberToObject(data, "device", Device[DEVICEID]);
//    String(Filtered.TVOC)
//    aJson.addFalseToObject(data, "d", "interlace");
//    aJson.addNumberToObject(data, "e", 24);
 //   aJson.addNumberToObject(data, "f", 1.29);
//    aJson.addStringToObject(data, "device", String(Device[DEVICEID]));
    aJson.addStringToObject(data, "device", Device[DEVICEID]);
  }

    char* Jsonstring = aJson.print(root); // Jsonstring e al
    aJson.deleteItem(root);//sil
    root = aJson.parse(Jsonstring);//string i parsla json objesine
    free(Jsonstring); //string bosalt
  Jsonstring = aJson.print(root); // tkrar stringe
  if (Jsonstring != NULL) {
    Serial.println(Jsonstring);
    free(Jsonstring);
  }
  else {
    Serial.print( "error");
  }
    aJsonObject* username = aJson.getObjectItem(root, "username");
    Serial.println(username->valuestring);
 //    aJson.deleteItem(username);//sil

    aJsonObject* password = aJson.getObjectItem(root, "password");
    Serial.println(password->valuestring);
 //    aJson.deleteItem(password);//sil

    aJsonObject* datacontent = aJson.getObjectItem(root, "data");

    aJsonObject* temp = aJson.getObjectItem(datacontent, "a");
//    aJsonObject* temp = aJson.getArrayItem(datacontent, 0);

    Serial.print("a:");
    Serial.println(temp->valuestring);


    //temp = aJson.getArrayItem(datacontent, 1);
    temp = aJson.getObjectItem(datacontent, "c");
    Serial.print("c:");
    Serial.println(temp->valuestring);
 //   temp = aJson.getObjectItem(datacontent, "f");
//    Serial.print("f:");
 //   Serial.println(temp->valuestring);
  //  char* value;
 //   long* value;
   // value = temp->valuestring;
 //   Serial.println(temp->valuestring);
  //    Serial.print(value);

 //   aJson.deleteItem(temp);//sil


  //   aJson.deleteItem(datacontent);//sil
 //   aJson.deleteItem(root);

 */
}

