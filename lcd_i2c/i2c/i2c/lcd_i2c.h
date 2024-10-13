/*
 * lcd_i2c.h
 *
 * Created: 9/28/2024 3:43:40 AM
 *  Author: DungLT
 */ 


#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "i2c_lib.h"

#define LCD_RS 0			// lcd rs
#define LCD_RW 1			// lcd rw
#define LCD_EN 2			// lcd en

void lcdCommand (unsigned char cmd);
void lcdData (unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);


#endif /* LCD_I2C_H_ */