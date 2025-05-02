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
	
	float Latitude;		//Specifies the North-most Latitude of Region
	
	float Longitude;	//Specifies the East-most Longitude of Region

}S_Landmark;

typedef struct{
	
	S_Landmark Region;			//Specifies the Region of location
	
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
void GPS_Get_message(char *buffer);




#endif /* INC_GPS_Driver_H_ */