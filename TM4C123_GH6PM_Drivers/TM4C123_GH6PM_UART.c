/*
 ============================================================================
 Name        : TM4C123_GH6PM_UART.c
 Author      : Ereeny Awany Wahba, Andrew Ehab, Kyrolos Essam
 Description : UART Driver, C99
 ============================================================================
 */

#include "TM4C123_GH6PM_UART.h"


//----------------------------
//Global Variables
//----------------------------
const int len = 128;
char command[len] = {0};
#define CR 0x0D


void UART_Init()
{
	SYSCTL_RCGCUART_R |= 0x04; // activate clk
	// missing the while check loop of clock to check they are
	
	//  Wait for clocks to stabilize
	delay_ms(1);
	UART2_CTL_R &= ~0x0001; // disable UART

	// BRD=((clk<<2)+(baudrate>>1))/baudrate;

	UART2_IBRD_R = 0x68; // IBRD=int(80000000/(16*9600)) int (520.8333)
	UART2_FBRD_R = 0xB;	 // FBRD = int(0.8333 * 64 + 0.5)
	UART2_LCRH_R = 0x0070; // 8-bit word length, enable FIFO 001110000
	UART2_CTL_R |= 0x0301; // enable RXE, TXE and UART 001100000001

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


void UART_Outint(int num)
{
	char num_str[20];
	sprintf(num_str,"%d",num);
	UART_OutString(num_str);
}


void getCommand1(char *command, int len)
{ 
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
