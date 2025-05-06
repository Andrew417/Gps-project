#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

#include "GPS.h"
#include "LCD.h"
#include "Switch.h"
#include "Speaker.h"
#include "Systick.h"

#define Buffer_Size		80

char Prev_landmark[Buffer_Size] = {0};
extern uint16_t dist;
extern uint16_t Inv_read;

int main()
{
	
	//GPIO_init(); 	//initalize GPIO
	PortF_Init();
	SysTick_Init();   // Initialize SysTick for delays 
	Interrupt_Init();
	UART_Init();
	LCD_init();		//initalize LCD
	
	S_Location current_location;
	
	while(1)
	{
		//@debug
//		UART_OutString("distance: ");
//		UART_Outint(dist - 50);
//		UART_OutString("\n\r");
		
		
		GPS_Get_Current_location(&current_location);
		//Print new location if diff from previous location and 
		if((strcmp(current_location.Region, Prev_landmark) != 0) && (Inv_read == 0)) 
		{
			strcpy(Prev_landmark, current_location.Region);
			GPS_Display_region(&current_location);
			
			switch(current_location.Region_Index + 1)
			{
				case Hall_A:						Speaker_PlayTrack(Hall_A);						break;
				case Hall_C:						Speaker_PlayTrack(Hall_C);						break;
				case Large_Field:				Speaker_PlayTrack(Large_Field);				break;
				case Credit_building:		Speaker_PlayTrack(Credit_building);		break;
				case Library:						Speaker_PlayTrack(Library);						break;
				case Loban_WSHP:				Speaker_PlayTrack(Loban_WSHP);				break;
				case No_location:				Speaker_PlayTrack(No_location);				break;
			}
			
		}
		else if(Inv_read != 0) //Came from Invaild readings
		{
			//Reset Prev_location
			 strcpy(Prev_landmark, "No locations");
		}
		else	//Same location
		{
			
		}
		GPS_UpdateLED(dist);
		
		
	}
		delay_ms(100);
}


// ISR for GPIO Port F
void GPIOF_Handler(void)
{
    if (GPIO_PORTF_RIS_R & 0x01)					//Check if interrupt caused by PF0	
			{       			
        GPIO_PORTF_ICR_R |= 0x01;        	// Clear interrupt flag
				delay_ms(20);
			
				if(Inv_read != 0)
				{	
					
					Speaker_PlayTrack(No_location);
					
					// Clear LCD display
					lcd_cmd(LCD_CLEAR_SCREEN);    		// Clear display
				
					// Display distance on LCD
					lcd_cmd(LCD_BEGIN_AT_FIRST_ROW); 	// Start at first row
					lcd_string("No valid Read :(");
					
					lcd_cmd(LCD_BEGIN_AT_SECOND_ROW); // Start at second row
					lcd_string("Dist: ?? m");
					delay_ms(3000);
					
					//Write on LCD no of Invalids
					lcd_cmd(LCD_CLEAR_SCREEN);
					lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
					lcd_string("Invalid Reading");

					lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
					lcd_string("Invalids:");
					LCD_Print_int(Inv_read);
				}
				else
				{
					// Clear LCD display
					lcd_cmd(LCD_CLEAR_SCREEN);    		// Clear display
				
					// Display distance on LCD
					lcd_cmd(LCD_BEGIN_AT_FIRST_ROW); 	// Start at first row
					lcd_string("Dist to nearest:");

					lcd_cmd(LCD_BEGIN_AT_SECOND_ROW); // Start at second row
					LCD_Print_int(dist);
					lcd_data('m');
					
					//@debug
//				UART_OutString("\n\r");
//				UART_OutString("Interrupt Distance: ");
//				UART_Outint(dist);
//				UART_OutString("\n\r");
					// Wait ~3 seconds
					delay_ms(3000);
				}
				
				
				strcpy(Prev_landmark, "No locations");
    }
}
