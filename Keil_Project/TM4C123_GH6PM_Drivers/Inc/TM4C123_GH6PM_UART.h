
#ifndef INC_TM4C123_GH6PM_UART_H_
#define INC_TM4C123_GH6PM_UART_H_


//----------------------------
//Includes
//----------------------------

#include "stdlib.h"
#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "Utils.h"

void UART7_Init(void);
char UART7_InChar(void);
void UART7_OutChar(char data);
void UART7_OutString(char *pt);
void UART7_getCommand1(char *command , int len);

#endif /* INC_TM4C123_GH6PM_UART_H_*/