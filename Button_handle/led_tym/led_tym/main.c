/*
 * led_tym.c
 *
 * Created: 8/28/2024 3:45:51 PM
 * Author : DungLT
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include<stdint.h>
#include<util/delay.h>

void write_pin(volatile uint8_t *PORTx, char PORTxn, int val)
{
	if(val)
	{
		*PORTx |= (1 << PORTxn);
	}
	else
	{
		*PORTx &= ~(1 << PORTxn);
	}
}

void  nhay_dong_thoi(unsigned char arr1[], unsigned char arr2[])
{
	for(int i =0; i < 8; i++)
	{
		write_pin(&PORTD,arr1[i],1);
		_delay_ms(35);
	}
	for(int i =0; i < 6; i++)
	{
		write_pin(&PORTB,arr2[i],1);
		_delay_ms(35);
	}
	for(int i =0; i < 8; i++)
	{
		write_pin(&PORTD,arr1[i],0);
		_delay_ms(35);
	}
	for(int i =0; i < 6; i++)
	{
		write_pin(&PORTB,arr2[i],0);
		_delay_ms(35);
	}
}

void  con_tro_chay(unsigned char arr1[], unsigned char arr2[])
{
	for(int i =0; i < 8; i++)
	{
		write_pin(&PORTD,arr1[i],1);
		_delay_ms(20);
		write_pin(&PORTD,arr1[i],0);
		_delay_ms(20);
	}
	for(int i =0; i < 6; i++)
	{
		write_pin(&PORTB,arr1[i],1);
		_delay_ms(20);
		write_pin(&PORTB,arr1[i],0);
		_delay_ms(20);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD |= 0xFF;
	DDRB |= 0xFF;
	unsigned char led1[] = {PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6, PORTD7};
	unsigned char led2[] = {PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5};	
    while (1) 
    {
		nhay_dong_thoi(led1,led2);
		con_tro_chay(led1,led2);
    }
}

