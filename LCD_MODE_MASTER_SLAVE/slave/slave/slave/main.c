/*
 * master_mode_i2c.c
 *
 * Created: 9/28/2024 4:04:41 PM
 * Author : DungLT
 */ 

#include <avr/io.h>
#include "lcd_4bitlib.h"

void i2c_slave_init(unsigned char slaveAddress)
{
	TWSR = 0x04;
	TWAR =  slaveAddress;
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);
}

unsigned char i2c_read_status(void)
{
	unsigned char i = 0;
	i = TWSR & 0xF8;
	return i;
}

unsigned char i2c_received(unsigned char islast)
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

void i2c_slave_listen()
{
	while((TWCR & (1 << TWINT)) == 0);
}

void i2c_showError(unsigned char er)
{
	DDRB = 0xFF;
	PORTB = er;
}


int main(void)
{
	DDRB = 0xFF;
    i2c_slave_init(0b00000010);
	i2c_slave_listen();
	
	unsigned char s,i;
	s = i2c_read_status();
	if(s != 0x60)
	{
		i2c_showError(s);
		return 0;
	}
	i = i2c_received(0);
	s = i2c_read_status();
	if(s != 0x80)
	{
		i2c_showError(s);
		return 0;
	}

	PORTB = i;
    while (1);
	return 0;
}

