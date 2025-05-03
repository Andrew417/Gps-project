#include "GPS.h"
#include <float.h>   // For INFINITY
#define MAX_LANDMARK_DISTANCE 500.0f 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;
#define CR 0x0D

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
	
	//GPS_Get_message(Message_Buffer);	//Get GPS message using UART 
	
	//GPS Message Example
	//$GPRMC,194453.00,A,30.0640206,N,31.2801822,E,0.031,,220425,,,A*7D
	if(Message_Buffer[18] == 'V')
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

	}

	//Compare Current location's longitude and Latitude with Landmarks
	GPS_Set_Landmark(location);
	

}

//compares current location longitude & latitude 
//Sets location datatype variable landmark element
void GPS_Set_Landmark(S_Location* location)
{	
		//get distance implmentation
		// Convert current location to radians
    float lat1 = location->Latitude * M_PI / 180.0;
    float lon1 = location->Longitude * M_PI / 180.0;
    
    float min_dist = MAX_LANDMARK_DISTANCE;
    int nearest_idx = 0;

    // Check all landmarks
    for (int i = 0; i < 7; i++) {
        // Convert landmark location to radians
        float lat2 = landmarks[i].Latitude * M_PI / 180.0;
        float lon2 = landmarks[i].Longitude * M_PI / 180.0;

        // Calculate differences
        float dlat = lat2 - lat1;
        float dlon = lon2 - lon1;

        // Haversine formula
        float a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
        float c = 2 * atan2(sqrt(a), sqrt(1-a));
        float dist = 6371000 * c;  // Earth radius in meters

        // Check if this is the nearest so far
        if (dist < min_dist) {
            min_dist = dist;
            nearest_idx = i;
        }
		}
		strncpy(location->landmark.name, landmarks[nearest_idx].name, sizeof(location->landmark.name));
		// location->landmark.name[sizeof(location->landmark.name) - 1] = '\0'; // Ensure null-termination
		
}

void GPS_Get_message(char *buffer)
{

		char character ;
		for (uint8_t i=0;i< Message_Size ; i++)
		{
			character =UART_InChar();
			if ((character !='\n') || (character != CR))		//'\n' is the terminatiing character of GPS message
			{
				buffer[i]=character;
				UART_OutChar(buffer[i]);
			}
		 else
				 break;
		}
}


void GPS_Display_region(S_Location* location)
{
	
	//print location->region->name
	
}