#include "LCD.h"
#include "TM4C123.h"


//vdd,anode 15(3.3)
//vss,CATHode16(gnd)
//RS(PD0),RW(PD1),EN(PD2)
//D7(PA7),D6(PA6),D5(PA5),D4(PB4),D3(PE5),D2(PE4),D1(PB1),D0(PB0)




void passdata(unsigned char data)//data = 8 bit hexa
{
	//D0=PB0
	if(data &0x01){GPIOB->DATA = GPIOA->DATA |(1);}
	else          {GPIOB->DATA = GPIOA->DATA &(~(1));}
	
	//D1=PB1
	if(data &0x02){GPIOB->DATA = GPIOA->DATA |(1<<1);}
	else          {GPIOB->DATA = GPIOA->DATA &(~(1<<1));}
	
	//D2=PE4
	if(data &0x04){GPIOE->DATA = GPIOA->DATA |(1<<2);}
	else          {GPIOE->DATA = GPIOA->DATA &(~(1<<2));}
	
	//D3=PE5
	if(data &0x08){GPIOE->DATA = GPIOA->DATA |(1<<3);}
	else          {GPIOE->DATA = GPIOA->DATA &(~(1<<3));}
	
	//D4=PB4
	if(data &0x10){GPIOB->DATA = GPIOA->DATA |(1<<4);}
	else          {GPIOB->DATA = GPIOA->DATA &(~(1<<4));}
	
	//D5=PA5
	if(data &0x20){GPIOA->DATA = GPIOA->DATA |(1<<5);}
	else          {GPIOA->DATA = GPIOA->DATA &(~(1<<5));}
	
	//D6=PA6
	if(data &0x40){GPIOA->DATA = GPIOA->DATA |(1<<6);}
	else          {GPIOA->DATA = GPIOA->DATA &(~(1<<6));}
	
	//D7=PA7
	if(data &0x80){GPIOA->DATA = GPIOA->DATA |(1<<7);}
	else          {GPIOA->DATA = GPIOA->DATA &(~(1<<7));}
}
//
void lcd_data(unsigned char data)
{
	//pass the 8bit data to datalines
	passdata(data);
	//turn on r/w
	GPIOD->DATA = GPIOD->DATA &(~(1<<1));
	//turn on rs for writing 
	GPIOD->DATA = GPIOD->DATA |(1);
	//turn on EN 
	GPIOD->DATA = GPIOD->DATA |(1<<2);
	// wait
	delay(5000);
	// turn off EN
	GPIOD->DATA = GPIOD->DATA &(~(1<<2));
}
//
void lcd_cmd(unsigned char cmd)
{
	//pass the 8bit data to datalines
	passdata(cmd);
	//turn on r/w
	GPIOD->DATA = GPIOD->DATA &(~(1<<1));
	//turn off rs for writing 
	GPIOD->DATA = GPIOD->DATA &(~(1));
	//turn on EN 
	GPIOD->DATA = GPIOD->DATA |(1<<2);
	// wait
	delay(5000);
	// turn off EN
	GPIOD->DATA = GPIOD->DATA &(~(1<<2));
}
//
void lcdstring(unsigned char *str ,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		lcd_data(str[i]);
	}
}
//
void LCD_init(void)
{
	//8bit mode utilising 16 columns,2rows
	lcd_cmd(0x38);
	//entry mode set
	lcd_cmd(0x06);
	//display on,cursor on
	lcd_cmd(0x0c);
	//clear
	lcd_cmd(0x01);
}
//
void delay(long d)
{
    while(d--);
	
}
