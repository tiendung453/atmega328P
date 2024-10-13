/*
 * GccApplication1.c
 *
 * Created: 9/25/2024 4:12:04 PM
 * Author : DungLT
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart_init(void)
{
	// baudrate = 9600
	UBRR0H = 0x00;
	UBRR0L = 0x33;
	// bat truyen nhan 
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	// set 8bit 1stopbit
	UCSR0C = (1 << UCSZ00)|(1 << UCSZ01);
}

void usart_transmit(unsigned char data)
{
	// doi cho den khi buffer rong
	/*udre0 = 5 dich phai 5 bit
	ucsra = 00000000 & 00100000 = 0*/
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char usart_receive(void)
{
	// doi khi data duoc nhan
	while(!(UCSR0A & (1<<RXC0)));
	// lay va tra ve data tu buffer
	return UDR0;
}

void usart_transmit_it_config()
{
	UCSR0B |= (1 << TXCIE0);
}

void transmit_string(char *str)
{
	int i =0;
	while (str[i] != '\0')
	{
		usart_transmit(str[i]);
		i++;
	}
}

ISR(USART_TX_vect)
{
	PORTB = UDR0;
}

int main(void)
{
    /* Replace with your application code */
	usart_init();
	usart_transmit_it_config();
	sei();
	DDRB = 0xFF;
	usart_transmit('c');
	usart_transmit(' ');
	transmit_string("hello bruh");
    while (1) 
    {
    }
	return 0;
}
