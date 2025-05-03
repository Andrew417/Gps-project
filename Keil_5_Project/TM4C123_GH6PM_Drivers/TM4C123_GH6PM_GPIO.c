#include "TM4C123_GH6PM_GPIO.h"
void GPIO_init()
{
	//==Used Pins==
	/* 
	LCD: PA5, PA6, PA7, PB0, PB1, PB4, PD0, PD1, PD2, PE4, PE5
	UART2: D6 (Rx), D7 (Tx)
	UART7: E0 (Rx), E1 (Tx)
	
	
	*/
	SYSCTL_RCGCGPIO_R |= 0x3F; // 00111111 for all ports
	while ((SYSCTL_PRGPIO_R & 0x3F) == 0)
		; // Wait until clock initialization for used GPIOs

	/* ===TO USE ANY PORT N===
	 * GPIO_PORTN_LOCK_R = GPIO_LOCK_KEY;    	// Unlock Port F commit register
	 * GPIO_PORTN_CR_R |= 0x0E;            		// The bits which equals 1 can be changed, up to 8 bits N0->N7
	 *
	 * GPIO_PORTN_AMSEL_R &= ~0xhex;         	// Disable analog on selected pins
	 * GPIO_PORTN_PCTL_R  &= ~0xhex;    			// Clear PCTL bits for selected pins
	 * GPIO_PORTN_AFSEL_R &= ~0xhex;          // Choose alternate functions on selected pins
	 * GPIO_PORTN_DIR_R   |= 0xhex;          	// Set direction of selected pins: 0 input, 1 output
	 * GPIO_PORTN_DEN_R   |= 0xhex;          	// Enable digital function on selected pins: 1 is digital
	 * GPIO_PORTN_DATA_R  &= ~0xhex;        	// Initialize selected pins
	 *
	 */ 

	// ==Port A==

	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY; // Unlock Port F commit register
	GPIO_PORTA_CR_R |= 0xE0;		   // The bits which equals 1 can be changed, 11100000 A5-7

	// Analog is already disabled for Port A
	GPIO_PORTA_PCTL_R &= 0x0;  // Clear PCTL bits for all pins
	GPIO_PORTA_AFSEL_R &= ~0xE0; // Choose alternate functions on selected pins
	GPIO_PORTA_DIR_R |= 0xE0;  // Set selected pins as outputs
	GPIO_PORTA_DEN_R = 0xE0;   // Enable digital function on selected pins:
	GPIO_PORTA_DATA_R &= 0;	   // Initialize selected pins

	// ==Port B==

	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY; // Unlock Port B commit register
	GPIO_PORTB_CR_R |= 0x13;		   // The bits which equals 1 can be changed, up to 8 bits N0->N7

	GPIO_PORTB_AMSEL_R &= ~0x13;	  // Disable analog on selected pins
	GPIO_PORTB_PCTL_R = 0;	  // Clear PCTL bits for selected pins
	GPIO_PORTB_AFSEL_R &= ~0x13;	  // Choose alternate functions on selected pins
	GPIO_PORTB_DIR_R |= 0x13;	  // Set direction of selected pins: 0 input, 1 output
	GPIO_PORTB_DEN_R |= 0x13; // Enable digital function on selected pins
	GPIO_PORTB_DATA_R = 0;	  // Initialize selected pins

	// ==Port D==

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // Unlock Port D commit register
	GPIO_PORTD_CR_R |= 0xC7;		   // The bits which equals 1 can be changed, up to 8 bits N0->N7

	GPIO_PORTD_AMSEL_R &= ~0xC7;	  // Disable analog on selected pins
	GPIO_PORTD_PCTL_R = 0;	  // Clear PCTL bits for selected pins
	GPIO_PORTD_AFSEL_R &= ~0xC7;	  // Choose alternate functions on selected pins
	GPIO_PORTD_DIR_R |= 0xC7;	  // Set direction of selected pins: 0 input, 1 output
	GPIO_PORTD_DEN_R |= 0xC7; // Enable digital function on selected pins
	GPIO_PORTD_DATA_R = 0;	  // Initialize selected pins

	// ==Port E==

	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY; // Unlock Port D commit register
	GPIO_PORTE_CR_R |= 0x30;		   // The bits which equals 1 can be changed, up to 8 bits N0->N7

	GPIO_PORTE_AMSEL_R &= ~0x30;	  // Disable analog on selected pins
	GPIO_PORTE_PCTL_R = 0;	  // Clear PCTL bits for selected pins
	GPIO_PORTE_AFSEL_R &= ~0x30;	  // Choose alternate functions on selected pins
	GPIO_PORTE_DIR_R |= 0x30;	  // Set direction of selected pins: 0 input, 1 output
	GPIO_PORTE_DEN_R |= 0x30; // Enable digital function on selected pins
	GPIO_PORTE_DATA_R = 0;	  // Initialize selected pins

	// ==Port F==
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // Unlock Port F commit register
	GPIO_PORTF_CR_R |= 0x0E;		   // The bits which equals 1 can be changed, up to 8 bits N0->N7

	GPIO_PORTF_AMSEL_R &= ~0x0E;	  // Disable analog on selected pins
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // Clear PCTL bits for selected pins
	GPIO_PORTF_AFSEL_R &= ~0x0E;	  // Choose alternate functions on selected pins
	GPIO_PORTF_DIR_R |= 0x0E;		  // Set selected pins as outputs
	GPIO_PORTF_DEN_R |= 0x0E;		  // Enable digital function on selected pins
	GPIO_PORTF_DATA_R |= 0x0E;		  // Initialize selected pins
}