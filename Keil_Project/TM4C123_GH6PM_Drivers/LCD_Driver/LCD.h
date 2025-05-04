#include "TM4C123.h"
#ifndef LCD_H_
#define LCD_H_


void delay (long d);

void passdata(unsigned char data);

void lcd_data(unsigned char data);

void lcd_cmd(unsigned char cmd);

void lcdstring(unsigned char *str ,int length);

void LCD_init(void);

#endif