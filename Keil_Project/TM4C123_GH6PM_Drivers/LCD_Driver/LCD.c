#include "LCD.h"
//vdd,anode 15(3.3)
//vss,CATHode16(gnd)
// Rs = PD0
// Rw = PD1
// En = PD2
// D0 = PA7, D1 = PA6, D2 = PA5, D3 = PB4
// D4 = PE5, D5 = PE4, D6 = PE1, D7 = PD3

void passdata(unsigned char data)//data = 8 bit hexa
{
	//D0=PA7
	if(data &0x01){GPIOA->DATA |= (1<<7);}
	else          {GPIOA->DATA &= ~(1<<7);}
	
	//D1=PA6
	if(data &0x02){GPIOA->DATA = GPIOA->DATA |(1<<6);}
	else          {GPIOA->DATA = GPIOA->DATA &(~(1<<6));}
	
	//D2=PA5
	if(data &0x04){GPIOA->DATA = GPIOA->DATA |(1<<5);}
	else          {GPIOA->DATA = GPIOA->DATA &(~(1<<5));}
	
	//D3=PB4
	if(data &0x08){GPIOB->DATA = GPIOB->DATA |(1<<4);}
	else          {GPIOB->DATA = GPIOB->DATA &(~(1<<4));}
	
	//D4=PE5
	if(data &0x10){GPIOE->DATA = GPIOE->DATA |(1<<5);}
	else          {GPIOE->DATA = GPIOE->DATA &(~(1<<5));}
	
	//D5=PE4
	if(data &0x20){GPIOE->DATA = GPIOE->DATA |(1<<4);}
	else          {GPIOE->DATA = GPIOE->DATA &(~(1<<4));}
	
	//D6=PE1
	if(data &0x40){GPIOE->DATA = GPIOE->DATA |(1<<1);}
	else          {GPIOE->DATA = GPIOE->DATA &(~(1<<1));}
	
	//D7=PD3
	if(data &0x80){GPIOD->DATA = GPIOD->DATA |(1<<3);}
	else          {GPIOD->DATA = GPIOD->DATA &(~(1<<3));}
}
//
void lcd_data(unsigned char data)
{
	//pass the 8bit data to datalines
	passdata(data);
	//turn on r/w=0
	GPIOD->DATA = GPIOD->DATA &(~(1<<1));
	//turn on rs for writing 
	GPIOD->DATA = GPIOD->DATA |(1);
	//turn on EN 
	GPIOD->DATA = GPIOD->DATA |(1<<2);
	// wait
	delay_ms(5);
	// turn off EN
	GPIOD->DATA = GPIOD->DATA &(~(1<<2));
	delay_ms(5);
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
	delay_ms(1);
	// turn off EN
	GPIOD->DATA = GPIOD->DATA &(~(1<<2));
	delay_ms(2);
}
//
void lcd_string( char *str )
{
	
	while(*str)
	{
		lcd_data(*str++);
	}
}
//
void LCD_init(void)
{
	 SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1) | (1 << 1) | (1 << 3) | (1<< 4); // Enable Port A, B, D, E
   while ((SYSCTL->PRGPIO = SYSCTL->PRGPIO & ((1) | (1 << 1) | (1 << 3) | (1 << 4))) == 0);

    //inti pins
   GPIOA->DIR = GPIOA->DIR|(1 << 7) | (1<< 6) | (1 << 5);
   GPIOA->DEN = GPIOA->DEN| (1 << 7) | (1 << 6) | (1 << 5);

   GPIOB->DIR = GPIOB->DIR| (1 << 4);
   GPIOB->DEN = GPIOB->DEN| (1 << 4);

   GPIOE->DIR = GPIOE->DIR| (1 << 5) | (1 << 4) | (1 << 1);  
   GPIOE->DEN = GPIOE->DEN| (1 << 5) | (1 << 4) | (1 << 1);

    
   GPIOD->DIR = GPIOD->DIR| (1) | (1 << 1) | (1 << 2) | (1 << 3);
   GPIOD->DEN = GPIOD->DEN| (1) | (1 << 1) | (1 << 2) | (1 << 3);

   SysTick_Init();   // Initialize SysTick for delays

	//8bit mode utilising 16 columns,2rows
	lcd_cmd(0x38);
	//entry mode set
	lcd_cmd(0x06);
	//display on,cursor on
	lcd_cmd(0x0c);
	//clear
	lcd_cmd(0x01);
	delay_ms(5);
	
}
//
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
 
void LCD_Print_int(uint16_t number)
{
	char dist[20];
	sprintf(dist,"%d",number);
	lcd_string(dist);
}

void LCD_Print_float(float distance){
  char dist[20];
	sprintf(dist,"%.2f",distance);
	lcd_string(dist);
}