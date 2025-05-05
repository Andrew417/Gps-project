#include "LCD.h"


#define LED_RED 		(1U << 0)

int main(void) {
    LCD_Init();
	
		SYSCTL->RCGCGPIO |= (1U << 5);
	  GPIOF->DIR |= (1U << LED_RED);
    GPIOF->DEN |= (1U << LED_RED);
	
	
    LCD_Command(0x80);    // Move cursor to first line
    LCD_String("A4troooo");

		LCD_Command(0xC0);    // Move cursor to second line
		LCD_String("Ya Martina >:(!");

	
		GPIOF->DATA |= (1U << LED_RED);

    while(1) {
        // Infinite loop
    }
}
