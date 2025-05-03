#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"

S_Location current_location;

#define LED_RED 		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)

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
	
//	SYSCTL_RCGCGPIO_R |= (1U << 5);
//	GPIO_PORTF_DIR_R  |= (LED_RED | LED_BLUE | LED_GREEN);
//	GPIO_PORTF_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
	
	
	//GPS_Get_Current_location(&current_location);
	
	while(1)
	{
//		int i = 0;
//		GPIO_PORTF_DATA_R |= (LED_RED);
//		for(i=0; i < 10; i++)
//		delay(145448);
//		GPIO_PORTF_DATA_R &= ~(LED_RED );
//		GPIO_PORTF_DATA_R |= (LED_BLUE);
//		for(i=0; i < 10; i++)
//		delay(145448);
//		GPIO_PORTF_DATA_R &= ~(LED_BLUE);
//		GPIO_PORTF_DATA_R |= (LED_GREEN);
//		for(i=0; i < 10; i++)
//		delay(145448);
//		GPIO_PORTF_DATA_R &= ~(LED_GREEN);
	}
}

