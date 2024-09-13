/*
 * lcd_4bitlib.h
 *
 * Created: 9/10/2024 11:00:04 PM
 *  Author: DungLT
 */ 


#ifndef LCD_4BITLIB_H_
#define LCD_4BITLIB_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_PTR PORTB		// lcd data port 
#define LCD_DDR DDRB		// lcd data ddr
#define LCD_PIN PINB		// lcd data pin

#define LCD_RS 0			// lcd rs
#define LCD_RW 1			// lcd rw
#define LCD_EN 2			// lcd en 

void lcdCommand (unsigned char cmd);
void lcdData (unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);




#endif /* LCD_4BITLIB_H_ */