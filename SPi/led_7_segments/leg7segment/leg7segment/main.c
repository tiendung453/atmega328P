/*
 * spi_max7221.c
 *
 * Created: 7/14/2020 8:49:34 PM
 * Author : https://aki-technical.blogspot.com
 */ 

#include <avr/io.h>

#define F_CPU 4000000UL
#include <util/delay.h>

#define MOSI 3
#define SCK 5
#define SS 2
void spi_init(void)
{
	DDRB = (1 << MOSI)|(1 << SCK)|(1 << SS);
	SPCR = (1 << SPE)|(1 << MSTR);
}
void spi_send_data(unsigned char cmd, unsigned char data)
{
	PORTB &= ~(1 << SS);
	SPDR = cmd; // g?i l?nh cmd 
	while (!(SPSR & (1 << SPIF))); // ??i khi truy?n xong 
	SPDR = data; // send data
	while (!(SPSR & (1 << SPIF)));
	PORTB |= (1 << SS);
}

int main(void)
{
	spi_init();
	spi_send_data(0x09,0xFF);
	spi_send_data(0x0B, 0x01);
	spi_send_data(0x0C, 0x01);
	spi_send_data(0x0A, 0x09);
	spi_send_data(0x01, 5);
	spi_send_data(0x02, 6);
    while (1) 
    {
	}
}