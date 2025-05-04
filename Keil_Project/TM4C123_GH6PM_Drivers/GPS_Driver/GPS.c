#include "GPS.h"

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;
#define CR 0x0D
#define max 1000.0

//GPS Message Example
//$GPRMC,194453.00,A,3017.75041,N,03144.32030,E,0.031,,220425,,,A*7D


//----------------------------
//Saved Regions
//----------------------------
S_Landmark landmarks[7] = {
    
		{"Hall A", 30.06414306, 31.28019695},
    {"Hall C", 30.06364748, 31.28043102},
    {"Large Field", 30.06377145, 31.27950216},
    {"Credit building", 30.06341296, 31.278245681},
    {"Student Affairs Office", 30.06509733, 31.27863045},
    {"library", 30.06525677, 31.28019831},
    {"Loban WSHP", 30.06320738, 31.27940831}
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
		//print on LCD Invalid reading
	}
	else //(Message_Buffer[18] == 'A') Vaild reading
	{
		
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
    
    
			// Print Lat and long on Screen
//		UART_OutString("Longitude: ");
//		UART_OutString(lon_str);
//		UART_OutString("\n\r");
//		
//		UART_OutString("Latitude: ");
//		UART_OutString(lat_str);
//		UART_OutString("\n\r");
		
		//// Convert the strings to float (((NMEA Format)))
    //location->Longitude = atof(lon_str);
    //location->Latitude = atof(lat_str);		
		
		//Converting to Decimal Degree
//		float lat_deg = floor(atof(lat_str) / 100);          	// 30 degrees
//		float lat_min = atof(lat_str) - (lat_deg * 100);     	// 15.0262 minutes
//		location->Latitude = lat_deg + (lat_min / 60);  			// 30 + (15.0262/60) = 30.250437
//		
//		float lon_deg = floor(atof(lon_str)/ 100);          	// 31 degrees
//		float lon_min = atof(lon_str) - (lon_deg * 100);     	// 29.033 minutes
//		location->Longitude = lon_deg + (lon_min / 60);  			// 31 + (29.033/60) = 31.483883
//		
//		
//		sprintf(lat_str, "%.6f", location->Latitude);
//		sprintf(lon_str, "%.6f", location->Longitude);
//		
			// Print Lat and long on Screen ((Decimal Degree))
		UART_OutString("Longitude: ");
		UART_OutString(lon_str);
		UART_OutString("\n\r");
		
		UART_OutString("Latitude: ");
		UART_OutString(lat_str);
		UART_OutString("\n\r");
		
		//Compare Current location's longitude and Latitude with Landmarks
		GPS_Set_Landmark(location);

	}

	
	

}


//compares current location longitude & latitude 
//Sets location datatype variable landmark element
void GPS_Set_Landmark(S_Location* location) 
{

    float lat1 = location->latitude * M_PI / 180.0;
    float lon1 = location->longitude * M_PI / 180.0;
    float min_dist = max;
    int nearest_idx = 0;

    for (int i = 0; i < 7; i++) {
        // Convert landmark location to radians
        float lat2 = landmarks[i].latitude * M_PI / 180.0;
        float lon2 = landmarks[i].longitude * M_PI / 180.0;
        float dlat = lat2 - lat1;
        float dlon = lon2 - lon1;

        // Haversine formula
        float a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
        float c = 2 * atan2(sqrt(a), sqrt(1-a));
        float dist = EARTH_RADIUS * c;  


        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
    }
}
uint8_t GPS_Get_message(char *buffer)
{
		uint8_t cor_msg = 0;
		char character ;
		for (uint8_t i=0;i< Message_Size ; i++)
		{
			character =UART_InChar();
			if ((character !='E') || (character != CR))		//'*' is the terminatiing character of GPS message
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
	
	//print location->region->name
	
}