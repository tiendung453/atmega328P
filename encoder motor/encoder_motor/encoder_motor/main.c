/*
 * encoder_motor.c
 *
 * Created: 9/30/2024 2:07:27 AM
 * Author : DungLT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>


volatile uint32_t dem = 0;
void timer1_init()
{
	TCCR1B |= (1 << CS10);
	TCCR1A = 0x00;
	TIMSK1 |= (1 << TOIE1);
}

ISR(TIMER1_OVF_vect)
{
	dem++;
}

uint32_t gettick()
{
	return (dem * 65536) + (uint32_t)TCNT1;
}


void PWM_Init(uint8_t ocr)
{
	TCCR0A |= (1 << WGM01)|(1 << WGM00); // ch? ?? fast pwm 3 top =  0xFF
	TCCR0B |= (1 << CS00)|(1 << CS01); // prescaler = 64;
	TCCR0A |= (1 << COM0A1); // non invert
	OCR0A = ocr; 
}

void gpio_init()
{
	DDRD = (1 << DDD6);
	DDRD |= (1 << DDD0) | (1 << DDD1); 
	PORTD |= (1 << PORTD0);
	PORTD &= ~(1 << PORTD1);
}

void interrupt_init()
{
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
}

ISR(INT0_vect)
{
	dem++;
}

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

void set_motor(int dir, )

ISR(USART_TX_vect)
{
	PORTB = UDR0;
}

int main(void)
{
	PWM_Init(255);
	timer1_init();
	interrupt_init();
	gpio_init();
	usart_init();
	dem = 0;
	TCNT1 = 0;
	sei();

	cli();
    while (1) 
    {	
    }
}
