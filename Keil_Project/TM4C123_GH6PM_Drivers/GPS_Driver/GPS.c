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
	
	GPS_Get_message(Message_Buffer);	//Get GPS message using UART 
	
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
    
    // Convert the strings to float
    location->Longitude = atof(lat_str);
    location->Latitude = atof(lon_str);
		
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

void GPS_Get_message(char *buffer)
{

		char character ;
		for (uint8_t i=0;i< Message_Size ; i++)
		{
			character =UART7_InChar();
			if ((character !='\n') || (character != CR))		//'\n' is the terminatiing character of GPS message
			{
				buffer[i]=character;
				UART7_OutChar(buffer[i]);
			}
		 else
				 break;
		}
}


void GPS_Display_region(S_Location* location)
{
	
	//print location->region->name
	
}