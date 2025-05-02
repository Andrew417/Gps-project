#include "GPS.h"

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;

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

	float Current_long = 0;			//Current longitude
	float Current_lat = 0;			//Current Latitude
	
	//Get longitude and latitude using UART from GPS
	
	location->Longitude = Current_long;
	location->Latitude = Current_lat;

	//Compare Current location's longitude and Latitude with Saved Regions
	

}

void GPS_Get_message(char *buffer)
{



}


void GPS_Display_region(S_Location* location)
{
	
	//print location->region->name
	
	
}