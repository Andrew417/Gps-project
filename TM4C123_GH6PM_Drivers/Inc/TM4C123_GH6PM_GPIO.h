/*
 ============================================================================
 Name        : TM4C123_GH6PM_GPIO.h
 Author      : Arsany Hany Anwar
 ============================================================================
 */


#ifndef INC_TM4C123_GH6PM_GPIO_H_
#define INC_TM4C123_GH6PM_GPIO_H_

//----------------------------
//Includes
//----------------------------
#include "stdlib.h"
#include "TM4C123GH6PM.h"
#include "Utils.h"


//----------------------------
//Macros
//----------------------------
#define LED_RED 			(1)
#define LED_BLUE 			(2)
#define LED_GREEN 		(3)



//----------------------------
//APIs
//----------------------------
void GPIO_init(void);

#endif 