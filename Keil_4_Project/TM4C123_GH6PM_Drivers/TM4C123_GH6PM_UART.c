#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
const int len=128;
char command[len]={0};
#define CR 0x0D
void UART7_Init(){
SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7; // activate UART7
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // activate port E

UART7_CTL_R &= ~UART_CTL_UARTEN; // disable UART
	
	//BRD=((clk<<2)+(baudrate>>1))/baudrate;

UART7_IBRD_R = 0x68; // IBRD=int(80000000/(16*9600)) int (520.8333)
UART7_FBRD_R = 0xB; // FBRD = int(0.8333 * 64 + 0.5)

UART7_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN; // 8-bit word length, enable FIFO 001110000
UART7_CTL_R |= UART_CTL_RXE | UART_CTL_TXE|UART_CTL_UARTEN; // enable RXE, TXE and UART 001100000001

GPIO_PORTE_AFSEL_R |= 0x03; // enable alt function on PE0 (U7RX), PE1 (U7TX)
GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x000000FF) | 0x00000011; // configure PE0, PE1 for UART7
GPIO_PORTE_DEN_R |= 0x03; // enable digital I/O on PE0, PE1
GPIO_PORTE_AMSEL_R &= ~0x03; // disable analog on PE0, PE1
}
   

char UART7_InChar(void){
while ((UART7_FR_R & UART_FR_RXFE) !=0){}; //block program untill input is recieved
	return (char)(UART7_DR_R & 0xFF); //return the first 8 bit data
}

void UART7_OutChar(char data){
while ((UART7_FR_R & UART_FR_TXFF) !=0){}; //block program untill input is recieved
	UART7_DR_R = data; //return the first 8 bit data
}

void UART7_OutString(char *pt){
while(*pt){
UART7_OutChar(*pt);
	pt++;
}
}




void UART7_getCommand1(char *command , int len){ // get the whole command
 char character ;
	int i;
	for (i=0;i<len ; i++){
	  character =UART7_InChar();
		if (character !='\r'){
		    command[i]=character;
			   UART7_OutChar(command[i]);
		}
		else if (character =='\r' || i==len || character == CR)
			break;
	}
}