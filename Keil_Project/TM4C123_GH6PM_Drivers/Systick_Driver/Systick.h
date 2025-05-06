// Systick.h - Header for SysTick driver
#ifndef SYSTICH_H_
#define SYSTICH_H_

#include "TM4C123.h"
#include <TM4c123gh6pm.h>
#include "stdio.h"
#include "stdlib.h"

void delay_ms(uint32_t ms);
void SysTick_Init(void);
void SysTick_Wait_1_ms(uint32_t delay);


#endif