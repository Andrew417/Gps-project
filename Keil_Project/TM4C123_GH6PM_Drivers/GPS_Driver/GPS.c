#include "GPS.h"

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;
uint16_t Inv_read = 0;
uint16_t dist = 0;

//GPS Message Example
//$GPRMC,194453.00,A,3015.0262,N,03129.033,E,0.031,,220425,,,A*7D



//----------------------------
//Saved Regions
//----------------------------
S_Landmark landmarks[Landmarks_Number] = {
    
		{"Hall A", 30.06414306, 31.28019695},
    {"Hall C", 30.06364748, 31.28043102},
    {"Large Field", 30.06377145, 31.27950216},
    {"Credit building", 30.06341296, 31.278245681},
    {"Student Affairs Office", 30.06509733, 31.27863045},
    {"library", 30.06525677, 31.28019831},
    {"Loban WSHP", 30.06320738, 31.27940831},
		{"Mina's Home", 30.2503508, 31.4833527}
};



void GPS_Get_Current_location(S_Location* location)
{
	
	
	// Pointers for parsing latitude and longitude
	char lat_str[20], lon_str[20];
	char Message_Buffer[80];					//Buffer that holds GPS message
	
	
	while(GPS_Get_message(Message_Buffer) != 1);	//Get GPS message using UART 
	
	//GPS Message Example
	//$GPRMC,194453.00,A,3017.75041,N,03144.32030,E,0.031,,220425,,,A*7D
	//$GPRMC,,V,,,,,,,,,,N*53
	//$GPRMC,182710.27,V,,,,,,,,,,N*75
	if(Message_Buffer[8] == 'V' || 	Message_Buffer[17] == 'V' )
	{	
		
		//Increment No. of invalid readings
		Inv_read++;
		
		//@debug
//		UART_OutString("\n\r");
//		UART_OutString("Invalid reading No: ");
//		UART_Outint(Inv_read);
//		UART_OutString("\n\r");
//		UART_OutString(Message_Buffer);
//		UART_OutString("\n\r");
	
		if(Inv_read == 1)
		{
			//Write on LCD no of Invalids
			lcd_cmd(LCD_CLEAR_SCREEN);
			lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
			lcd_string("Invalid Reading");
	
			lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
			lcd_string("Invalids:");
			LCD_Print_int(Inv_read);
			
			
		}
		else
		{
			//Up number on LCD
			lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
			for(uint8_t i = 0;  i < 9; i++)
			{
				lcd_cmd(LCD_MOVE_CURSOR_RIGHT);
			}
			LCD_Print_int(Inv_read);
			
		}
		
	}
	else //(Message_Buffer[18] == 'A') Vaild reading
	{
		
		//Reset Number of Invaild readings
		Inv_read = 0;
		
		
		//Find the latitude field after third comma
    char *lat_ptr = strstr(Message_Buffer, ",") + 1; 
    lat_ptr = strstr(lat_ptr, ",") + 1; 
    lat_ptr = strstr(lat_ptr, ",") + 1; 

		 //Extract latitude 
    strncpy(lat_str, lat_ptr, 9); //Extract full latitude number 
    lat_str[9] = '\0'; // Null-terminate the string
		
		
		 //Find the longitude field
    char *lon_ptr = strstr(lat_ptr, ",") + 1; 
    lon_ptr = strstr(lon_ptr, ",") + 1; 
		
		// Extract longitude
    strncpy(lon_str, lon_ptr, 9); // Extract full longitude number 
    lon_str[9] = '\0'; // Null-terminate the string
    
    //@debug
//			// Print Lat and long on Screen
//			UART_OutString("Before Conv: \n\r");
//		
//		UART_OutString("Latitude: ");
//		UART_OutString(lat_str);
//		UART_OutString("     ");
//		UART_OutString("Longitude: ");
//		UART_OutString(lon_str);
//		UART_OutString("\n\r");
		
		////Convert the strings to float (((NMEA Format)))
    location->Longitude = atof(lon_str);
    location->Latitude = atof(lat_str);		
		
		//Converting to Decimal Degree

	
		
			//@debug
//		sprintf(lat_str, "%.5f", location->Latitude);
//		sprintf(lon_str, "%.5f", location->Longitude);
//		
//		// Print Lat and long on Screen ((Decimal Degree))
//		UART_OutString("After Conv: \n\r");
//		UART_OutString("\n\rLatitude: ");
//		UART_OutString(lat_str);
//		UART_OutString("  ");
//		
//		UART_OutString("Longitude: ");
//		UART_OutString(lon_str);
//		UART_OutString("\n\n\r");
		
		
		//Compare Current location's longitude and Latitude with Landmarks
		GPS_Set_Landmark(location);

	}

	
	

}


