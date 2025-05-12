/*
 ============================================================================
 Name        : Systick.h
 Author      : Ereeny Awany, Martina Reda
 Description : Header for SysTick driver, C99
 ============================================================================
 */
 
#ifndef SYSTICH_H_
#define SYSTICH_H_

//----------------------------
//Includes
//----------------------------
#include "TM4C123.h"
#include <TM4c123gh6pm.h>
#include "stdio.h"
#include "stdlib.h"

//----------------------------
//APIs
//----------------------------
void delay_ms(uint32_t delay);
void SysTick_Init(void);


#endif