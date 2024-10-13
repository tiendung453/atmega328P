/*
 * button_pcint.c
 *
 * Created: 9/17/2024 7:04:45 PM
 * Author : DungLT
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
void pcint_init(void)
{
	DDRC &= ~((1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3));
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	sei();
}

ISR(PCINT1_vect)
{
	if (!(PINC & (1 << PINC0)))
	{
		PORTD |= (1 << PORTD0);
	}
	else PORTD &= ~(1 << PORTD0);
	
	if (!(PINC & (1 << PINC1)))
	{
		PORTD |= (1 << PORTD1);
	}
	else PORTD &= ~(1 << PORTD1);

	if (!(PINC & (1 << PINC2)))
	{
		PORTD |= (1 << PORTD2);
	}
	else PORTD &= ~(1 << PORTD2);
	
	if (!(PINC & (1 << PINC3)))
	{
		PORTD |= (1 << PORTD3);
	}
	else PORTD &= ~(1 << PORTD3);
}
int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRC = 0xF0;
	PORTC = 0xFF;
	pcint_init();
    while (1) 
    {
    }
}

