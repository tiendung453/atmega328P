/*
 * step.c
 *
 * Created: 9/12/2024 9:07:41 PM
 *  Author: DungLT
 */ 
#include "step.h"
static uint16_t time_delay = 50;
static uint16_t min_delay = 5;
static uint16_t max_delay = 100;
static uint16_t step = 5;

static double debounce = 3;
char buff_step[10];

void delay_ms(double d)
{
	while (d--) {
		_delay_ms(1);
	}
}

void clock_wise()
{
	PORTB = 0x03;
	delay_ms(time_delay);
	PORTB = 0x05; 
	delay_ms(time_delay);
	PORTB = 0x09;
	delay_ms(time_delay);
	PORTB = 0x11;
    delay_ms(time_delay);
}

void counter_clock_wise()
{
    PORTB = 0x11;
    delay_ms(time_delay);
    PORTB = 0x09;
    delay_ms(time_delay);
    PORTB = 0x05;
    delay_ms(time_delay);
    PORTB = 0x03;
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
	PORTB = 0x00;
}

void key_delay() 
{
	for (uint8_t i = 0; i < 7; i++)
	{
		delay_ms(debounce);
	}
}

void display_step()
{
	sprintf(buff_step,"%2d",time_delay);
	lcd_gotoxy(6,2);
	lcd_print(buff_step);
}