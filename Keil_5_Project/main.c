#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"



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
	
	GPIO_init(); 	//initalize GPIO
	UART_Init();	//initalize UART
	LCD_init();		//initalize LCD

	
	char lcd_buffer[60] = "LCD Working";
	
	lcd_data('a');
	
	//lcdstring(lcd_buffer, strlen(lcd_buffer));
	
	
	while(1)
	{
		
		
		
	}
	
	
}

