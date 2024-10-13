/*
 * master_mode_i2c.c
 *
 * Created: 9/28/2024 4:04:41 PM
 * Author : DungLT
 */ 

#include <avr/io.h>
#include "lcd_4bitlib.h"

void i2c_start()
{
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTA);
	while(!(TWCR & (1 <<TWINT)));
}

void i2c_stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while(!(TWCR & (1 <<TWINT)));
}

void i2c_master_trasmit(unsigned char data)
{
	TWDR = data;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 <<TWINT)));
}

void i2c_master_init()
{
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = 0x04;
}

unsigned char i2c_read_status(void)
{
	unsigned char i = 0;
	i = TWSR & 0xF8;
	return i;
}

unsigned char i2c_read_data(unsigned char islast)
{
	if(islast == 0)
	{
		TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);
	}
	else 
	{
		TWCR = (1 << TWINT)|(1 << TWEN);
	}
	while((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

void i2c_showError(unsigned char er)
{
	DDRB = 0xFF;
	PORTB = er;
}


int main(void)
{
	DDRB = 0xFF;
	unsigned char s;
    i2c_master_init();
	i2c_start();
	s = i2c_read_status();
	if(s != 0x08)
	{
		i2c_showError(s);
		return 0;
	}
	i2c_master_trasmit(0b00000010);
	s = i2c_read_status();
	if(s != 0x18)
	{
		i2c_showError(s);
		return 0;
	}
	i2c_master_trasmit(0b11111000);
	s = i2c_read_status();
	if(s != 0x28)
	{
		i2c_showError(s);
		return 0;
	}
	i2c_stop();
	
    while (1);
	return 0;
}

