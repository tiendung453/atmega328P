#include "lcd_4bitlib.h"

void lcdCommand(unsigned char cmd)
{
	LCD_PTR = (LCD_PTR & 0x0F) | (cmd & 0xF0);
	LCD_PTR &= ~(1 << LCD_RS);					// rs = 0
	LCD_PTR &= ~(1 << LCD_RW);					// rw = 0 for write
	LCD_PTR |= (1 << LCD_EN);					// en = 1
	_delay_us(10);
	LCD_PTR &= ~(1 << LCD_EN);					// en = 0
	_delay_us(20);
	LCD_PTR = (LCD_PTR & 0x0F) | (cmd << 4);
	LCD_PTR |= (1 << LCD_EN);					// en = 1
	_delay_us(10);
	LCD_PTR &= ~(1 << LCD_EN);					// en = 0
}

void lcdData(unsigned char data)
{
	LCD_PTR = (LCD_PTR & 0x0F) | (data & 0xF0);
	LCD_PTR |= (1 << LCD_RS);					// rs = 1
	LCD_PTR &= ~(1 << LCD_RW);					// rw = 0
	LCD_PTR |= (1 << LCD_EN);					// en = 1
	_delay_us(10);
	LCD_PTR &= ~(1 << LCD_EN);					// en = 0
	LCD_PTR = (LCD_PTR & 0x0F) | (data << 4);
	LCD_PTR |=	(1 << LCD_EN);					// en = 1
	_delay_us(10);
	LCD_PTR &= ~(1 << LCD_EN);
}

void lcd_init()
{
	LCD_DDR = 0xFF;
	LCD_PTR &= ~(1 << LCD_EN);
	_delay_us(2000);
	lcdCommand(0x33);
	_delay_us(100);
	lcdCommand(0x32);
	_delay_us(100);
	lcdCommand(0x28);
	_delay_us(100);
	lcdCommand(0x0C);
	_delay_us(100);
	lcdCommand(0x01);
	_delay_us(100);
	lcdCommand(0x06);
	_delay_us(100);
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
