#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	DDRD |= (1 << DDD2)|(1 << DDD3);

	OCR0A = 255;


	TCCR0A = (1 << WGM00)|(1 << COM0A1);
	TCCR0B = (1 << CS00);
	OCR0A = 100;
	
				PORTD = (1 << PORTD2);
				PORTD &= ~(1 << PORTD3);

	while (1)
	{
		
	}

	return 0;
}
