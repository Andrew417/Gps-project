/*
 ============================================================================
 Name        : Switch.h
 Author      : Julia Nasser, Sief Waleed
 Description : Header of SysTick driver, C99
 ============================================================================
 */
 
#ifndef SWITCH_H_
#define SWITCH_H_

//----------------------------
//Includes
//----------------------------
#include <stdint.h>
#include "LCD.h"
#include "GPS.h"
#include "tm4c123gh6pm.h"

//----------------------------
//Macros
//----------------------------
#define EnableInterrupts()  __enable_irq()

//----------------------------
//APIs
//----------------------------
void Interrupt_Init(void);
void GPIOF_Handler(void);


#endif 