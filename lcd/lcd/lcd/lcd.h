/*
 * lcd.h
 *
 * Created: 9/7/2024 12:10:11 PM
 *  Author: DungLT
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "keypad.h"
#include "calc.h"

// khai bao chan data
#define LCD_PORTB PORTB // config port data
#define LCD_DDRB DDRB // config ddr data
#define LCD_PINB PINB // lcd data pin

// khai bao chan command
#define LCD_PORTC PORTC
#define LCD_DDRC DDRC
#define LCD_PINC PINC

// khai bao chan rs rw en
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void delay_us(unsigned int d);
void lcdCommand( unsigned char cmd);
void lcdData (unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);

#endif /* LCD_H_ */