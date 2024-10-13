/*
 * uart.c
 *
 * Created: 10/12/2024 8:04:00 PM
 *  Author: DungLT
 */ 
#include "uart.h"
void UART_Init()
{
	UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
	UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
	UCSR0A = 0x00;
	UBRR0H = 0x00;
	UBRR0L = 0x33;
}

void UART_Transmited(unsigned char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void UART_Transmited_Multi_char(unsigned char *data)
{
	int i =0;
	while(data[i] != '\0')
	{
		UART_Transmited(data[i]);
		i++;
	}
	
}

unsigned char UART_Received()
{
	while (!(UCSR0A & (1 << RXC0)));
	
	return UDR0;
}