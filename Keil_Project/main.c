#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"
#include "Switch.h"

#define Buffer_Size		80

#define LED_RED 		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)


char Prev_landmark[Buffer_Size] = {0};
extern uint16_t dist;



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
	PortF_Init();
	Interrupt_Init();
	UART_Init();
	LCD_init();		//initalize LCD
	
	S_Location current_location;
	
	
	while(1)
	{
		//@debug
//		UART_OutString("distance: ");
		UART_Outint(dist - 50);
		UART_OutString("\n\r");
		delay_ms(1000);
		
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


// ISR for GPIO Port F
void GPIOF_Handler(void) {
    if (GPIO_PORTF_RIS_R & 0x01) {       // Check if interrupt caused by PF0				
        GPIO_PORTF_ICR_R |= 0x01;        // Clear interrupt flag

			
				// Clear LCD display
        lcd_cmd(LCD_CLEAR_SCREEN);    // Clear display
			
				// Display distance on LCD
				lcd_cmd(LCD_BEGIN_AT_FIRST_ROW); // Start at first row
				lcd_string("Dist to nearest:");

				lcd_cmd(LCD_BEGIN_AT_SECOND_ROW); // Start at second row
				LCD_Print_int(dist);
				lcd_data('m');
				
				//@debug
				UART_OutString("\n\r");
				UART_OutString("Interrupt Distance: ");
				UART_Outint(dist);
				UART_OutString("\n\r");
        // Wait ~3 seconds
				delay_ms(3000);
        strcpy(Prev_landmark, "No locations");
    }
}
