

#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"

const int len = 128;
char command[len] = {0};
#define CR 0x0D

// Define UART selection constants
#define UART0_ID 0
#define UART6_ID 6

void UART_Init(){//initializing UART 
    unsigned BRD;
    SYSCTL_RCGCUART_R |= 0x0001; // activate UARTO
    SYSCTL_RCGCGPIO_R |= 0x0001; // activate port A
    UART0_CTL_R &= ~0x0001; // disable UART
    
    UART0_IBRD_R = 0x68; // IBRD=int(80000000/(16*9600)) int (520.8333)
    UART0_FBRD_R = 0xB; // FBRD = int(0.8333 * 64 + 0.5)
    
    UART0_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000
    UART0_CTL_R = 0x0301; // enable RXE, TXE and UART 001100000001
    
    GPIO_PORTA_AFSEL_R |= 0x03; // enable alt function PAO, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00)|0x00000011; //configure UART for PAO, PA1 */
    GPIO_PORTA_DEN_R |= 0x03; // enable digital I/O on PAO, PAI
    GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog function on PAO, PAI
    }


// Assuming these definitions exist in your code:
// #define UART0_ID 0
// #define UART1_ID 1
// #define UART2_ID 2
// #define GET_BIT(reg, bit) ((reg) & (1 << (bit)))

char UART_InChar(void)
{
	while (UART0_FR_R & UART_FR_RXFE)
		;							  // block program untill input is recieved
	return (char)(UART0_DR_R & 0xFF); // return the first 8 bit data
}

void UART_OutChar(char data)
{
	while ((UART0_FR_R & UART_FR_TXFF))
		;			   // block program untill input is recieved
	UART0_DR_R = data; // return the first 8 bit data
}

void UART_OutString(char *pt)
{
	while (*pt)
	{
		UART_OutChar(*pt);
		pt++;
	}
}

void getCommand1(char *command, int len)
{ // get the whole command
	char character;
	int i;
	for (i = 0; i < len; i++)
	{
		character = UART_InChar();
		if (character != '\r')
		{
			command[i] = character;
		}
		else if (character == '\r' || i == len || character == CR){
			command[i] = '\0';  	// Null-terminate
            UART_OutString("\r\n");  // New line
            break;
		}
	}
}
	
void PortF_init(){
SYSCTL_RCGCGPIO_R |= 0x20;
while((SYSCTL_PRGPIO_R &0x20)==0);
	GPIO_PORTF_LOCK_R =GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |=0x0E; //allow change tos to PF321
	GPIO_PORTF_AMSEL_R &=~0x0E;   //disable analog function
	GPIO_PORTF_AFSEL_R &=~0x0E;   // NO alternate function
	GPIO_PORTF_PCTL_R &=~0x0000FFF0; // GPIO Clear bit PCTL
	GPIO_PORTF_DEN_R |=0x0E;
	GPIO_PORTF_DIR_R |=0x0E;
	//GPIO_PORTF_PUR_R |=0x10;
	GPIO_PORTF_DATA_R&=~0x0E;
}
void RGB_SetOutput(unsigned char data){
	GPIO_PORTF_DATA_R |=data;
}


void RGB_ClearOutput(unsigned char data){
	GPIO_PORTF_DATA_R &= ~data;
}


int main()
{
	PortF_init();
	UART_INIT(0,9600);
	while (1)
	{
		// UART_OutString("Enter:\n");
		getCommand1(command, len);
		if (strcmp(command, "A") == 0)
		{
			// function to light led
			RGB_ClearOutput(0x0E);
			RGB_SetOutput(0x02);

			memset(command, 0, len); // clear the array that holds the taken string
		}
		else
		{
			// function to light led
			RGB_ClearOutput(0x0E);
			RGB_SetOutput(0x04);
			memset(command, 0, len);
		}
		// UART_OutString("\n");
	}
}