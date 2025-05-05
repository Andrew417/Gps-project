#include "TM4C123_GH6PM_GPIO.h"
void GPIO_init()
{
	SYSCTL_RCGCGPIO_R |= 0x3B; // 111011 for ports A, B, D, E & F
	while ((SYSCTL_PRGPIO_R & 0x3B) == 0); // Wait until clock initialization for used GPIOs

	/* ===TO USE ANY PORT N===
	 * GPIO_PORTN_LOCK_R = GPIO_LOCK_KEY;    	// Unlock Port N commit register
	 * GPIO_PORTN_CR_R |= 0x0E;            		// The bits which equals 1 can be changed, up to 8 bits N0->N7
	 *
	 * GPIO_PORTN_AMSEL_R &= ~0xhex;         	// Disable analog on selected pins
	 * GPIO_PORTN_PCTL_R  &= ~0xhex;    			// Clear PCTL bits for selected pins
	 * GPIO_PORTN_AFSEL_R &= ~0xhex;          // Choose alternate functions on selected pins
	 * GPIO_PORTN_DIR_R   |= 0xhex;          	// Set direction of selected pins: 0 input, 1 output
	 * GPIO_PORTN_DEN_R   |= 0xhex;          	// Enable digital function on selected pins: 1 is digital
	 * GPIO_PORTN_DATA_R  &= ~0xhex;        	// Initialize selected pins
	 */
	
	
	// ==Port A==
	//A7, A6, A5
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY; // Unlock Port A commit register
	GPIO_PORTA_CR_R |= 0xE0;		   // The bits which equals 1 can be changed, 11100000 A5-7

	// Analog is already disabled for Port A
	GPIO_PORTA_PCTL_R &= ~0xFFF00000;  // Clear PCTL bits for selected pins
	GPIO_PORTA_AFSEL_R &= ~0xE0; // Choose alternate functions on selected pins
	GPIO_PORTA_DIR_R |= 0xE0;  // Set direction of selected pins: 0 input, 1 output
	GPIO_PORTA_DEN_R |= 0xE0;   // Enable digital function on selected pins:
	GPIO_PORTA_DATA_R &= ~0xE0;	   // Initialize selected pins


	// ==Port B==
	//B4
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY; // Unlock Port B commit register
	GPIO_PORTB_CR_R |= 0x10;		   

	GPIO_PORTB_AMSEL_R &= ~0x10;	  // Disable analog on selected pins
	GPIO_PORTB_PCTL_R &= ~0x000F0000;	  
	GPIO_PORTB_AFSEL_R &= ~0x10;	 
	GPIO_PORTB_DIR_R |= 0x10;	  
	GPIO_PORTB_DEN_R |= 0x10; 
	GPIO_PORTB_DATA_R &= ~0x10;	  


	// ==Port D==
	//LCD: D0-D3
	//UART: D6, D7
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // Unlock Port D commit register
	GPIO_PORTD_CR_R |= 0xCF;		   // Use the needed bits

	GPIO_PORTD_AMSEL_R &= ~0xCF;	  
	GPIO_PORTD_PCTL_R &= ~0xFF00FFFF;  // Clear PCTL for used bits
	GPIO_PORTD_PCTL_R |= 0x11000000;   // Set PD6 and PD7 to UART2
	GPIO_PORTD_AFSEL_R &= ~0x0F;	//Clear alternate function for D0-D3
	GPIO_PORTD_AFSEL_R |= 0xC0;	  // Choose alternate functions for D7, D6 (UART)
	GPIO_PORTD_DIR_R |= 0x8F;	  // Set output for pins D0-D3, D7 (U2Tx)
	GPIO_PORTD_DIR_R &= ~0x40; // PD6 (U2Rx) as input
	GPIO_PORTD_DEN_R |= 0xCF; 
	GPIO_PORTD_DATA_R &= ~0xCF;	  


	// ==Port E==
	// E5, E4, E1
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY; // Unlock Port E commit register
	GPIO_PORTE_CR_R |= 0x32;		   

	GPIO_PORTE_AMSEL_R &= ~0x32;	  
	GPIO_PORTE_PCTL_R &= ~0x00FF00F0;	  
	GPIO_PORTE_AFSEL_R &= ~0x32;	  
	GPIO_PORTE_DIR_R |= 0x32;
	GPIO_PORTE_DEN_R |= 0x32; 
	GPIO_PORTE_DATA_R &= ~0x32;	  


	// ==Port F==
	//F1, F2, F3 (LEDs)
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // Unlock Port F commit register
	GPIO_PORTF_CR_R |= 0x0E;

	GPIO_PORTF_AMSEL_R &= ~0x0E;   
	GPIO_PORTF_AFSEL_R &= ~0x0E;   
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_DIR_R |= 0x0E;
	//GPIO_PORTF_PUR_R |=0x10;
	GPIO_PORTF_DATA_R &= ~0x0E;	//Initialize LEDs as off
}







