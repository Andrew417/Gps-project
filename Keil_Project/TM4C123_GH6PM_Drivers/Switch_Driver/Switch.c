#include "Switch.h"
//#include "PLL.h"


//----------------------------
//Saved Regions
//----------------------------
extern S_Landmark landmarks[Landmarks_Number];

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


