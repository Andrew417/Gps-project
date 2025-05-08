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
#include "string.h"
#include "stdio.h"
#include "Utils.h"

//----------------------------
//User type definitions (structures)
//----------------------------
typedef struct{
	
	char	name[40];
	
	float Latitude;		//Specifies the North-most Latitude of Region
	
	float Longitude;	//Specifies the East-most Longitude of Region

}S_Landmark;

typedef struct{
	
	char Region[20];			//Specifies the Region of location
	
	uint8_t Region_Index;	//Index of Region from Saved Landmarks location;
	
	float Longitude;			//Specifies the Longitude of location
	
	float Latitude;				//Specifies the Latitude of location
	
	uint16_t distance;
	
}S_Location;

//----------------------------
//Macros
//----------------------------
#define pi 									3.141592			//Used in distance and Coardinates Conversion from NMEA to degree
#define Message_Size 				80						//Size of Char Array to hold GPS Message
#define MAX_DIST 						1000.0				//Used in Nearest Location Distance comparison
#define Landmarks_Number		7							//No. of Landmakes saved On Tiva C

//----------------------------
//APIs
//----------------------------

void GPS_Get_Current_location(S_Location* location);
void GPS_Display_region(S_Location* location);
uint8_t GPS_Get_message(char *buffer);
void GPS_Set_Landmark(S_Location* location);
void GPS_UpdateLED(uint16_t distance);


#endif 