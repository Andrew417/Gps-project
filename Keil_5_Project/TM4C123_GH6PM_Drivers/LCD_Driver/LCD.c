#include "LCD.h"
#include "TM4C123_GH6PM_GPIO.h"


//vdd,anode 15(3.3)
//vss,CATHode16(gnd)
//RS(PD0),RW(PD1),EN(PD2)
//D7(PB0),D6(PB1),D5(PB5),D4(PD3),D3(PB4),D2(PA5),D1(PA6),D0(PA7)
//Previous: D5(E4), D4(E5)



void passdata(unsigned char data)//data = 8 bit hexa
{
	//D0=PA7
	if(data &0x01){GPIO_PORTA_DATA_R |=(1<<7);}
	else          {GPIO_PORTA_DATA_R &=(~(1<<7));}
	
	//D1=PA6
	if(data &0x02){GPIO_PORTA_DATA_R |=(1<<6);}
	else          {GPIO_PORTA_DATA_R &=(~(1<<6));}
	
	//D2=PA5
	if(data &0x04){GPIO_PORTA_DATA_R |=(1<<5);}
	else          {GPIO_PORTA_DATA_R &=(~(1<<5));}
	
	//D3=PB4
	if(data &0x08){GPIO_PORTB_DATA_R |=(1<<4);}
	else          {GPIO_PORTB_DATA_R &=(~(1<<4));}
	
	//D4=PD3
	if(data &0x10){GPIO_PORTD_DATA_R |=(1<<3);}
	else          {GPIO_PORTD_DATA_R &=(~(1<<3));}
	
	//D5=PB5
	if(data &0x20){GPIO_PORTB_DATA_R |=(1<<2);}
	else          {GPIO_PORTB_DATA_R &=(~(1<<2));}
	
	//D6=PB1
	if(data &0x40){GPIO_PORTA_DATA_R |=(1<<1);}
	else          {GPIO_PORTB_DATA_R &=(~(1<<1));}
	
	//D7=PB0
	if(data &0x80){GPIO_PORTB_DATA_R |=(1);}
	else          {GPIO_PORTB_DATA_R &=(~(1));}
}
//
void lcd_data(unsigned char data)
{
	//pass the 8bit data to datalines
	passdata(data);
	//turn on r/w
	GPIO_PORTD_DATA_R &=(~(1<<1));
	//turn on rs for writing 
	GPIO_PORTD_DATA_R |=(1);
	//turn on EN 
	GPIO_PORTD_DATA_R |=(1<<2);
	// wait
	delay(5000);
	// turn off EN
	GPIO_PORTD_DATA_R &=(~(1<<2));
}
//
void lcd_cmd(unsigned char cmd)
{
	//pass the 8bit data to datalines
	passdata(cmd);
	//turn on r/w
	GPIO_PORTD_DATA_R &=(~(1<<1));
	//turn off rs for writing 
	GPIO_PORTD_DATA_R &=(~(1));
	//turn on EN 
	GPIO_PORTD_DATA_R |=(1<<2);
	// wait
	delay(5000);
	// turn off EN
	GPIO_PORTD_DATA_R &=(~(1<<2));
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
