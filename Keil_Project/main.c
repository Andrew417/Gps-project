#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"



#define LED_RED 		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)

#define Buffer_Size		40
char RX_Buffer[40] = {0};

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
	//UART7_Init();	//initalize UART
	//LCD_init();		//initalize LCD

	//UART7_OutString("Hello From TivaC \n\r");
	
	//UART7_getCommand1(RX_Buffer, Buffer_Size);
	//UART7_OutString(RX_Buffer);
	
	GPS_Get_Current_location(&current_location);
	
	
	while(1)
	{
		
		
		
	}
	
	
}

