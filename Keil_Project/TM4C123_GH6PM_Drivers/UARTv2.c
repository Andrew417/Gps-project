#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"

const int len = 128;
char command[128] = {0};

// -------- GPIO Functions ----------
void PortF_init() {
    SYSCTL_RCGCGPIO_R |= 0x20;             // Enable clock for Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Wait until ready

    GPIO_PORTF_LOCK_R = 0x4C4F434B;        // Unlock Port F
    GPIO_PORTF_CR_R |= 0x0E;               // Allow changes to PF1-3
    GPIO_PORTF_AMSEL_R &= ~0x0E;           // Disable analog
    GPIO_PORTF_AFSEL_R &= ~0x0E;           // Disable alt functions
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;      // GPIO clear PCTL
    GPIO_PORTF_DEN_R |= 0x0E;              // Enable digital
    GPIO_PORTF_DIR_R |= 0x0E;              // Set PF1-3 as output
    GPIO_PORTF_DATA_R &= ~0x0E;            // All LEDs OFF
}

void RGB_SetOutput(unsigned char data) {
    GPIO_PORTF_DATA_R |= data;
}

void RGB_ClearOutput(unsigned char data) {
    GPIO_PORTF_DATA_R &= ~data;
}

// -------- MAIN (Simulation-friendly) ----------
int main() {
    PortF_init();

    while (1) {
        // Simulate input string
        strcpy(command, "A"); // Try changing to "B", "abc", etc.

        if (strcmp(command, "A") == 0) {
            RGB_ClearOutput(0x0E);   // Turn off all LEDs
            RGB_SetOutput(0x02);     // Turn on RED (PF1)
        } else {
            RGB_ClearOutput(0x0E);
            RGB_SetOutput(0x04);     // Turn on BLUE (PF2)
        }

        memset(command, 0, len); // Clear input buffer

        // Simulate delay
        for (int i = 0; i < 1000000; i++){};
    }
}
