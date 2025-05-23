/*
 ============================================================================
 Name        : TM4C123_GH6PM_UART.h
 Author      : Ereeny Awany Wahba, Andrew Ehab, Kyrolos Essam
 ============================================================================
 */


#ifndef INC_TM4C123_GH6PM_UART_H_
#define INC_TM4C123_GH6PM_UART_H_


//----------------------------
//Includes
//----------------------------
#include "stdlib.h"
#include "TM4C123GH6PM.h"
#include "TM4C123_GH6PM_GPIO.h"
#include "Utils.h"
#include "string.h"
#include "stdint.h"
#include "math.h"
#include "LCD.h"
#include "stdio.h"


//----------------------------
//APIs
//----------------------------
void UART_Init(void);
char UART_InChar(void);
void UART_OutChar(char data);
void UART_OutString(char *pt);
void UART_Outint(int num);
void UART_getCommand1(char *command , int len);


#endif 