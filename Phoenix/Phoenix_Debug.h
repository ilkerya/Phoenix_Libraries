void PrintUnsortedValues(unsigned char Index){
	unsigned char i;
			Serial.println();Serial.println("TempArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(TempArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("HumArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(HumArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("PMArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(PMArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("VOCArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(VOCArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("CO2Arr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(CO2eArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("LightArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(LightArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("PressureArr(Raw)");
			for(i=0;i<=Index;i++){
				Serial.print(i);Serial.print(":");Serial.print(PressureArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}


}
void PrintSortedValues(unsigned char index){
	unsigned char i;
			Serial.println();Serial.println("TempArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(TempArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("HumArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(HumArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("PMArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(PMArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("VOCArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(VOCArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("CO2Arr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(CO2eArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("LightArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(LightArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}
			Serial.println();Serial.println("PressureArr(Sorted)");
			for(i=0;i<=index;i++){
				Serial.print(i);Serial.print(":");Serial.print(PressureArr[i]);Serial.print("  ");if (i == 14)Serial.println();
			}


}
void PrintIAQFinalLelevels(void){
	Serial.println();
	Serial.print("Pm25:");Serial.print(IAQ_Health[QUE_PM25]);
	Serial.print("  Temp:");Serial.print(IAQ_Health[QUE_TEMP]);
	Serial.print("  Hum:");Serial.print(IAQ_Health[QUE_HUMD]);
	Serial.print("  Voc:");Serial.print(IAQ_Health[QUE_VOC]);
	Serial.print("  Co2:");Serial.print(IAQ_Health[QUE_CO2]);
//	Serial.print("  Press:");Serial.print(IAQ_Health[QUE_CO2]);
	Serial.println();


}

void PrintFilteredAverageValues(){
			Serial.println();
			Serial.print("Average");
			Serial.print("  Temp :");Serial.print(Filtered.Temperature);
			Serial.print("  Humidity :");Serial.print(Filtered.Humidity);
			Serial.print("  PM25 :");Serial.print(Filtered.PM25);
			Serial.print("  VOC :");Serial.print(Filtered.TVOC);
			Serial.print("  CO2e :");Serial.print(Filtered.CO2e);
			Serial.print("  Light :");Serial.print(Filtered.Light);
			Serial.print("  Noise :");Serial.print(Filtered.Noise);
			Serial.print("  Pressure :");Serial.print(Filtered.Pressure);
			Serial.print("     ");Serial.print(IAQstr);
			Serial.println();

}

void PrintTiltUnsorted(int MaxArray){
	int i;
			Serial.println();Serial.println("Tilt(Raw)");
			for(i=0;i<=MaxArray;i++){
				Serial.print(i);Serial.print(":");Serial.print(GSensorArr[i]);Serial.print("  ");
				if (i == 15)Serial.println();
				if (i == 30)Serial.println();

			}

}



void PrintTiltSorted(int MaxArray){
	int i;
	Serial.println();Serial.println("Tilt(Sorted)");
	for(i=0;i<=MaxArray;i++){
		Serial.print(i);Serial.print(":");Serial.print(GSensorArr[i]);Serial.print("  ");
		if (i == 15)Serial.println();
		if (i == 30)Serial.println();
	}
}


void PrintDeviceInfo(void){
	Serial.print("DeviceId : ");Serial.print(String(Device[DEVICEID]));
	Serial.print("  UserId : ");Serial.print(Device[USERID]);
	Serial.print(" email : ");Serial.print(Device[USER_EMAIL2SEND]);
}

