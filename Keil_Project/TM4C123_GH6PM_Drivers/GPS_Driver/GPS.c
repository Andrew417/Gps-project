#include "GPS.h"

//----------------------------
//Global Variables
//----------------------------
const double EARTH_RADIUS = 6371000;

//----------------------------
//Saved Regions
//----------------------------




void GPS_Get_Current_location(S_Location* location)
{

	float Current_long = 0;			//Current longitude
	float Current_lat = 0;			//Current Latitude
	
	//Get longitude and latitude using UART from GPS
	
	location->Longitude = Current_long;
	location->Latitude = Current_lat;

	//Compare Current location's longitude and Latitude with Saved Regions
	

}


void GPS_Display_region(S_Location* location)
{
	
	//print location->region->name
	
	
}