/*
 * GPS.h
 *
 *  Created on: Apr 18, 2025
 *    
 */

#ifndef INC_GPS_Driver_H_
#define INC_GPS_Driver_H_

//----------------------------
//Includes
//----------------------------

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"
#include "math.h"
#include "LCD.h"

//----------------------------
//User type definitions (structures)
//----------------------------
typedef struct{
	
	char	name[40];
	
	float Latitude_North;	//Specifies the North-most Latitude of Region
	
	float Longitude_East;	//Specifies the East-most Longitude of Region
	
	float Latitude_South;	//Specifies the South-most Latitude of Region
		
	float Longitude_West;	//Specifies the West-most Longitude of Region
}S_Region;

typedef struct{
	
	S_Region Region;			//Specifies the Region of location
	
	float Longitude;			//Specifies the Longitude of location
	
	float Latitude;				//Specifies the Latitude of location
	
}S_Location;

//----------------------------
//Macros
//----------------------------
#define pi 3.1415926535


//----------------------------
//APIs
//----------------------------

void GPS_Get_Current_location(S_Location* location);
void GPS_Display_region(S_Location* location);




#endif /* INC_GPS_Driver_H_ */