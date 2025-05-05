#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"



#define LED_RED 		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)

#define Buffer_Size		80
char Prev_landmark[Buffer_Size] = {0};

S_Location current_location;

/*
void delay(void)
{
	unsigned long volatile time;
	time = 145448;
	while(time)
	{
		time--;
	}
	
}
*/
int main()
{
	
	//GPIO_init(); 	//initalize GPIO
	UART_Init();
	LCD_init();		//initalize LCD


	
	
	while(1)
	{
		
		GPS_Get_Current_location(&current_location);
		if(strcmp(current_location.Region.name, Prev_landmark) != 0)
		{
			strcpy(Prev_landmark, current_location.Region.name);
			GPS_Display_region(&current_location);
		}
		else //same location
		{
			
		}
		
	}
		
	
}

