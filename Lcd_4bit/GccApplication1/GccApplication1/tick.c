/*
 * tick.c
 *
 * Created: 9/17/2024 3:55:15 PM
 *  Author: DungLT
 */ 

#include "tick.h"
uint32_t tick_count = 0;
uint8_t mode = 0; 
uint8_t running = 0;
uint8_t direction = 0; 


char buff[10];

void timer1_init(void)
{
	TCCR1B |= (1 << WGM12);
	OCR1A = 249;
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS11) | (1 << CS10);
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	tick_count++;
}

uint32_t GetTick(void)
{
	uint32_t ticks;
	
	cli();
	ticks = tick_count;
	sei();
	
	return ticks;
}

void pcint_init(void)
{
	DDRC &= ~((1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3));
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	sei();
}

ISR(PCINT1_vect)
{
	if (!(PINC & (1 << PINC0)) )
	{
		mode = 1;
		running = 1;
		direction = 1;
	} 
	
	if (!(PINC & (1 << PINC1)))
	{
		mode = 2;
		running = 1;
		direction = 2;
	}

	if (!(PINC & (1 << PINC2)))
	{
		mode = 3;
	}
	
	if (!(PINC & (1 << PINC3)))
	{
		mode = 4;
	}
}

void select_mode()
{
	switch(mode)
	{
		case 1:
			clock_wise();
			break;
		case 2:
			counter_clock_wise();
			break;
		case 3:
			increase_speed();
//			if(running == 1)
//			{
//				if(direction == 1) mode = 1;
//				else if(direction == 2) mode = 2;
//			}
			break;
		case 4:
			decrease_speed();
//			if(running == 1)
//			{
//				if(direction == 1)mode = 1;
//				else if(direction == 2) mode = 2;
//			}
			break;
	}
}

void display_mode()
{
	sprintf(buff,"%2d",mode);
	lcd_gotoxy(1,2);
	lcd_print(buff);
}
