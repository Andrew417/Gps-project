#ifndef INC_TM4C123_GH6PM_GPIO_H_
#define INC_TM4C123_GH6PM_GPIO_H_


//----------------------------
//Includes
//----------------------------

#include "stdlib.h"
#include "TM4C123GH6PM.h"
#include "Utils.h"


//----------------------------
//Defines
//----------------------------

#define LED_RED 		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)

void GPIO_init(void);

#endif 