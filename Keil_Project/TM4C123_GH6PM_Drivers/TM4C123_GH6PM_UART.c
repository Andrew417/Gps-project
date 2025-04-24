#include "TM4C123_GH6PM_GPIO.h"
#include "TM4C123_GH6PM_UART.h"
#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
const int len=128;
char command[len]={0};
#define CR 0x0D

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

char UART_InChar(void){
        while ((UART0_FR_R & 0x10) !=0); //block program untill input is recieved
            return (char)(UART0_DR_R & 0xFF); //return the first 8 bit data
    }
        
void UART_OutChar(char data){
        while ((UART0_FR_R & 0x0020) !=0); //block program untill input is recieved
            UART0_DR_R = data; //return the first 8 bit data
   }
        
void UART_OutString(char *pt){ //to display a message on the screen
        while(*pt){
        UART_OutChar(*pt);
            pt++;
        }
  }
        

<<<<<<< HEAD
 void getCommand1(char *command , int len){ // get the whole command
    char character ;
       int i;
       for (i=0;i<len ; i++){
         character =UART_InChar();
           if ((character !='\r') || (character != CR)){
               command[i]=character;
                  UART_OutChar(command[i]);
           }
           else if (character =='\r' || i==len || character == CR)
               break;
       }
   }
   
=======

>>>>>>> 60f720b8e121275098b8eb958813befd7b27bfc7
