#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int main(void)
{
	// C?u hình chân PC3 là chân xu?t (output)
	DDRC = 1 << 3;
	// ??t m?c th?p cho chân PC3
	PORTC = ~(1 << 3);

	// C?u hình ng?t ngoài INT0 ?? kích ho?t khi có c?nh xu?ng
	EICRA = (1 << ISC01); // ISC01 = 1, ISC00 = 0 ?? kích ho?t trên c?nh xu?ng
	EIMSK = (1 << INT0);  // Cho phép ng?t INT0

	sei(); // B?t ng?t toàn c?c

	while (1)
	{
		// Code chính c?a ch??ng trình
	}
}

// Hàm ISR cho ng?t INT0
ISR(INT0_vect)
{
	PORTC ^= (1 << 3); // ??o tr?ng thái chân PC3
}
