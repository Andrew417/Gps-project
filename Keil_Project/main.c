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
char RX_Buffer[Buffer_Size] = {0};

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

	lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);    // Move cursor to first line
	lcd_string("Number: ");

   uint8_t i = 0;
	
	while(1)
	{
		
		//GPS_Get_Current_location(&current_location);
		
		lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);    // Move cursor to second line
		LCD_Print_float(i);
		i++;
		delay_ms(1000);
	
		
	}
		
	
}

