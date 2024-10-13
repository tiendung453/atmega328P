/*
 * lcd_i2c.c
 *
 * Created: 9/28/2024 3:43:27 AM
 *  Author: DungLT
 */ 
#include "lcd_i2c.h"
void lcdCommand(unsigned char cmd)
{
	TWDR = 
}

void lcdData(unsigned char data)
{

}

void lcd_init()
{

}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char arr[] = {0x80, 0xC0, 0x94, 0xD4};
	lcdCommand(arr[y-1] + (x-1));
	_delay_us(200);
}

void lcd_print(char *str)
{
	unsigned char i = 0;
	while (str[i] != 0)
	{
		lcdData(str[i]);
		i++;
	}
}
