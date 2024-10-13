/*
 * i2c.c
 *
 * Created: 9/26/2024 10:33:34 PM
 * Author : DungLT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS 0
#define LCD_EN 1

void i2c_init()
{
	TWBR = 0x47; // f_scl = 50 cho xtal = 8 Mhz
	TWSR = 0x00; // prescaler = 1;
	TWCR = 0x04;
}

void i2c_write(unsigned char data)
{
	TWDR = data; // dat du lieu vào TWDR
	TWCR = (1 << TWINT) | (1 << TWEN); // Xóa co TWINT ?? b?t ??u truy?n
	while (!(TWCR & (1 << TWINT))); // Ch? cho TWINT ???c thi?t l?p l?i
}

void i2c_start(void)
{
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
	/*xóa bit twint bang cách ghi 1 vào bit này 
	bit twen kích hoat i2c khi bit thì twi ki?m soát các chân sda và scl
	 twsta bit thì thành master  */
	while (!(TWCR & (1 << TWINT)));
	// cho co duoc thiet lap cho bit start 
}

void i2c_stop()
{
	TWCR =(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void lcdCommand(unsigned char cmd)
{
	TWDR = (TWDR & 0x0F)|(cmd & 0xF0);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR &= ~(1 << LCD_RS);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR |= (1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	_delay_us(1);
	
	TWDR &= ~(1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	_delay_us(20);
	
	TWDR = (TWDR & 0x0F)|(cmd << 4);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR |= (1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	_delay_us(1);
	
	TWDR &= ~(1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void lcdData(unsigned char data)
{
	TWDR = (TWDR & 0x0F)|(data & 0xF0);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR |= (1 << LCD_RS);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR |= (1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	_delay_us(1);
	
	TWDR &= ~(1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	TWDR = (TWDR & 0x0F)|(data << 4);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	TWDR |= (1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	
	_delay_us(1);
	
	TWDR &= ~(1 << LCD_EN);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void lcd_init()
{
	TWDR &= ~(1 << LCD_EN);
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


int main(void)
{
    /* Replace with your application code */
	i2c_init();
	i2c_start();
	i2c_write(0x4E);
	lcd_init();
	lcd_gotoxy(1,1);
	lcd_print("abcdefg");
	i2c_stop();
	
	
    while (1) 
    {
    }
}

