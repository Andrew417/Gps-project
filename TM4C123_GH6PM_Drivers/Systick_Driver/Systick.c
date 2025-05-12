/*
 ============================================================================
 Name        : Systick.C
 Author      : Julia Nasser, Martina Reda
 Description : Implementation of SysTick driver, C99
 ============================================================================
 */
 
#include "Systick.h"

void SysTick_Init(void){

 SysTick->CTRL= 0; 
 SysTick->LOAD = 16000 - 1; 
 SysTick->VAL = 0;   
 SysTick->CTRL = 0x00000005; 
 }

 
 
 void delay_ms(uint32_t delay) {
    unsigned long i;
    for (i = 0; i < delay; i++) {
        while ((SysTick->CTRL & 0x10000) == 0); // Wait for COUNT flag
    }
}