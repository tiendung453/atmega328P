/*
 * joystick.c
 *
 * Created: 10/7/2024 7:59:06 PM
 * Author : DungLT
 */ 

#include "lcd_4bitlib.h"
#include "uart.h"
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t speed = 0;
uint8_t maxSpeed = 255;
uint8_t minSpeed = 0;
volatile uint8_t mode = 0;
volatile uint8_t running = 0;
volatile uint8_t direction = 0;

void speedUp()
{
	if((speed > 0) && (speed < 255))
	{
		speed = speed + 10;
		OCR0A = speed;
	}
	else if( speed <= 0)
	{
		speed = 0;
		OCR0A = speed;
	}
	else
	{
		speed = 255;
		OCR0A = speed;
	}
}

void speedDown()
{
		if((speed > 0) && (speed < 255))
		{
			speed = speed - 10;
			OCR0A = speed;
		}
		else if( speed <= 0)
		{
			speed = 0;
			OCR0A = speed;
		}
		else
		{
			speed = 255;
			OCR0A = speed;
		}
}

void delay_ms(uint8_t time_delay)
{
	for(int i = 0; i< time_delay;i++)
	{
		_delay_ms(1);
	}
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ADC_Init()
{
	ADMUX = (1 << REFS0);
	ADCSRA |= (1 << ADPS2)|(1 << ADPS0)|(1 <<ADIE)|(1 << ADEN);
}

int ADC_Read(unsigned char channel)
{
	ADMUX = 0x40|(channel & 0x07);
	_delay_ms(1);
	
	return ADCW;
}

ISR(ADC_vect)
{
	int ADC_Val = ADC_Read(0);
	speed = map(ADC_Val, 0, 1023, minSpeed, maxSpeed);
	OCR0A = speed;
	ADCSRA |= (1 << ADSC);
}


void PWM_Init()
{
	DDRD |= (1 << DDD6);
	TCCR0A = (1 << WGM00)|(1 << COM0A1);
	TCCR0B = (1 << CS00);
	OCR0A = 248;
}

void Set_Motor(uint8_t on,uint8_t dir)
{
	DDRD |=(1 << DDD2)|(1 << DDD3);
	if(on == 1)
	{
		if(dir == 1)
		{
			PORTD = (1 << PORTD2);
			PORTD &= ~(1 << PORTD3);
		}
		else if(dir == -1)
		{
			PORTD |= (1 << PORTD3);
			PORTD &= ~(1 << PORTD2);
		}
	}
	else if((on == 0) && (dir == 0))
	{
		PORTD = 0x00;
	}
}

void pcint_init(void)
{
	DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3));
	PORTC = (1 << PORTC0)|(1 << PORTC1)|(1 << PORTC2)|(1 << PORTC3);
	DDRD &= ~(1 << DDD4);
	PORTD |= (1 << PORTC4);
	PCICR |= (1 << PCIE1)|(1 << PCIE2);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	PCMSK2 |= (1 << PCINT20);
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
}

ISR(PCINT2_vect)
{
	if (!(PIND & (1 << PIND4)))
	{
		mode = 5;
	}
}

void select_mode()
{
	switch(mode)
	{
		case 1:
			Set_Motor(1,1);
			break;
		case 2:
			Set_Motor(1,-1);
			break;
		case 3:
			speedUp();
			if(running == 1)
			{
				if(direction == 1) mode = 1;
				else if(direction == 2) mode = 2;
			}
			break;
		case 4:
			speedDown();
			if(running == 1)
			{
				if(direction == 1)mode = 1;
				else if(direction == 2) mode = 2;
			}
			break;
		case 5:
			Set_Motor(0,0);
			break;
		
	}
}



int main(void)
{
	
	//ADC_Init();
	pcint_init();
	PWM_Init();
	//ADCSRA |= (1 << ADSC);
	sei();
	DDRD = 0xFF;
    while (1) 
    {
		PORTD = mode;
    }
}

