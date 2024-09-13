/*
 * atmel.c
 *
 * Created: 8/31/2024 1:36:50 PM
 * Author : DungLT
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
void tDelay();

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB |= (1 << PORTB4);
    while (1) 
    {
		tDelay();
		PORTB = PORTB ^0x10;
    }
}

void tDelay()
{
		TCNT0 = 116;
		TCCR0B = (1<<CS01);
		while((TIFR0&(1 << TOV0)) == 0);
		TCCR0B = 0;
		TIFR0 = 0x1;
}