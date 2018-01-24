
/*
	2017.12.27 IY
	All Keys and Tokens are fake! Sice they are private did not expose any! This file lets you compile the project
	any key or token must be created in order to run relevent service!
*/


	char  TriodorAddress[]= "xxxx.xxxxxxx.net";

  	String Trio_username = "xxxxxx";
  	String Trio_password = "xxxxxxxxxxx";
	#define TRIODOR_POST_MSG "/sensorvalues/add"



//#ifndef Device[]=

// https://m2x.att.com/devices/12345678901234567890123456789012

const  char* Device[]={"123456789012345", "1234","12345678901234567890123456789012","12345678901234567890123456789012"};
//Serial.print("DeviceId : ");Serial.print(String(Device[0]));
//Serial.print("DeviceSNo : ");Serial.print(String(Device[1]));
//Serial.print("DeviceId4AT&TM2x : ");Serial.print(String(Device[2])); //AT&T IoT Platform Device ID
//Serial.print("APIKey4AT&TM2x : ");Serial.print(String(Device[3])); //AT&T IoT Platform API Key

char* Config[]={"foo@gmail.com","0","0","0","0"};//

//Serial.print("Email : ");Serial.print(String(Config[0])); //Email to send from foo@gmail.com ->
//Serial.print("EmailOn/Off : ");Serial.print(String(Config[1])); //Email enable/disable 1=enable 0=disable
//Serial.print("TweetOn/Off : ");Serial.print(String(Config[2])); //Tweet enable/disable 1=enable 0=disable
//Serial.print("PrivateCloudOn/Off : ");Serial.print(String(Config[3])); //PrivateCloud enable/disable  1=enable 0=disable
//Serial.print("GoogleOn/Off : ");Serial.print(String(Config[4])); //Google search enable/disable  1=enable 0=disable



// "arduino-tweet.appspot.com"
char TweetToken[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

#define TEMBOO_ACCOUNT "xxxxxxx"  // Your Temboo account name
#define TEMBOO_APP_KEY_NAME "1234567"  // Your Temboo app name
#define TEMBOO_APP_KEY "12345678901234567890123456789012"  // Your Temboo app key


// temboo account name
// https://foo.temboolive.com/


// your Gmail username,formatted as a complete email address, e.g., "john.bonham@gmail.com"
const String GMAIL_USER_NAME = "foo@gmail.com";

// your application specific password (see instructions above)
const String GMAIL_APP_PASSWORD = "1234567890123456";

const String USER_EMAIL2RECEIVE = "fake@gmail.com";

const String CONSUMERKEYVALUE = "fffffffffffffffffffffffff";
const String ACCESSTOKENVALUE= "fffffffffffffffffffffffff";
const String CONSUMERSECRETVALUE = "fffffffffffffffffffffffff";
const String ACCESSTOKENSECRETVALUE = "fffffffffffffffffffffffff";

