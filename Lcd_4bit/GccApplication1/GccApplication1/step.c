/*
 * step.c
 *
 * Created: 9/12/2024 9:07:41 PM
 *  Author: DungLT
 */ 
#include "step.h"

static double time_delay = 50;
static double min_delay = 2;
static double max_delay = 100;
static double step = 2;

static double debounce = 3;

void delay_ms(double d)
{
	while (d--) {
		_delay_ms(1);
	}
}

void clock_wise()
{
	PORTD = 0x01;
	delay_ms(time_delay);
	PORTD = 0x02; 
	delay_ms(time_delay);
	PORTD = 0x04;
	delay_ms(time_delay);
	PORTD = 0x08;
    delay_ms(time_delay);
}

void counter_clock_wise()
{
    PORTD = 0x08;
    delay_ms(time_delay);
    PORTD = 0x04;
    delay_ms(time_delay);
    PORTD = 0x02;
    delay_ms(time_delay);
    PORTD = 0x01;
    delay_ms(time_delay);
}

void increase_speed()
{
	if(time_delay > min_delay)
	{
		time_delay -= step;
	}
	else if(time_delay == min_delay)
	{
		time_delay = min_delay;
	}
}

void decrease_speed()
{
	if(time_delay < max_delay)
	{
		time_delay += step;
	}
	else if(time_delay == max_delay)
	{
		time_delay = max_delay;
	}
}

void stop_motor()
{
	PORTD = 0x00;
}

void key_delay() 
{
	for (uint8_t i = 0; i < 7; i++)
	{
		delay_ms(debounce);
	}
}