#include "tm4c123_gh6pm_uart.h"


const int len = 128;
char command[len] = {0};
#define CR 0x0D

void UART_Init()
{
	SYSCTL_RCGCUART_R |= 0x04; // activate clk
	SYSCTL_RCGCGPIO_R |= 0x08; // activate port D

	// missing the while check loop of clock to check they are
	//  Wait for clocks to stabilize
	while ((SYSCTL_PRGPIO_R & 0x0008) == 0)
	{
	};

	UART2_CTL_R &= ~0x0001; // disable UART

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTD_CR_R |= 0xC0;

	// BRD=((clk<<2)+(baudrate>>1))/baudrate;

	UART2_IBRD_R = 0x68; // IBRD=int(80000000/(16*9600)) int (520.8333)
	UART2_FBRD_R = 0xB;	 // FBRD = int(0.8333 * 64 + 0.5)
  GPIO_PORTD_DIR_R &= ~0x40; // PD6 (U2RX) as input
  GPIO_PORTD_DIR_R |= 0x80;  // PD7 (U2TX) as output
	UART2_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000
	UART2_CTL_R |= 0x0301; // enable RXE, TXE and UART 001100000001
	GPIO_PORTD_AFSEL_R |= 0xC0;											// enable alt function on PD6 (U2RX), PD7 (U2TX)
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & ~0xFF000000) | 0x11000000; // configure PD6, PD7 for UART2
	GPIO_PORTD_DEN_R |= 0xC0;											// enable digital I/O on PD6, PD7
	GPIO_PORTD_AMSEL_R &= ~0xC0;										// disable analog on PD6, PD7
}

void PortF_init(){
SYSCTL_RCGCGPIO_R |= 0x20;
while((SYSCTL_PRGPIO_R &0x20)==0) ;
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

char UART_InChar(void)
{
	while ((UART2_FR_R & 0x10) != 0)
		;							  // block program untill input is recieved
	return (char)(UART2_DR_R & 0xFF); // return the first 8 bit data
}

void UART_OutChar(char data)
{
	while ((UART2_FR_R & 0x20) != 0)
		;			   // block program untill input is recieved
	UART2_DR_R = data; // return the first 8 bit data
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
			UART_OutChar(command[i]);
		}
		else
		{
			command[i] = '\0';		// Null-terminate on carriage return
			UART_OutString("\r\n"); // Newline
			break;
		}
	}
}
void RGB_SetOutput(unsigned char data){
GPIO_PORTF_DATA_R |=data;
}


void RGB_ClearOutput(unsigned char data){
GPIO_PORTF_DATA_R &= ~data;
}

