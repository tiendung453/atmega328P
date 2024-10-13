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
	TWDR = data; // ??t d? li?u vào TWDR
	TWCR = (1 << TWINT) | (1 << TWEN); // Xóa c? TWINT ?? b?t ??u truy?n
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