
#ifndef INC_TM4C123_GH6PM_UART_H_
#define INC_TM4C123_GH6PM_UART_H_


//----------------------------
//Includes
//----------------------------

#include "stdlib.h"
#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "Utils.h"

void UART_Init(void);
char UART_InChar(void);
void UART_OutChar(char data);
void UART_OutString(char *pt);
void getCommand1(char *command , int len);

#endif /* INC_TM4C123_GH6PM_UART_H_*/