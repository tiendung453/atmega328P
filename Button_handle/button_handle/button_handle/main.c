#include "button.h"

#define HIGH 1

int main(void)
{
	/* Replace with your application code */
	DDRD &= ~(1 << DDD1);  // C?u h�nh PD1 l� ??u v�o
	DDRD |= (1 << DDD3);   // C?u h�nh PD3 l� ??u ra

	while (1)
	{
		// ??c tr?ng th�i c?a ch�n PD1 (n�t nh?n ho?c t�n hi?u ??u v�o)
		if (!(PIND & (1 << PIND1)))  // Ki?m tra bit 1 c?a PIND (t??ng ???ng v?i PD1)
		{
			PORTD |= (1 << PORTD3);  // ??t PD3 l�n m?c cao (1)
		}
		else
		{
			PORTD &= ~(1 << PORTD3);  // ??t PD3 xu?ng m?c th?p (0)
		}
	}
}
