#include "button.h"

#define HIGH 1

int main(void)
{
	/* Replace with your application code */
	DDRD &= ~(1 << DDD1);  // C?u hình PD1 là ??u vào
	DDRD |= (1 << DDD3);   // C?u hình PD3 là ??u ra

	while (1)
	{
		// ??c tr?ng thái c?a chân PD1 (nút nh?n ho?c tín hi?u ??u vào)
		if (!(PIND & (1 << PIND1)))  // Ki?m tra bit 1 c?a PIND (t??ng ???ng v?i PD1)
		{
			PORTD |= (1 << PORTD3);  // ??t PD3 lên m?c cao (1)
		}
		else
		{
			PORTD &= ~(1 << PORTD3);  // ??t PD3 xu?ng m?c th?p (0)
		}
	}
}
