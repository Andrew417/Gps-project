#ifndef SWITCH_H_
#define SWITCH_H_

#include <stdint.h>
#include "LCD.h"
#include "GPS.h"
#include "tm4c123gh6pm.h"

#define EnableInterrupts()  __enable_irq()

void PortF_Init(void);
void Interrupt_Init(void);
void GPIOF_Handler(void);


#endif 