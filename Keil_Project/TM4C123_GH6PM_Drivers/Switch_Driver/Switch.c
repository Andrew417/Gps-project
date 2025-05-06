#include "Switch.h"
//#include "PLL.h"


//----------------------------
//Saved Regions
//----------------------------
extern S_Landmark landmarks[Landmarks_Number];


void PortF_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;          // Enable clock for Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) {} // Wait for clock to stabilize

		// ==Port F==	
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     // Unlock PF0
    GPIO_PORTF_CR_R |= 0x0F;            // Allow changes to PF0–PF3

    GPIO_PORTF_AMSEL_R &= ~0x0F;        // Disable analog functions on PF0–PF3
    GPIO_PORTF_PCTL_R &= ~0x0000FFFF;   // Clear alternate function control
    GPIO_PORTF_DIR_R &= ~0x01;          // PF0 (switch) as input
    GPIO_PORTF_DIR_R |= 0x0E;           // PF1–PF3 (LEDs) as output
    GPIO_PORTF_AFSEL_R &= ~0x0F;        // Disable alternate functions
    GPIO_PORTF_PUR_R |= 0x01;           // Enable pull-up resistor on PF0
    GPIO_PORTF_DEN_R |= 0x0F;           // Enable digital I/O on PF0–PF3
		GPIO_PORTF_DATA_R |= 0x0E;		  		// Initialize LEDs to be on
		
}


void Interrupt_Init(void) {		
		// Interrupt configuration for PF0
    GPIO_PORTF_IS_R &= ~0x01;           // PF0 is edge-sensitive
    GPIO_PORTF_IBE_R &= ~0x01;          // Not both edges
    GPIO_PORTF_IEV_R &= ~0x01;          // Falling edge trigger (when the button is pressed)
    GPIO_PORTF_ICR_R |= 0x01;           // Clear any prior interrupt (clear flag)
    GPIO_PORTF_IM_R |= 0x01;            // Arm interrupt on PF0
		
		// Enable the IRQ line for Port F in the NVIC
    // NVIC_EN0_R controls IRQs 0–31; bit 30 is Port F
    NVIC_EN0_R |= (1 << 30);
		
		EnableInterrupts();								// Enable global interrupt flag
		
		// (Optional) Set a priority for IRQ 30 (priority 0: lower numerical value = higher priority)
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF);
	
}


