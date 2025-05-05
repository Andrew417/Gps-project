#include "TM4C123.h"
#include <TM4c123gh6pm.h>
#ifndef LCD_H_
#define LCD_H_


void delay_ms (uint32_t ms);

void passdata(unsigned char data);

void lcd_data(unsigned char data);

void lcd_cmd(unsigned char cmd);

void lcdstring( char *str );

void LCD_init(void);

void SysTick_Init(void);

void SysTick_Wait_1_ms(uint32_t delay);

void float_to_string(float distance);
#endif