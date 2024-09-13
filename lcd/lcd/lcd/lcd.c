/*
 * lcd.c
 *
 * Created: 9/7/2024 12:09:59 PM
 *  Author: DungLT
 */ 
#include "lcd.h"
// tao ham delay
void delay_us(unsigned int d)
{
	while (d--) {
		_delay_us(1); // Dùng h?ng s? tr?c ti?p
	}
}

// tao lenh cmd lcd
void lcdCommand( unsigned char cmd)
{
	LCD_PORTB = cmd; // send cmd to data port
	LCD_PORTC &= ~(1<<LCD_RS); // rs = 0 for command
	LCD_PORTC &= ~(1<<LCD_RW); // rw =0 for write
	LCD_PORTC |= (1<<LCD_EN); // en = 1 for H to L pulse
	delay_us(1); // wait to make en wide
	LCD_PORTC &= ~(1<<LCD_EN); // en = 0 for H to L pulse
	delay_us(100);
}

// tao lenh gui data
void lcdData (unsigned char data)
{
	LCD_PORTB = data; // send data to data port
	LCD_PORTC |= (1<<LCD_RS); // rs = 1 for data
	LCD_PORTC &= ~(1<<LCD_RW); // rw =0 for write
	LCD_PORTC |= (1<<LCD_EN); // en = 1 for H to L pulse
	delay_us(1);
	LCD_PORTC &= ~(1<<LCD_EN); // en = 0 for H to L pulse
	delay_us(100);
}

// tao 1 khoi khai bao lcd
void lcd_init()
{
	LCD_DDRB = 0xFF;
	LCD_DDRC = 0xFF;
	
	LCD_PORTC &= ~(1<<LCD_EN); // en = 0 for H to L pulse
	delay_us(2000);				// wait for init
	
	lcdCommand(0x38);    // lcd 2 line 5x8 matrix
	lcdCommand(0x0C); // bat hien thi va con tro
	lcdCommand(0x01); // clear lcd
	delay_us(2000);
	lcdCommand(0x06); // dich con tro sang phai
}

// ham di chuyen con tro
void lcd_gotoxy(unsigned char x, unsigned char y)
{
	if (x > 16 || y > 2) // Ki?m tra các giá tr? h?p l?
	return;
	unsigned char firstCharAdd[]={0x80, 0xC0, 0x94, 0xD4};
	lcdCommand(firstCharAdd[y-1]+x-1);
	delay_us(100);
}

// ham in len lcd
void lcd_print(char *str)
{
	unsigned char i = 0;
	while(str[i] != 0)
	{
		lcdData(str[i]);
		i++;
	}
}
