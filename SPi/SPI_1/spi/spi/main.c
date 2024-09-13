/*
 * spi.c
 *
 * Created: 8/31/2024 10:03:34 PM
 * Author : DungLT
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#define MOSI 3
#define SCK 5



int main(void)
{
    /* Replace with your application code */
	DDRB = (1 << MOSI) | (1<<SCK);
	DDRD = 0xFF;
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
    while (1) 
    {
		SPDR = 'G';
		while(!(SPSR &(1<<SPIF)));
		PORTD = SPDR;
    }
	return 0;
}

