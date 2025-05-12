/*
 ============================================================================
 Name        : Main.c
 Author      : Mina Fathy Labib, Julia Nasser
 Description : Main Application, C99
 ============================================================================
 */


//----------------------------
//Includes
//----------------------------
#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"
#include "GPS.h"
#include "LCD.h"
#include "Switch.h"
#include "Systick.h"


//----------------------------
//Global Variables
//----------------------------
char Prev_landmark[80] = {0};						//Saving The last Printed location Name on LCD
extern uint16_t Inv_read;								//No. of Invalid Msgs from GPS module from GPS.c
S_Location current_location;						//Global Variable That holds Current Location Data

int main()
{
	GPIO_init(); 				//Initalize GPIO
	SysTick_Init();   	//Initialize SysTick for delays
	Interrupt_Init();		//initalize Interrupt
	UART_Init();				//initalize UART
	LCD_init();					//initalize LCD
	
	current_location.distance = MAX_DIST;
	
	while(1)
	{		
		GPS_Get_Current_location(&current_location);
		//Print new location if diff from previous location and 
		if((strcmp(current_location.Region, Prev_landmark) != 0) && (Inv_read == 0)) 
		{
			strcpy(Prev_landmark, current_location.Region);
			GPS_Display_region(&current_location);
			
		}
		else if(Inv_read != 0) //Came from Invaild readings
		{
			//Reset Prev_location
			 strcpy(Prev_landmark, "No locations");
		}
		else	//(Same location)
		{
			//Do Nothing
		}
		GPS_UpdateLED(current_location.distance);
	}
}


// ISR for GPIO Port F
void GPIOF_Handler(void)
{
		//Check if interrupt caused by PF0	
    if (GPIO_PORTF_RIS_R & 0x01)					
		{       			
			// Clear interrupt flag
			GPIO_PORTF_ICR_R |= 0x01;        	
			delay_ms(20);

			if(Inv_read != 0)
			{	
									
				// Clear LCD display
				lcd_cmd(LCD_CLEAR_SCREEN);
			
				// Display distance on LCD
				lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
				lcd_string("No valid Read :(");
				
				lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
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
				lcd_cmd(LCD_CLEAR_SCREEN);    	
			
				// Display distance on LCD
				lcd_cmd(LCD_BEGIN_AT_FIRST_ROW);
				lcd_string("Dist to nearest:");

				lcd_cmd(LCD_BEGIN_AT_SECOND_ROW);
				LCD_Print_int(current_location.distance);
				lcd_data('m');
				
				delay_ms(3000);
			}
				
			strcpy(Prev_landmark, "No locations");
		}
}
