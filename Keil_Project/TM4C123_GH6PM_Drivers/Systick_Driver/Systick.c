// Systick.c - Implementation of SysTick driver

#include "Systick.h"


void delay_ms(uint32_t ms) {
    SysTick_Wait_1_ms(ms);
}
//
void SysTick_Init(void){

 SysTick->CTRL= 0; 
 SysTick->LOAD = 16000 - 1; 
 SysTick->VAL = 0;   
 SysTick->CTRL = 0x00000005; 
 }
//
 void SysTick_Wait_1_ms(uint32_t delay) {
    unsigned long i;
    for (i = 0; i < delay; i++) {
        while ((SysTick->CTRL & 0x10000) == 0); // Wait for COUNT flag
    }
}