//compares current location longitude & latitude 
//Sets location datatype variable landmark element
void GPS_Set_Landmark(S_Location* location) 
{

		location->Longitude = floorf(location->Longitude/100) + fmodf(location->Longitude,100)/60;
		location->Latitude = floorf(location->Latitude/100) + fmodf(location->Latitude,100)/60; 
	
    float lat1 = location->Latitude * pi / 180.0;
    float lon1 = location->Longitude * pi / 180.0;
    float min_dist = MAX_DIST;
    int nearest_idx = 0;
		
	//@debug
//	UART_OutString("\n\r");
//	UART_OutString("Lat1: ");		
//	UART_Outint(lat1 * 1000);
//	UART_OutString("Lon1: ");		
//	UART_OutString("   ");
//	UART_Outint(lon1 * 1000);
//	UART_OutString("\n\r");
//	delay_ms(3000);
	
    for (int i = 0; i < Landmarks_Number; i++) {
        // Convert landmark location to radians
        float lat2 = landmarks[i].Latitude * pi / 180.0;
        float lon2 = landmarks[i].Longitude * pi / 180.0;
        float dlat = lat2 - lat1;
        float dlon = lon2 - lon1;

        // Haversine formula
        float a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
        float c = 2 * atan2(sqrt(a), sqrt(1-a));
        dist = EARTH_RADIUS * c;  


        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
				//@debug
//				UART_OutString("\n\r");
//				UART_OutString("Lat2: ");		
//				UART_Outint(lat2 * 1000);
//				UART_OutString("   ");
//				UART_OutString("Lon2: ");		
//				UART_Outint(lon2 * 1000);
//				UART_OutString("\n\r");
//				delay_ms(1000);
//				UART_OutString("dlat: ");		
//				UART_Outint(dlat * 1000);
//				UART_OutString("   ");
//				UART_OutString("dlon: ");		
//				UART_Outint(dlon * 1000);
//				UART_OutString("\n\r");
//				delay_ms(1000);
//				UART_OutString("a: ");		
//				UART_Outint(a * 1000);
//				UART_OutString("   ");
//				UART_OutString("c: ");		
//				UART_Outint(c * 1000);
//				UART_OutString("   ");
//				UART_OutString("dist: ");		
//				UART_Outint((int)dist);
//				UART_OutString("\n\r");	
//				delay_ms(3000);
	
    }
		strncpy(location->Region.name, landmarks[nearest_idx].name, sizeof(location->Region.name) - 1);
    location->Region.name[sizeof(location->Region.name) - 1] = '\0'; // Ensure null-termination

		//@debug
//		UART_OutString("Location: ");
//		UART_OutString(location->Region.name);
//		UART_OutString("\n\r");
		
}

float CalculateDistance(S_Location* current, S_Landmark* landmark) {
    float lat1 = current->Latitude * pi / 180.0;
    float lon1 = current->Longitude * pi / 180.0;
    float lat2 = landmark->Latitude * pi / 180.0;
    float lon2 = landmark->Longitude * pi / 180.0;

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    float a = sin(dlat/2) * sin(dlat/2) + 
              cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371000 * c; // Earth raduis in meters
}

// Find the nearest landmark
const char* FindNearestLandmark(S_Location* current) {
    float min_dist = MAX_DIST;
    int nearest_idx = 0;

    for (int i = 0; i < 5; i++) {
        float dist = CalculateDistance(current, &landmarks[i]);
        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
    }
    return landmarks[nearest_idx].name;
}

uint8_t GPS_Get_message(char *buffer)
{
		uint8_t cor_msg = 0;
		char character ;
		for (uint8_t i=0;i< Message_Size ; i++)
		{
			character =UART_InChar();
			if ((character !='*'))		//'*' is the terminatiing character of GPS message
			{
				if(i < 3) 
				{
					buffer[i]=character;
				}
				else if(((i == 3) && (character == 'R')) || (cor_msg == 1))
				{
					buffer[i]=character;
					cor_msg = 1;
				}
				else
				{
					return 0;
				}
				
			}
		 else
				 break;
		}
		
		return cor_msg;
}



void GPS_Display_region(S_Location* location)
{
	
	lcd_cmd(LCD_CLEAR_SCREEN);
	lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
	lcd_string("Current Location");
	lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
	lcd_string(location->Region.name);
	
}
