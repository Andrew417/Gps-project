/*
 * Utils.h
 *
 *  Created on: Apr 18, 2025
 *      Author: Mina Fathy
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg, bit) 	 		(reg  |=  (1 << bit))
#define ClearBit(reg, bit) 	 	(reg  &= ~(1 << bit))
#define ToggleBit(reg, bit)	 	(reg  ^=  (1 << bit))
#define GetBit(reg, bit)	 		((reg &   (1 << bit)) >> bit)
#define GetReg(reg, bit)			(reg & 0xFF)


#endif
