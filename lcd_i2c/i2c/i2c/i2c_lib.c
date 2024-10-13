/*
 * i2c_lib.c
 *
 * Created: 9/28/2024 10:37:11 AM
 *  Author: DungLT
 */ 
#include "i2c_lib.h"
void i2c_init()
{
	TWBR = 0x47; // f_scl = 50 cho xtal = 8 Mhz
	TWSR = 0x00; // prescaler = 1;
	TWCR = 0x04;
}

void i2c_write(unsigned char data)
{
	TWDR = data; // ??t d? li?u v�o TWDR
	TWCR = (1 << TWINT) | (1 << TWEN); // X�a c? TWINT ?? b?t ??u truy?n
	while (!(TWCR & (1 << TWINT))); // Ch? cho TWINT ???c thi?t l?p l?i
}

void i2c_start(void)
{
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
	/*x�a bit twint bang c�ch ghi 1 v�o bit n�y 
	bit twen k�ch hoat i2c khi bit th� twi ki?m so�t c�c ch�n sda v� scl
	 twsta bit th� th�nh master  */
	while (!(TWCR & (1 << TWINT)));
	// cho co duoc thiet lap cho bit start 
}

void i2c_stop()
{
	TWCR =(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}