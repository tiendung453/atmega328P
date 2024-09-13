#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int main(void)
{
	// C?u h�nh ch�n PC3 l� ch�n xu?t (output)
	DDRC = 1 << 3;
	// ??t m?c th?p cho ch�n PC3
	PORTC = ~(1 << 3);

	// C?u h�nh ng?t ngo�i INT0 ?? k�ch ho?t khi c� c?nh xu?ng
	EICRA = (1 << ISC01); // ISC01 = 1, ISC00 = 0 ?? k�ch ho?t tr�n c?nh xu?ng
	EIMSK = (1 << INT0);  // Cho ph�p ng?t INT0

	sei(); // B?t ng?t to�n c?c

	while (1)
	{
		// Code ch�nh c?a ch??ng tr�nh
	}
}

// H�m ISR cho ng?t INT0
ISR(INT0_vect)
{
	PORTC ^= (1 << 3); // ??o tr?ng th�i ch�n PC3
}
