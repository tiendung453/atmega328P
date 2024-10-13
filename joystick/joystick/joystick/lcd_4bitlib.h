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

#define LCD_PTR PORTB		
#define LCD_DDR DDRB		
#define LCD_PIN PINB	

#define LCD_RS 4		
#define LCD_EN 5		

void lcdCommand (unsigned char cmd);
void lcdData (unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);
void lcd_clear();



#endif /* LCD_4BITLIB_H_ */